#include "positioning.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"
#include "error_handler.h"
#include "mqtt_controller.h"

static const char *TAG = "positioning";

void positioning_init(void)
{
    ESP_LOGI(TAG, "Positioning module initialized");
}

void positioning_handle_message(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);

    if (strcmp(topic, TOPIC_DATA_ISTWERT) == 0) {
        message_t msg = {
            .type = MSG_POSITIONING_ISTWERT,
            .topic = topic,
            .data = data
        };
        message_bus_publish(&msg);
        ESP_LOGI(TAG, "Published istwert to message bus: %s", data);
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