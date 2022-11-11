// WiFi Configuration
const char* ssid = "??";
const char* password = "??";

// MQTT Configuration
const char* mqtt_server = "192.168.1.114";
const int mqtt_port = 1883;
const char* mqtt_id = "radiation_sensor";
const char* mqtt_sub_topic_healthcheck = "/home/meteo/radiation_sensor";
const char* mqtt_sub_topic_ip = "/home/meteo/radiation_sensor/ip";
const char* mqtt_sub_topic_operation = "/home/meteo/radiation_sensor/operation";
const char* mqtt_pub_topic_radiation = "/home/meteo/radiation_sensor/cpm";

// Other params
const int pin_detector = 14; //D5
