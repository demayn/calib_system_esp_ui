#include "mqtt_controller.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "freertos/queue.h"
#include "string.h"
#include "mqtt_topics.h"

static const char *TAG = "mqtt_controller";

static esp_mqtt_client_handle_t client = NULL;
static bool mqtt_connected = false;

// Queue für UI Updates
typedef struct {
    char topic[64];
    char data[256];
} mqtt_ui_update_t;

static QueueHandle_t ui_update_queue = NULL;

// MQTT Event Handler
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    
    switch (event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT Connected");
            mqtt_connected = true;
            
            // Subscribe to ALL data topics
            esp_mqtt_client_subscribe(client, TOPIC_DATA_ISTWERT, 0);
            esp_mqtt_client_subscribe(client, TOPIC_DATA_CALIBRATION_STATUS, 0);

            ESP_LOGI(TAG, "Subscribed to all data topics");
            break;
            
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT Disconnected");
            mqtt_connected = false;
            break;
            
        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "MQTT Error");
            mqtt_connected = false;
            break;
            
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT Data received, topic: %.*s, data: %.*s", 
                    event->topic_len, event->topic,
                    event->data_len, event->data);
            
            // UI Update in Queue stellen (statt direkt LVGL aufzurufen)
            if (ui_update_queue != NULL) {
                mqtt_ui_update_t update;
                snprintf(update.topic, sizeof(update.topic), "%.*s", event->topic_len, event->topic);
                snprintf(update.data, sizeof(update.data), "%.*s", event->data_len, event->data);
                
                if (xQueueSend(ui_update_queue, &update, 0) != pdTRUE) {
                    ESP_LOGW(TAG, "UI update queue full, dropping message");
                }
            }
            break;
            
        default:
            (void)event;  // Mark as unused to avoid warning
            break;
    }
}

void mqtt_app_start(void)
{
    ESP_LOGI(TAG, "Starting MQTT Client");
    
    // Queue für UI Updates erstellen
    ui_update_queue = xQueueCreate(10, sizeof(mqtt_ui_update_t));
    if (ui_update_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create UI update queue");
    }
    
    // MQTT Konfiguration
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.137.1",  // Deine Broker IP
    };
    
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void mqtt_publish_message(const char* topic, const char* data)
{
    if (mqtt_connected && client) {
        int msg_id = esp_mqtt_client_publish(client, topic, data, 0, 1, 0);
        ESP_LOGI(TAG, "MQTT publish: msg_id=%d, topic=%s, data=%s", msg_id, topic, data);
    } else {
        ESP_LOGW(TAG, "MQTT not connected, cannot publish to topic=%s", topic);
    }
}

bool mqtt_is_connected(void)
{
    return mqtt_connected;
}

void mqtt_process_ui_updates(void)
{
    if (ui_update_queue == NULL) return;
    
    mqtt_ui_update_t update;
    while (xQueueReceive(ui_update_queue, &update, 0) == pdTRUE) {
        ESP_LOGI(TAG, "Processing UI update - Topic: %s, Data: %s", update.topic, update.data);
        
        // Hier können wir jetzt sicher LVGL aufrufen, da wir im Haupttask sind
        // Diese Funktion muss von ui_events.c bereitgestellt werden
        extern void ui_handle_mqtt_message(const char* topic, const char* data);
        ui_handle_mqtt_message(update.topic, update.data);
    }
}