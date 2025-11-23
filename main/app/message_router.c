#include "message_router.h"
#include "esp_log.h"
#include "string.h"
#include "positioning.h"
#include "calibration.h"
#include "settings.h"
#include "help.h"
#include "mqtt_topics.h"

static const char *TAG = "message_router";

void message_router_handle(const char* topic, const char* data)
{
    ESP_LOGI(TAG, "Routing MQTT message - Topic: %s, Data: %s", topic, data); 
    // Delegiere an entsprechende Module basierend auf Topic
    // Hier können je nach Anwendungsfall auch grundsätzlich andere Routing-Strategien angewendet werden
    if (strstr(topic, "positionierung") != NULL) {
        positioning_handle_message(topic, data);
    }
    else {
        help_handle_message(topic, data);
    }
}