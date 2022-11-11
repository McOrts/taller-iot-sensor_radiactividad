/*
   This code interacts with the RadiationD-v1.1 (CAJOE) Geiger counter board
   and reports readings in CPM (Counts Per Minute).
   Connect the output of the Geiger counter to pin inputPin.
   ******* !!!!!!!!! Adapted to WEMOS D1 mini interruptions
   Author: Carlos Orts
   Based on initial work of Andreas Spiess
   License: MIT License
   Please use freely with attribution. Thank you!
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "settings.h"

/* Times for CPM calculation */
#define LOG_PERIOD 60000  //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000  //Maximum logging period without modifying this sketch

unsigned long counts;     //variable for GM Tube events
unsigned long cpm;        //variable for CPM
unsigned int multiplier;  //variable for calculation CPM in this sketch
unsigned long previousMillis;  //variable for time measurement

/* Configuración cliente WiFi */
WiFiClient espClient;
String IP = String(15);

/* Configuración MQTT */
PubSubClient clientMqtt(espClient);
char msg[50];
String mqttcommand = String(14);

/* Tube pulse counter */
ICACHE_RAM_ATTR void tube_impulse() {
  counts++;
  Serial.print("*");
}

void setup() {
  Serial.begin(9600);

  /* Initialize board's LED */
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
    
  /* Initialize wifi */
  setup_wifi();
  clientMqtt.setServer(mqtt_server, mqtt_port);
  clientMqtt.setCallback(callback);
  
  /* Times for CPM calculation */
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;      //calculating multiplier, depend on your log period

  /* Setup GPIO sensor port */
  pinMode(pin_detector, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_detector),tube_impulse, FALLING);
  Serial.println("Interruption estarted");
  delay (1000);
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

void setup_wifi() {
  delay(10);

  // Comienza el proceso de conexión a la red WiFi
  Serial.println();
  Serial.print("[WIFI]Conectando a ");
  Serial.println(ssid);

  // Modo estación
  WiFi.mode(WIFI_STA);
  // Inicio WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  IP=IpAddress2String(WiFi.localIP());
  Serial.println("");
  Serial.println("[WIFI]WiFi conectada");
  Serial.print("[WIFI]IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT]Mensaje recibido (");
  Serial.print(topic);
  Serial.print(") ");
  mqttcommand = "";
  for (int i = 0; i < length; i++) {
    mqttcommand += (char)payload[i];
  }
  Serial.print(mqttcommand);
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if (mqttcommand == "command") {
    Serial.println("don");
  } 
}

void reconnect() {
  Serial.print("[MQTT]Intentando conectar a servidor MQTT... ");
  // Bucle hasta conseguir conexión
  while (!clientMqtt.connected()) {
    Serial.print(".");
    // Intento de conexión
    if (clientMqtt.connect(mqtt_id)) { // Ojo, para más de un dispositivo cambiar el nombre para evitar conflicto
      Serial.println("");
      Serial.println("[MQTT]Conectado al servidor MQTT");
      // Once connected, publish an announcement...
      clientMqtt.publish(mqtt_sub_topic_healthcheck, "starting");
      clientMqtt.publish(mqtt_sub_topic_ip, IP.c_str());
      // ... and subscribe
      clientMqtt.subscribe(mqtt_sub_topic_operation);
    } else {
      Serial.print("[MQTT]Error, rc=");
      Serial.print(clientMqtt.state());
      Serial.println("[MQTT]Intentando conexión en 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  if (!clientMqtt.connected()) {
    reconnect();
  }
  clientMqtt.loop();
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){
    digitalWrite(LED_BUILTIN, LOW);       
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    snprintf (msg, 10, "%6i", cpm);
    clientMqtt.publish(mqtt_pub_topic_radiation, msg);   
    Serial.print(msg);
    Serial.println(" CPM");
    counts = 0;
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
