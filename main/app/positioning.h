#ifndef POSITIONING_H
#define POSITIONING_H

#ifdef __cplusplus
extern "C" {
#endif

void positioning_init(void);
void positioning_start(void);
void positioning_handle_message(const char* topic, const char* data);
void positioning_set_sollwert(const char* sollwert);
const char* positioning_get_current_sollwert(void);
void positioning_clear_sollwert(void);  
void positioning_send_sollwert(void);   
const char* positioning_get_current_sollwert(void);  




#ifdef __cplusplus
}
#endif

#endif