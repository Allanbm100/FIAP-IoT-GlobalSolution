#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTStable.h>

#define DHTPIN 19

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "SEU_IP";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

DHTStable dht;

const int LED_VIB = 2;
const int LED_TEMP = 4;
const int LED_UMID = 5;

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado: " + WiFi.localIP().toString());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("SafeQuakeESP32")) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(". Tentando novamente em 5s...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_VIB, OUTPUT);
  pinMode(LED_TEMP, OUTPUT);
  pinMode(LED_UMID, OUTPUT);

  delay(10000);

  conectarWiFi();
  client.setServer(mqtt_server, mqtt_port);
  conectarMQTT();
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  int status = dht.read22(DHTPIN);

  float temp = NAN;
  float umid = NAN;

if (status == DHTLIB_OK) {
    temp = dht.getTemperature();
    umid = dht.getHumidity();
  } else {
    temp = random(200, 350) / 10.0;
    umid = random(300, 800) / 10.0;
  }

  float vib = random(10, 80) / 10.0;

  String ts = String(millis());

  String payloadVib = "{\"sensor\":\"vibracao\",\"valor\":" + String(vib, 2) + ",\"timestamp\":" + ts + "}";
  String payloadEnv = "{\"sensor\":\"ambiente\",\"temperatura\":" + String(temp, 1) + ",\"umidade\":" + String(umid, 1) + ",\"timestamp\":" + ts + "}";

  client.publish("safequake/vibracao", payloadVib.c_str());
  client.publish("safequake/ambiente", payloadEnv.c_str());

  Serial.println(">> " + payloadVib);
  Serial.println(">> " + payloadEnv);

  
  digitalWrite(LED_VIB, vib > 5.0 ? HIGH : LOW);
  digitalWrite(LED_TEMP, temp > 30.0 ? HIGH : LOW);
  digitalWrite(LED_UMID, umid < 40.0 ? HIGH : LOW);

  delay(10000);
}