#include "calibration.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"

static const char *TAG = "calibration";

static void calibration_message_handler(const message_t* msg) {
    switch(msg->type) {
        case MSG_CALIBRATION_STATUS:
            ESP_LOGI(TAG, "Calibration status update: %s", msg->data);
            // Hier später UI Updates über Message Bus
            break;
        default:
            break;
    }
}

void calibration_init(void) {
    message_bus_subscribe(MSG_CALIBRATION_STATUS, calibration_message_handler);
    ESP_LOGI(TAG, "Calibration module initialized");
}

void calibration_handle_message(const char* topic, const char* data) {
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);
    
    if (strcmp(topic, TOPIC_DATA_CALIBRATION_STATUS) == 0) {
        message_t msg = {
            .type = MSG_CALIBRATION_STATUS,
            .topic = topic,
            .data = data
        };
        message_bus_publish(&msg);
    }
}

void calibration_start(void) {
    ESP_LOGI(TAG, "Starting calibration");
    // Hier später MQTT Message senden
}

void calibration_set_parameter(const char* parameter, const char* value) {
    ESP_LOGI(TAG, "Setting calibration parameter: %s = %s", parameter, value);
    // Hier später über Message Bus arbeiten
}