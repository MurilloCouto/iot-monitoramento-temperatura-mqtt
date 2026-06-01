🌡️ Sistema de Monitoramento da Temperatura do Ar Utilizando IoT e MQTT

Projeto desenvolvido para demonstrar conceitos de Internet das Coisas (IoT) utilizando ESP32, DHT22 e o protocolo MQTT para monitoramento ambiental e controle remoto de dispositivos.

📋 Sobre o Projeto

Este sistema realiza a leitura de temperatura e umidade através de um sensor DHT22 conectado a um ESP32. Os dados são enviados para um broker MQTT pela internet, permitindo monitoramento em tempo real.

Além disso, o projeto conta com um LED indicador, que pode ser acionado:

Automaticamente quando a temperatura ultrapassa um limite definido;
Remotamente por meio de mensagens MQTT.

O ambiente de testes foi desenvolvido utilizando a plataforma Wokwi.

🎯 Objetivos
Ler temperatura e umidade do ambiente;
Conectar o ESP32 à internet via Wi-Fi;
Utilizar o protocolo MQTT para comunicação;
Publicar dados em tópicos MQTT;
Receber comandos remotos;
Acionar um LED como atuador;
Demonstrar conceitos de sensoriamento, comunicação e atuação em sistemas IoT.

🏗️ Arquitetura do Sistema
Camada de Sensoriamento

Responsável pela coleta dos dados ambientais.

Componente:

DHT22

Dados coletados:

Temperatura (°C)
Umidade Relativa (%)
Camada de Processamento

Componente:

ESP32 DevKit V4

Funções:

Leitura do sensor;
Processamento dos dados;
Controle do LED;
Comunicação MQTT.
Camada de Comunicação

Tecnologias:

Wi-Fi
MQTT

Broker utilizado:

broker.hivemq.com
Porta: 1883

🔧 Componentes Utilizados
Componente	Função
ESP32 DevKit V4	Microcontrolador principal
DHT22	Sensor de temperatura e umidade
LED Vermelho	Indicador visual
Resistor 220 Ω	Proteção do LED
Broker MQTT	Comunicação Publish/Subscribe
MQTT Explorer	Monitoramento dos tópicos
Wokwi	Simulação do circuito

📡 Comunicação MQTT
Tópico de Temperatura
mackenzie/iot/grupo12/temperatura

Responsável pela publicação dos valores de temperatura.

Tópico de Umidade
mackenzie/iot/grupo12/umidade

Responsável pela publicação dos valores de umidade.

Controle do LED
mackenzie/iot/grupo12/led

Mensagens aceitas:

ON
OFF

⚙️ Funcionamento
Inicialização

Ao iniciar o sistema:

ESP32 é energizado;
Sensor DHT22 é inicializado;
LED permanece desligado;
ESP32 conecta ao Wi-Fi;
ESP32 conecta ao Broker MQTT.
Leitura do Sensor

A cada 3 segundos:

Temperatura é lida;
Umidade é lida;
Dados são publicados no broker MQTT.
Controle Automático

Quando:

Temperatura ≥ 30°C

O sistema:

Liga o LED;
Registra o evento no monitor serial.
Controle Remoto

Publicando:

Tópico: mackenzie/iot/grupo12/led
Mensagem: ON

Resultado:

LED Ligado

Publicando:

Mensagem: OFF

Resultado:

LED Desligado

📚 Bibliotecas Utilizadas
WiFi.h
PubSubClient.h
DHTesp.h

Funções:

Conexão Wi-Fi;
Comunicação MQTT;
Leitura do sensor DHT22.

🧩 Estrutura do Código
conectarWiFi()

Responsável pela conexão do ESP32 à rede Wi-Fi.

conectarMQTT()

Responsável pela conexão ao broker MQTT.

callback()

Responsável por:

Receber mensagens MQTT;
Interpretar comandos;
Acionar o LED.
loop()

Executa continuamente:

Verificação da conexão MQTT;
Leitura do sensor;
Publicação dos dados;
Controle automático do LED.

✅ Resultados Obtidos

Durante os testes foi possível validar:

Inicialização do ESP32;
Conexão Wi-Fi;
Obtenção de endereço IP;
Comunicação MQTT;
Inscrição em tópicos;
Estrutura Publish/Subscribe;
Controle lógico do LED.
⚠️ Limitações Encontradas

Durante os testes no Wokwi foi identificada uma falha na leitura do sensor DHT22.

Mensagem observada:

Erro ao ler o DHT22

Impactos:

Não foi possível validar a leitura real dos dados;
Não foi possível comprovar o envio de temperatura e umidade;
O acionamento automático do LED não pôde ser demonstrado integralmente.

Apesar disso, a infraestrutura MQTT permaneceu funcional durante os testes.

🚀 Melhorias Futuras
Utilização de hardware físico real;
Dashboard para monitoramento;
Banco de dados para histórico;
Aplicativo móvel;
Notificações automáticas;
Inclusão de novos sensores.

🛠️ Tecnologias Utilizadas
ESP32
MQTT
Wi-Fi
DHT22
MQTT Explorer
Wokwi
Arduino Framework
C++

📂 Repositório
[link](https://github.com/MurilloCouto/iot-monitoramento-temperatura-mqtt)

🎥 Demonstração
https://youtube.com/SEU-VIDEO********** SUBSTITUIR

👥 Integrantes
Henrique Coelho
Jhonatas Melo
Murillo Couto

📄 Licença

Este projeto foi desenvolvido para fins acadêmicos no curso de Análise e Desenvolvimento de Sistemas da Universidade Presbiteriana Mackenzie.
