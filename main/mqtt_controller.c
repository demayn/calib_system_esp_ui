#include "mqtt_controller.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "mqtt_controller";

static esp_mqtt_client_handle_t client = NULL;
static bool mqtt_connected = false;

// MQTT Event Handler
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    
    switch (event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT Connected");
            mqtt_connected = true;
            break;
            
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT Disconnected");
            mqtt_connected = false;
            break;
            
        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "MQTT Error");
            mqtt_connected = false;
            break;
            
        default:
            // Event-Variable wird nur in bestimmten Cases verwendet
            // Das ist okay - wir markieren sie als unused um die Warnung zu vermeiden
            (void)event;
            break;
    }
}

void mqtt_app_start(void)
{
    ESP_LOGI(TAG, "Starting MQTT Client");
    
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
        ESP_LOGI(TAG, "Sent publish: msg_id=%d, topic=%s, data=%s", msg_id, topic, data);
    } else {
        ESP_LOGW(TAG, "MQTT not connected, cannot publish to topic=%s", topic);
    }
}

bool mqtt_is_connected(void)
{
    return mqtt_connected;
}