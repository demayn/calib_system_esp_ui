#include "positioning.h"
#include "esp_log.h"
#include "string.h"
#include "message_bus.h"
#include "mqtt_topics.h"
#include "error_handler.h"
#include "mqtt_controller.h"

static const char *TAG = "positioning";

// Sollwert Buffer
static char current_sollwert[32] = "";

void positioning_init(void)
{
    strcpy(current_sollwert, "");
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

void positioning_set_sollwert(const char* sollwert)
{
    if (sollwert == NULL) return;
    
    strncpy(current_sollwert, sollwert, sizeof(current_sollwert) - 1);
    current_sollwert[sizeof(current_sollwert) - 1] = '\0';
    
    ESP_LOGI(TAG, "Sollwert gesetzt: %s", current_sollwert);
}

void positioning_clear_sollwert(void)
{
    strcpy(current_sollwert, "");
    ESP_LOGI(TAG, "Sollwert gelöscht");
}

void positioning_send_sollwert(void)
{
    if (!mqtt_is_connected()) {
        error_handler_report(ERROR_MQTT_NOT_CONNECTED, "positioning_send_sollwert");
        return;
    }
    
    if (strlen(current_sollwert) == 0) {
        ESP_LOGW(TAG, "Kein Sollwert zum Senden vorhanden");
        return;
    }
    
    ESP_LOGI(TAG, "Sende Sollwert: %s", current_sollwert);
    mqtt_publish_message("positionierung/sollwert", current_sollwert);
    
    // Sollwert zurücksetzen nach dem Senden
    strcpy(current_sollwert, "");
}

const char* positioning_get_current_sollwert(void)
{
    return current_sollwert;
}