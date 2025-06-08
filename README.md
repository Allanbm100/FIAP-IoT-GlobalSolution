# 🛵 Projeto SafeQuake - Global Solution

## 📋 Descrição do Projeto

O projeto SafeQuake é uma solução IoT desenvolvida para monitorar condições ambientais e possíveis vibrações estruturais, auxiliando em cenários de risco de terremotos. Utilizando um ESP32, sensores no Wokwi e comunicação MQTT com um painel Node-RED, a solução permite o acompanhamento em tempo real de temperatura, umidade e atividade sísmica.

---

## 🔧 Tecnologias Utilizadas

- C++ (Arduino/ESP32)
- MQTT (PubSubClient e Mosquitto)
- Node-RED
- Broker MQTT local
- Dashboard web em tempo real

---

## 🚀 Instalação e Execução

### ESP32 (Firmware Arduino)

1. Abra o `main.cpp` na IDE Arduino.
2. Configure o Wi-Fi (SSID e senha) e o IP do broker MQTT.
3. Carregue o código no ESP32.
4. O dispositivo começará a publicar os dados em loop.

### Node-RED

1. Instale o Node-RED:  
   ```bash
   npm install -g --unsafe-perm node-red
   ```
2. Inicie o Node-RED:
   ```bash
   node-red
   ```
3. Importe o fluxo do arquivo `flows-Node-Red.json` na interface do Node-RED (http://<SEU_IP>:1880).
4. Configure o broker MQTT no Node-RED com o mesmo IP usado no ESP32.
5. Acesse o dashboard: http://<SEU_IP>:1880/ui

---

## 📍 Funcionalidades

- Identificar a vibração local.
- Identificar a umidade do local.
- Identificar a temperatura do local.
- Definir atenção a situações que ultrapassem valores normais.
- Apresentar essa atenção de forma visual com LEDs.
- Apresentar os dados coletados em um dashboard.

---

## 👥 Equipe

| Nome Completo         | RM       |
| [Allan Brito Moreira] | [558948] |
| [Levi Magni]          | [98276]  |
| [Caio Liang]          | [558868] |
