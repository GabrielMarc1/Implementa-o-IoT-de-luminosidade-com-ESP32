# Sistema Inteligente de Iluminação Urbana com ESP32

## Descrição

Este projeto apresenta o desenvolvimento de um sistema inteligente de iluminação urbana baseado em Internet das Coisas (IoT), utilizando o microcontrolador ESP32.

O sistema monitora a luminosidade do ambiente por meio de um sensor de luz e realiza o acionamento automático da iluminação através de um módulo relé. Além disso, o dispositivo conecta-se à internet utilizando Wi-Fi e estabelece comunicação com um broker MQTT para envio de informações em tempo real.

O projeto foi desenvolvido em ambiente de simulação Wokwi e programado utilizando Arduino IDE.

## Funcionalidades

* Monitoramento de luminosidade ambiente.
* Acionamento automático da iluminação.
* Comunicação via Wi-Fi.
* Comunicação MQTT utilizando broker HiveMQ.
* Indicação visual do estado da conexão Wi-Fi.
* Indicação visual do estado da conexão MQTT.
* Monitoramento em tempo real através do Serial Monitor.
* Medição de latência do sistema.

## Hardware Utilizado

* ESP32 DevKit V4
* Sensor de luminosidade (LDR Module)
* Módulo Relé 5V
* LED indicador Wi-Fi
* LED indicador MQTT
* LED representando iluminação pública
* Resistores de 150 Ω
* Jumpers
* Protoboard virtual (Wokwi)

## Software Utilizado

* Arduino IDE
* Wokwi Simulator
* Biblioteca WiFi.h
* Biblioteca PubSubClient.h

## Comunicação e Protocolos

### TCP/IP

O ESP32 conecta-se à internet através de uma rede Wi-Fi utilizando a pilha TCP/IP integrada.

### MQTT

O protocolo MQTT é utilizado para comunicação entre o ESP32 e o broker HiveMQ.

Broker utilizado:

broker.hivemq.com

Porta:

1883

## Como Executar

1. Abrir o projeto na Arduino IDE ou Wokwi.
2. Instalar a biblioteca PubSubClient.
3. Compilar o código.
4. Executar a simulação.
5. Monitorar os dados através do Serial Monitor.

## Resultados

Durante os testes foram observados:

* Tempo médio de resposta do atuador: aproximadamente 1 ms.
* Tempo médio de envio MQTT: aproximadamente 4 ms.

Os resultados demonstram baixa latência e funcionamento adequado da solução proposta.
