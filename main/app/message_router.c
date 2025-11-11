#include "message_router.h"
#include "esp_log.h"
#include "string.h"
#include "positioning.h"
#include "calibration.h"
#include "settings.h"
#include "help.h"

static const char *TAG = "message_router";

void message_router_handle(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "MQTT Message Received");
    ESP_LOGI(TAG, "Topic: %s", topic);
    ESP_LOGI(TAG, "Data: %s", data);
    
    // Einfach alles an alle Module weiterleiten (v1.0)
    
    positioning_handle_mqtt_message(topic, data);
    calibration_handle_mqtt_message(topic, data);
    settings_handle_mqtt_message(topic, data);
    help_handle_mqtt_message(topic, data);
    
    ESP_LOGI(TAG, "Routed to all modules");
}