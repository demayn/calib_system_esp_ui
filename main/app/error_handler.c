#include "error_handler.h"
#include "esp_log.h"
#include <stdio.h>    
#include <stdbool.h> 

static const char *TAG = "error_handler";
static error_code_t last_error = ERROR_NONE;
static char error_context[64] = {0};

void error_handler_init(void) {
    last_error = ERROR_NONE;
    error_context[0] = '\0';
    ESP_LOGI(TAG, "Error handler initialized");
}

void error_handler_report(error_code_t code, const char* context) {
    last_error = code;
    snprintf(error_context, sizeof(error_context), "%s", context);
    
    switch(code) {
        case ERROR_MQTT_NOT_CONNECTED:
            ESP_LOGE(TAG, "MQTT not connected: %s", context);
            break;
        case ERROR_UI_OBJECT_NULL:
            ESP_LOGW(TAG, "UI object is NULL: %s", context);
            break;
        default:
            ESP_LOGE(TAG, "Error %d: %s", code, context);
    }
}

bool error_handler_has_errors(void) {
    return last_error != ERROR_NONE;
}

const char* error_handler_get_last_message(void) {
    return error_context;
}