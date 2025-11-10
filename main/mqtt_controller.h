#ifndef MQTT_CONTROLLER_H
#define MQTT_CONTROLLER_H

#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialisiert den MQTT Client
 */
void mqtt_app_start(void);

/**
 * @brief Sendet eine MQTT Nachricht
 * @param topic Topic name
 * @param data Nachricht als String
 */
void mqtt_publish_message(const char* topic, const char* data);

/**
 * @brief Prüft ob MQTT verbunden ist
 */
bool mqtt_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_CONTROLLER_H */