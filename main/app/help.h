#ifndef HELP_H
#define HELP_H

#ifdef __cplusplus
extern "C" {
#endif

void help_init(void);
void help_show_page(int page);
void help_handle_mqtt_message(const char* topic, const char* data);

#ifdef __cplusplus
}
#endif
#endif