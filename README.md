# Sistema de Monitoramento da Temperatura do Ar Utilizando IoT com HiveMQ

## Grupo 12

### Integrantes

* Henrique dos Santos Coelho
* Jhonatas Correia Melo
* Murillo Alves Couto

### Professor
* Andre Luis de Oliveira

---

# 1. Visão Geral do Projeto

Este projeto apresenta o desenvolvimento de um sistema de monitoramento ambiental baseado em Internet das Coisas (IoT), utilizando um microcontrolador ESP32, um sensor DHT22 e o protocolo MQTT com broker HiveMQ para comunicação entre dispositivos.

A proposta consiste em monitorar temperatura e umidade do ambiente, transmitindo essas informações para um broker MQTT na internet. Além disso, o sistema possui um atuador representado por um LED, que pode ser acionado automaticamente em função da temperatura ou remotamente por meio de mensagens MQTT.

O projeto foi desenvolvido e testado utilizando a plataforma de simulação Wokwi.  
Link da ferramenta: https://wokwi.com/

---

# 2. Objetivo

Desenvolver uma solução IoT capaz de:

* Realizar leitura de temperatura e umidade.
* Conectar-se à internet utilizando Wi-Fi.
* Utilizar o protocolo MQTT com broker HiveMQ.
* Publicar informações em tópicos MQTT.
* Receber comandos remotos.
* Acionar um dispositivo de saída (LED).
* Demonstrar os conceitos de sensoriamento, comunicação e atuação em sistemas IoT.

---

# 3. Arquitetura do Sistema

O sistema foi estruturado em três camadas principais:

## Camada de Sensoriamento

* Sensor DHT22  
* Coleta de temperatura (°C) e umidade (%)

## Camada de Processamento

* ESP32 DevKit V4  

Funções:

* Leitura do sensor  
* Processamento  
* Controle do LED  
* Comunicação MQTT  

## Camada de Comunicação

Tecnologias:

* Wi-Fi  
* MQTT (HiveMQ)

Broker utilizado:

broker.hivemq.com  

Porta:

1883  

---

# 4. Componentes Utilizados

| Componente | Função |
|----------|--------|
| ESP32 DevKit V4 | Microcontrolador |
| DHT22 | Sensor |
| LED Vermelho | Atuador |
| Resistor 220 Ω | Proteção |
| HiveMQ | Broker MQTT |
| MQTT Explorer / Web Client HiveMQ | Monitoramento |
| Wokwi | Simulação |

---

# 5. Diagrama de Funcionamento

Fluxo geral:

Sensor DHT22 → ESP32 → Wi-Fi → HiveMQ → Cliente  

Fluxo de controle:

Cliente → HiveMQ → ESP32 → LED  

---

# 6. Comunicação MQTT

Modelo utilizado:

Publish / Subscribe  

## Tópicos

- mackenzie/iot/grupo12/temperatura  
- mackenzie/iot/grupo12/umidade  
- mackenzie/iot/grupo12/led  

Mensagens aceitas:

- ON  
- OFF  

---

# 7. Funcionamento Esperado

## Inicialização

1. ESP32 liga  
2. Sensor inicializa  
3. Conecta ao Wi-Fi  
4. Conecta ao HiveMQ  
5. Inscreve no tópico do LED  

---

## Leitura do Sensor

A cada 3 segundos:

* leitura de temperatura  
* leitura de umidade  
* envio via MQTT  

---

## Controle Automático

Temperatura ≥ 30°C:

→ LED liga automaticamente  

---

## Controle Remoto

Publicação no tópico:

mackenzie/iot/grupo12/led  

ON → liga LED  
OFF → desliga LED  

---

# 8. Estrutura do Software

Bibliotecas:

* WiFi.h  
* PubSubClient.h  
* DHTesp.h  

---

# 9. Estrutura do Código

* conectarWiFi()  
* conectarMQTT()  
* callback()  
* loop()  

---

# 10. Resultados Obtidos

Durante os testes foi possível validar:

✅ Conexão Wi-Fi  
✅ Comunicação MQTT com HiveMQ  
✅ Publicação de dados  
✅ Controle remoto do LED  
✅ Automação baseada na temperatura  

---

## Medição de desempenho

### Atuador (HiveMQ → LED)

- 0,78 s  
- 0,74 s  
- 0,71 s  
- 0,71 s  

**Média: 0,74 s**

---

### Sensor (DHT22 → HiveMQ)

- 0,45 s  
- 0,39 s  
- 0,46 s  
- 0,50 s  

**Média: 0,45 s**

---

### Análise

O sistema apresentou baixa latência em ambas as medições.

O tempo de resposta do sensor (0,45 s) foi menor que o do atuador (0,74 s), debido ao fato de o atuador depender de um ciclo completo de envio, recepção e execução do comando.

---

# 11. Limitações Encontradas

Foram observadas limitações na visualização de mensagens no cliente MQTT, porém o funcionamento do sistema foi validado através do monitor serial e testes práticos.

---

# 12. Melhorias Futuras

* Uso de hardware real  
* Dashboard  
* Banco de dados  
* App mobile  
* Novos sensores  

---

# 13. Tecnologias Utilizadas

* ESP32  
* MQTT (HiveMQ)  
* Wi-Fi  
* DHT22  
* Arduino  
* Wokwi  

---

# 14. Repositório

https://github.com/MurilloCouto/iot-monitoramento-temperatura-mqtt  

---

# 15. Vídeo Demonstrativo

[https://www.youtube.com/watch?v=boniY5BjQEc](https://www.youtube.com/watch?v=UwB9aUJHbVA)  

---

# 16. Conclusão

O projeto demonstrou um sistema IoT completo, integrando sensoriamento, comunicação via MQTT e atuação remota.

Os resultados mostraram baixa latência e funcionamento consistente, validando o uso do protocolo MQTT para aplicações em tempo real.

---

# 17. Como Reproduzir

1. Acesse o Wokwi  
2. Execute o projeto  
3. Conecte ao HiveMQ:
   - broker.hivemq.com
   - porta 1883  

4. Inscreva-se:
mackenzie/iot/grupo12/#  

5. Teste envio:
- ON  
- OFF  

6. Observe o LED respondendo  
``
