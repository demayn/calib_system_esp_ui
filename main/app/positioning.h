#ifndef POSITIONING_H
#define POSITIONING_H

#ifdef __cplusplus
extern "C" {
#endif

void positioning_init(void);
void positioning_start(void);
void positioning_handle_message(const char* topic, const char* data);

#ifdef __cplusplus
}
#endif

#endif