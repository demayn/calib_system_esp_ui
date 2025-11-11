#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdbool.h> 

typedef enum {
    ERROR_NONE = 0,
    ERROR_MQTT_NOT_CONNECTED,
    ERROR_UI_OBJECT_NULL,
    ERROR_INVALID_PARAMETER,
    ERROR_NETWORK_TIMEOUT,
    ERROR_CALIBRATION_FAILED
} error_code_t;

void error_handler_init(void);
void error_handler_report(error_code_t code, const char* context);
bool error_handler_has_errors(void);
const char* error_handler_get_last_message(void);

#endif