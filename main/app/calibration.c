#include "calibration.h"
#include "esp_log.h"
#include "string.h"
#include "mqtt_controller.h"

static const char *TAG = "calibration";
static calibration_callback_t calibration_callback = NULL;

void calibration_init(calibration_callback_t callback)
{
    calibration_callback = callback;
    ESP_LOGI(TAG, "Calibration module initialized");
}

void calibration_handle_mqtt_message(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);
    
    // Hier können Kalibrierungs-spezifische MQTT Nachrichten verarbeitet werden
    if (strcmp(topic, "calibration") == 0 && calibration_callback != NULL) {
        calibration_callback("status", data);
    }
}

void calibration_start(void)
{
    ESP_LOGI(TAG, "Starting calibration");
    mqtt_publish_message("calibration", "start");
}

void calibration_stop(void)
{
    ESP_LOGI(TAG, "Stopping calibration");
    mqtt_publish_message("calibration", "stop");
}

void calibration_set_parameter(const char* parameter, const char* value)
{
    ESP_LOGI(TAG, "Setting calibration parameter: %s = %s", parameter, value);
    // Hier könnte man MQTT Nachrichten für spezifische Parameter senden
    if (calibration_callback != NULL) {
        calibration_callback(parameter, value);
    }
}