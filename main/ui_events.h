#ifndef UI_EVENTS_H
#define UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void ui_events_init(void);
void ui_handle_mqtt_message(const char* topic, const char* data);

#ifdef __cplusplus
}
#endif

#endif