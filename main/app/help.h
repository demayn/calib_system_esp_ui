#ifndef HELP_H
#define HELP_H

#ifdef __cplusplus
extern "C" {
#endif

void help_init(void);
void help_handle_message(const char* topic, const char* data);
void help_show_page(int page);

#ifdef __cplusplus
}
#endif

#endif