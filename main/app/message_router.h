#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Verarbeitet eine MQTT Nachricht und leitet sie an Module weiter
 * @param topic Topic der Nachricht
 * @param data Inhalt der Nachricht
 */
void message_router_handle(const char* topic, const char* data);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGE_ROUTER_H */