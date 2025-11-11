#include "positioning.h"
#include "esp_log.h"
#include "string.h"
#include "mqtt_controller.h"
#include "mqtt_topics.h"
#include "error_handler.h"


static const char *TAG = "positioning";
static positioning_istwert_callback_t istwert_callback = NULL;

void positioning_init(positioning_istwert_callback_t callback)
{
    istwert_callback = callback;
    ESP_LOGI(TAG, "Positioning module initialized");
}

void positioning_handle_mqtt_message(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);

    if (strcmp(topic, TOPIC_DATA_ISTWERT) == 0 && istwert_callback != NULL) {
        ESP_LOGI(TAG, "Updating istwert with: %s", data);
        istwert_callback(data);
    }
}

void positioning_start(void)
{
    if (!mqtt_is_connected()) {
        error_handler_report(ERROR_MQTT_NOT_CONNECTED, "positioning_start");
        return;
    }
    ESP_LOGI(TAG, "Start");
    mqtt_publish_message(TOPIC_CMD_POSITIONING_START, "1");
}

/*
void positioning_stop(void)
{
    ESP_LOGI(TAG, "Stopping positioning");
    mqtt_publish_message(TOPIC_CMD_POSITIONING_STOP, "0");
}
*/