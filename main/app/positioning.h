#ifndef POSITIONING_H
#define POSITIONING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Callback Typ für Istwert Updates
 */
typedef void (*positioning_istwert_callback_t)(const char* value);

/**
 * @brief Initialisiert das Positioning Modul
 * @param callback Callback für Istwert Updates
 */
void positioning_init(positioning_istwert_callback_t callback);

/**
 * @brief Verarbeitet MQTT Nachrichten für die Positionierung
 */
void positioning_handle_mqtt_message(const char* topic, const char* data);

/**
 * @brief Startet die Positionierung
 */
void positioning_start(void);

/**
 * @brief Stoppt die Positionierung
 */
void positioning_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* POSITIONING_H */