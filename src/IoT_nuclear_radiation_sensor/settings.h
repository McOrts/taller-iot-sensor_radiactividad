// WiFi Configuration
const char* ssid = "¿?";
const char* password = "?¿";

// MQTT Configuration
const char* mqtt_server = "?¿";
const int   mqtt_port = 11884;
const char* mqttUser = "¿?";
const char* mqttPassword = "?¿";
const char* mqtt_id = "radiation_sensor_canamunt";
const char* mqtt_sub_topic_healthcheck = "/canamunt/meteo/radiation_sensor";
const char* mqtt_sub_topic_ip = "/canamunt/meteo/radiation_sensor/ip";
const char* mqtt_sub_topic_operation = "/canamunt/meteo/radiation_sensor/operation";
const char* mqtt_pub_topic_radiation = "/canamunt/meteo/radiation_sensor/cpm";

// Other params
const int pin_detector = 14; //D5
