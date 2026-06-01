#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ======================================
// CONFIGURAÇÕES DO WI-FI
// ======================================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ======================================
// CONFIGURAÇÕES MQTT
// ======================================
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

// ======================================
// TÓPICOS MQTT - GRUPO 12
// ======================================
const char* topicTemperatura = "mackenzie/iot/grupo12/temperatura";
const char* topicUmidade = "mackenzie/iot/grupo12/umidade";
const char* topicLed = "mackenzie/iot/grupo12/led";

// ======================================
// PINOS DO CIRCUITO
// ======================================
const int DHT_PIN = 4;
const int LED_PIN = 5;

// ======================================
// OBJETOS
// ======================================
WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dhtSensor;

// ======================================
// CONFIGURAÇÕES DO SISTEMA
// ======================================
float limiteTemperatura = 30.0;

unsigned long ultimoEnvio = 0;
const long intervaloEnvio = 3000;

// ======================================
// CONECTAR WIFI
// ======================================
void conectarWiFi() {

  Serial.println();
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("=================================");
  Serial.println("Wi-Fi conectado com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("=================================");
}

// ======================================
// CALLBACK MQTT
// ======================================
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String mensagem = "";

  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  Serial.print("Mensagem recebida: ");
  Serial.println(mensagem);

  if (String(topic) == topicLed) {

    if (mensagem == "ON") {

      digitalWrite(LED_PIN, LOW); // LIGA

      Serial.println("LED ligado via MQTT.");

    } else if (mensagem == "OFF") {

      digitalWrite(LED_PIN, HIGH); // DESLIGA

      Serial.println("LED desligado via MQTT.");
    }
  }
}

// ======================================
// CONECTAR MQTT
// ======================================
void conectarMQTT() {

  while (!client.connected()) {

    Serial.print("Conectando ao broker MQTT... ");

    String clientId = "ESP32-Grupo12-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println("CONECTADO!");

      client.subscribe(topicLed);

      Serial.print("Inscrito no tópico: ");
      Serial.println(topicLed);

    } else {

      Serial.print("Falha MQTT. Código: ");
      Serial.print(client.state());

      Serial.println(" tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

// ======================================
// SETUP
// ======================================
void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // LED começa apagado
  digitalWrite(LED_PIN, HIGH);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  conectarWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

// ======================================
// LOOP
// ======================================
void loop() {

  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  unsigned long agora = millis();

  if (agora - ultimoEnvio >= intervaloEnvio) {

    ultimoEnvio = agora;

    TempAndHumidity dados = dhtSensor.getTempAndHumidity();

    float temperatura = dados.temperature;
    float umidade = dados.humidity;

    if (isnan(temperatura) || isnan(umidade)) {

      Serial.println("Erro ao ler o sensor DHT22.");
      return;
    }

    Serial.println("=================================");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    client.publish(
      topicTemperatura,
      String(temperatura, 2).c_str());

    client.publish(
      topicUmidade,
      String(umidade, 2).c_str());

    Serial.println("Dados enviados via MQTT.");

    if (temperatura >= limiteTemperatura) {

      digitalWrite(LED_PIN, LOW); // LIGA

      Serial.println("Temperatura acima do limite.");
      Serial.println("LED acionado automaticamente.");

    } else {

      digitalWrite(LED_PIN, HIGH); // DESLIGA

      Serial.println("Temperatura normal.");
      Serial.println("LED desligado.");
    }

    Serial.println("=================================");
  }
}
