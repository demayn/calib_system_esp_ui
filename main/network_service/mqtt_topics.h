#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

//Broker IP-Adresse
#define MQTT_BROKER_URI "mqtt://192.168.0.12"


// NUR für Publishing outgoing - das ist der echte Gewinn!
#define TOPIC_CMD_CALIBRATION_START    "calibration/start"
#define TOPIC_CMD_POSITIONING_SOLLWERT_X "positionierung/sollwert_x" 
#define TOPIC_CMD_POSITIONING_SOLLWERT_Y "positionierung/sollwert_y"

// Für Subscriptions incoming - nur zur Dokumentation
#define TOPIC_DATA_ISTWERT_X            "positionierung/istwert_x"
#define TOPIC_DATA_ISTWERT_Y           "positionierung/istwert_y"


//QoS Level (Quality of Service)
#define MQTT_QOS_0 0 // Sensor-Daten können auch mal verloren gehen
#define MQTT_QOS_1 1 // Mindestens einmal zustellen
#define MQTT_QOS_2 2 // Genau einmal zustellen

#endif