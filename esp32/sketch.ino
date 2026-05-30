#include <WiFi.h>
#include <PubSubClient.h>


// ================= WIFI =================


const char* ssid = "Wokwi-GUEST";
const char* password = "";


// ================= MQTT =================


const char* mqtt_server = "broker.hivemq.com";


WiFiClient espClient;
PubSubClient client(espClient);


// ================= LEDs =================


const int LED_WIFI = 18;
const int LED_MQTT = 19;


// ================= SENSOR =================


#define LIGHT_SENSOR_PIN 36
#define RELAY_PIN 27
#define ANALOG_THRESHOLD 500


// ================= WIFI =================


void setup_wifi() {


  Serial.println();
  Serial.print("Connecting WiFi");


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {


    delay(500);
    Serial.print(".");


    digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
  }


  Serial.println("\nWiFi connected");


  digitalWrite(LED_WIFI, HIGH);
}


// ================= MQTT =================


void reconnect() {


  while (!client.connected()) {


    Serial.print("Connecting MQTT...");


    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);


    if (client.connect(clientId.c_str())) {


      Serial.println(" connected");


      client.subscribe("ESP_TESTE");


      digitalWrite(LED_MQTT, HIGH);


    } else {


      Serial.print(" failed rc=");
      Serial.println(client.state());


      digitalWrite(LED_MQTT, LOW);


      delay(5000);
    }
  }
}


// ================= SENSOR DE LUZ =================


void sensorLuz() {

  // INICIA CONTAGEM DE TEMPO
  unsigned long inicioSensor = millis();

  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Luminosidade: ");
  Serial.println(analogValue);

  // AMBIENTE ESCURO
  if (analogValue > ANALOG_THRESHOLD) {

    digitalWrite(RELAY_PIN, HIGH);

    Serial.println("RELE LIGADO");

    // TEMPO ATUADOR
    unsigned long tempoAtuador = millis() - inicioSensor;

    Serial.print("Tempo resposta atuador: ");
    Serial.print(tempoAtuador);
    Serial.println(" ms");

    // ENVIO MQTT
    client.publish("cidade/luz/status", "LUZ LIGADA");

    // TEMPO MQTT
    unsigned long tempoMQTT = millis() - inicioSensor;

    Serial.print("Tempo envio MQTT: ");
    Serial.print(tempoMQTT);
    Serial.println(" ms");

  } else {

    digitalWrite(RELAY_PIN, LOW);

    Serial.println("RELE DESLIGADO");

    client.publish("cidade/luz/status", "LUZ DESLIGADA");
  }
}


// ================= SETUP =================


void setup() {


  Serial.begin(115200);


  // LEDs
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_MQTT, OUTPUT);


  // Relé
  pinMode(RELAY_PIN, OUTPUT);


  digitalWrite(LED_WIFI, LOW);
  digitalWrite(LED_MQTT, LOW);
  digitalWrite(RELAY_PIN, LOW);


  setup_wifi();


  client.setServer(mqtt_server, 1883);
}


// ================= LOOP =================


void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  sensorLuz();

  delay(1000);
}