#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

// NUR für Publishing outgoing - das ist der echte Gewinn!
#define TOPIC_CMD_POSITIONING_START    "positionierung/start"
#define TOPIC_CMD_POSITIONING_STOP     "positionierung/stop" 
#define TOPIC_CMD_CALIBRATION_START    "calibration/start"

// Für Subscriptions incoming - nur zur Dokumentation
#define TOPIC_DATA_ISTWERT             "positionierung/istwert"
#define TOPIC_DATA_CALIBRATION_STATUS  "calibration/status"

//QoS Level (Quality of Service)
#define MQTT_QOS_0 0 // Sensor-Daten können auch mal verloren gehen
#define MQTT_QOS_1 1 // Mindestens einmal zustellen
#define MQTT_QOS_2 2 // Genau einmal zustellen

#endif