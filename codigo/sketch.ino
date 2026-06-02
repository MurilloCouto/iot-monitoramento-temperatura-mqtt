#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22
#define LED_PIN 5

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

const char* topicTemperatura = "mackenzie/iot/grupo12/temperatura";
const char* topicUmidade = "mackenzie/iot/grupo12/umidade";
const char* topicLed = "mackenzie/iot/grupo12/led";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT_TYPE);

unsigned long ultimoEnvio = 0;
const long intervaloEnvio = 3000;

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }
  Serial.print("Mensagem recebida: ");
  Serial.println(mensagem);

  if (String(topic) == topicLed) {
    if (mensagem == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ligado via MQTT");
    }
    if (mensagem == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED desligado via MQTT");
    }
  }
}

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT... ");
    String clientId = "ESP32-Grupo12-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      client.subscribe(topicLed);
      Serial.print("Inscrito no tópico: ");
      Serial.println(topicLed);
    } else {
      Serial.print("Falha MQTT. Código: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  dht.begin();

  conectarWiFi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  Serial.println("=================================");
  Serial.println("Sistema iniciado");
  Serial.println("LED ligado para teste");
  Serial.println("=================================");
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  unsigned long agora = millis();
  if (agora - ultimoEnvio >= intervaloEnvio) {
    ultimoEnvio = agora;

    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    Serial.println("---------------------------------");

    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("ERRO: DHT22 sem leitura válida");
      client.publish("mackenzie/iot/grupo12/status", "Erro na leitura do DHT22");
    } else {
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");

      Serial.print("Umidade: ");
      Serial.print(umidade);
      Serial.println(" %");

      client.publish(topicTemperatura, String(temperatura, 2).c_str());
      client.publish(topicUmidade, String(umidade, 2).c_str());
      Serial.println("Dados enviados via MQTT");

      if (temperatura >= 30) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ligado automaticamente (temp >= 30°C)");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED desligado automaticamente");
      }
    }
    Serial.println("---------------------------------");
  }
}
