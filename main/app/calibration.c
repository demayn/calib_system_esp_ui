#include "calibration.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"

static const char *TAG = "calibration";


void calibration_init(void) {
    ESP_LOGI(TAG, "Calibration module initialized");
}


void calibration_start(void) {
    ESP_LOGI(TAG, "Starting calibration");
    // Hier später MQTT Message senden
}

void calibration_set_parameter(const char* parameter, const char* value) {
    ESP_LOGI(TAG, "Setting calibration parameter: %s = %s", parameter, value);
    // Hier später über Message Bus arbeiten
}