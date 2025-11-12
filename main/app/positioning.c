#include "positioning.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"
#include "error_handler.h"
#include "mqtt_controller.h"

static const char *TAG = "positioning";

static void positioning_message_handler(const message_t* msg)
{
    switch(msg->type) {
        case MSG_POSITIONING_ISTWERT:
            ESP_LOGI(TAG, "Updating istwert with: %s", msg->data);
            // UI Update über Message Bus statt direktem Callback
            break;
        default:
            break;
    }
}

void positioning_init(void)
{
    message_bus_subscribe(MSG_POSITIONING_ISTWERT, positioning_message_handler);
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