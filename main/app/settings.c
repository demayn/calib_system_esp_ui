#include "settings.h"
#include "esp_log.h"
#include "string.h"
#include "mqtt_controller.h"
#include "mqtt_topics.h"

static const char *TAG = "settings";
static settings_callback_t settings_callback = NULL;

void settings_init(settings_callback_t callback)
{
    settings_callback = callback;
    ESP_LOGI(TAG, "Settings module initialized");
}

void settings_handle_mqtt_message(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);

    if (strcmp(topic, TOPIC_DATA_SETTINGS_UPDATE) == 0 && settings_callback != NULL) {
        settings_callback("update", data);
    }
}

void settings_save_config(void)
{
    ESP_LOGI(TAG, "Saving settings");
    // Kann später mit NVS implementiert werden
}

void settings_load_config(void)
{
    ESP_LOGI(TAG, "Loading settings");
    // Kann später mit NVS implementiert werden
}

void settings_set_value(const char* key, const char* value)
{
    ESP_LOGI(TAG, "Setting %s = %s", key, value);
    
    if (settings_callback != NULL) {
        settings_callback(key, value);
    }
}