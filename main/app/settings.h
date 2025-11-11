#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*settings_callback_t)(const char* setting, const char* value);

void settings_init(settings_callback_t callback);
void settings_handle_mqtt_message(const char* topic, const char* data);
void settings_save_config(void);
void settings_load_config(void);
void settings_set_value(const char* key, const char* value);

#ifdef __cplusplus
}
#endif
#endif