#include "settings.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"

static const char *TAG = "settings";

static void settings_message_handler(const message_t* msg) {
    switch(msg->type) {
        case MSG_SETTINGS_UPDATE:
            ESP_LOGI(TAG, "Settings update: %s = %s", msg->topic, msg->data);
            // Hier später UI Updates über Message Bus
            break;
        default:
            break;
    }
}

void settings_init(void) {
    message_bus_subscribe(MSG_SETTINGS_UPDATE, settings_message_handler);
    ESP_LOGI(TAG, "Settings module initialized");
}

void settings_handle_message(const char* topic, const char* data) {
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);

    if (strcmp(topic, TOPIC_DATA_SETTINGS_UPDATE) == 0) {
        message_t msg = {
            .type = MSG_SETTINGS_UPDATE,
            .topic = topic,
            .data = data
        };
        message_bus_publish(&msg);
    }
}

void settings_save_config(void) {
    ESP_LOGI(TAG, "Saving settings");
}

void settings_load_config(void) {
    ESP_LOGI(TAG, "Loading settings");
}

void settings_set_value(const char* key, const char* value) {
    ESP_LOGI(TAG, "Setting %s = %s", key, value);
    // Hier später über Message Bus arbeiten
}