#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

void settings_init(void);
void settings_handle_message(const char* topic, const char* data);
void settings_save_config(void);
void settings_load_config(void);
void settings_set_value(const char* key, const char* value);

#ifdef __cplusplus
}
#endif

#endif