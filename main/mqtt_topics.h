#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

// NUR für Publishing (outgoing) - das ist der echte Gewinn!
#define TOPIC_CMD_POSITIONING_START    "positionierung/start"
#define TOPIC_CMD_POSITIONING_STOP     "positionierung/stop" 
#define TOPIC_CMD_CALIBRATION_START    "calibration/start"

// Für Subscriptions (incoming) - nur zur Dokumentation
#define TOPIC_DATA_ISTWERT             "istwert"
#define TOPIC_DATA_CALIBRATION_STATUS  "calibration/status"

#endif