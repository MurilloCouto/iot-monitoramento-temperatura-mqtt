# Sistema de Monitoramento da Temperatura do Ar Utilizando IoT e MQTT

## Grupo 12

### Integrantes

* Henrique dos Santos Coelho
* Jhonatas Correia Melo
* Murilo Alves Couto

### Professor
* Andre Luis de Oliveira

# 1. Visão Geral do Projeto

Este projeto apresenta o desenvolvimento de um sistema de monitoramento ambiental baseado em Internet das Coisas (IoT), utilizando um microcontrolador ESP32, um sensor DHT22 e o protocolo MQTT para comunicação entre dispositivos.

A proposta consiste em monitorar temperatura e umidade do ambiente, transmitindo essas informações para um broker MQTT através da internet. Além disso, o sistema possui um atuador representado por um LED, que pode ser acionado automaticamente em função da temperatura ou remotamente por meio de mensagens MQTT.

O projeto foi desenvolvido e testado utilizando a plataforma de simulação Wokwi.
link da ferramenta: https://wokwi.com/



# 2. Objetivo

Desenvolver uma solução IoT capaz de:

* Realizar leitura de temperatura e umidade.
* Conectar-se à internet utilizando Wi-Fi.
* Comunicar-se através do protocolo MQTT.
* Publicar informações em tópicos MQTT.
* Receber comandos remotos.
* Acionar um dispositivo de saída (LED).
* Demonstrar os conceitos de sensoriamento, comunicação e atuação em sistemas IoT.


# 3. Arquitetura do Sistema

O sistema foi estruturado em três camadas principais:

## Camada de Sensoriamento

Responsável pela coleta dos dados ambientais.

Componente utilizado:

* Sensor DHT22

Dados coletados:

* Temperatura (°C)
* Umidade Relativa (%)


## Camada de Processamento

Responsável pelo tratamento das informações.

Componente utilizado:

* ESP32 DevKit V4

Funções executadas:

* Leitura do sensor.
* Processamento dos dados.
* Controle do LED.
* Comunicação com o broker MQTT.


## Camada de Comunicação

Responsável pela transmissão de dados.

Tecnologias utilizadas:

* Wi-Fi
* MQTT

Broker utilizado:

broker.hivemq.com

Porta:

1883


# 4. Componentes Utilizados

| Componente      | Função                          |
| --------------- | ------------------------------- |
| ESP32 DevKit V4 | Microcontrolador principal      |
| DHT22           | Sensor de temperatura e umidade |
| LED Vermelho    | Indicador visual                |
| Resistor 220 Ω  | Proteção do LED                 |
| Broker MQTT     | Comunicação Publish/Subscribe   |
| MQTT Explorer   | Monitoramento dos tópicos       |
| Wokwi           | Simulação do circuito           |



# 5. Diagrama de Funcionamento

Fluxo geral do sistema:

Sensor DHT22 → ESP32 → Wi-Fi → Broker MQTT → MQTT Explorer

Controle remoto:
MQTT Explorer → Broker MQTT → ESP32 → LED


# 6. Comunicação MQTT

O protocolo MQTT foi utilizado para permitir a comunicação entre dispositivos conectados.

Modelo utilizado:

Publish / Subscribe



## Tópicos MQTT

### Temperatura

mackenzie/iot/grupo12/temperatura

Função:

Publicação dos valores de temperatura.



### Umidade

mackenzie/iot/grupo12/umidade

Função:

Publicação dos valores de umidade.



### Controle do LED

mackenzie/iot/grupo12/led

Função:

Recebimento de comandos remotos.

Mensagens aceitas:

ON

OFF



# 7. Funcionamento Esperado

## Inicialização

Ao iniciar o sistema:

1. O ESP32 é energizado.
2. O sensor DHT22 é inicializado.
3. O LED permanece desligado.
4. O ESP32 conecta-se ao Wi-Fi.
5. O ESP32 conecta-se ao broker MQTT.

Mensagens esperadas:

Wi-Fi conectado!

Conectando ao MQTT...

conectado!

Inscrito no tópico:
mackenzie/iot/grupo12/led



## Leitura do Sensor

A cada três segundos:

* Temperatura é lida.
* Umidade é lida.
* Dados são enviados ao broker MQTT.

Exemplo esperado:

Temperatura: 25.0 °C

Umidade: 60 %

Dados enviados via MQTT



## Controle Automático

Caso:

Temperatura ≥ 30°C

O sistema deve:

* Acionar o LED.
* Informar o evento no monitor serial.

Exemplo:

LED ligado automaticamente

Temperatura acima do limite



## Controle Remoto

Ao publicar:

Tópico:

mackenzie/iot/grupo12/led

Mensagem:

ON

Resultado esperado:

LED ligado.

Ao publicar:

OFF

Resultado esperado:

LED desligado.



# 8. Estrutura do Software

Principais bibliotecas utilizadas:

WiFi.h

Responsável pela conexão Wi-Fi.

PubSubClient.h

Responsável pela comunicação MQTT.

DHTesp.h

Responsável pela leitura do sensor DHT22.



# 9. Estrutura do Código

## conectarWiFi()

Função responsável pela conexão do ESP32 à rede sem fio.



## conectarMQTT()

Função responsável pela conexão com o broker MQTT.



## callback()

Responsável por receber mensagens MQTT.

Executa:

* Leitura do tópico.
* Interpretação do comando.
* Acionamento do LED.



## loop()

Executa continuamente:

* Verificação da conexão MQTT.
* Leitura do sensor.
* Publicação dos dados.
* Controle automático do LED.



# 10. Resultados Obtidos

Durante os testes foi possível validar:

✓ Inicialização do ESP32

✓ Conexão Wi-Fi

✓ Obtenção de endereço IP

✓ Comunicação MQTT

✓ Inscrição em tópicos

✓ Estrutura de publicação e assinatura

✓ Controle lógico do LED

Exemplo observado:

Wi-Fi conectado!

IP: 10.10.0.2

Conectando ao MQTT...

conectado!

Inscrito no tópico:
mackenzie/iot/grupo12/led



# 11. Limitações Encontradas

Durante os testes realizados no ambiente Wokwi foi identificada uma falha na leitura do sensor DHT22.

O sistema apresentava repetidamente a mensagem:

Erro ao ler o DHT22

Como consequência:

* Não foi possível validar a leitura real dos dados ambientais.
* Não foi possível comprovar o envio de temperatura e umidade ao broker MQTT.
* O acionamento automático do LED baseado na temperatura não pôde ser demonstrado integralmente.

Entretanto, a infraestrutura de comunicação MQTT permaneceu funcional durante os testes.



# 12. Melhorias Futuras

* Utilização de hardware físico real.
* Dashboard de monitoramento.
* Banco de dados para armazenamento histórico.
* Integração com aplicativos móveis.
* Notificações automáticas.
* Inclusão de sensores adicionais.



# 13. Tecnologias Utilizadas

* ESP32
* MQTT
* Wi-Fi
* DHT22
* MQTT Explorer
* Wokwi
* Arduino Framework
* C++



# 14. Repositório

Link do GitHub:

https://github.com/MurilloCouto/iot-monitoramento-temperatura-mqtt



# 15. Vídeo Demonstrativo

Link do YouTube:

https://www.youtube.com/watch?v=boniY5BjQEc



# 16. Conclusão

O projeto permitiu aplicar conceitos fundamentais de Internet das Coisas, comunicação entre dispositivos, protocolos de rede e integração entre sensores e atuadores.

Apesar da limitação encontrada na leitura do sensor DHT22 durante a simulação, foi possível validar a arquitetura IoT proposta, a conexão com a internet e a utilização do protocolo MQTT como mecanismo de comunicação entre dispositivos distribuídos.

Os resultados obtidos demonstram a viabilidade da solução e servem como base para futuras implementações em ambiente físico real.

