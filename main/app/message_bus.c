#include "message_bus.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "message_bus";

#define MAX_SUBSCRIBERS 10

typedef struct {
    message_type_t type;
    message_handler_t handler;
} subscriber_t;

static subscriber_t subscribers[MAX_SUBSCRIBERS];
static int subscriber_count = 0;

void message_bus_init(void) {
    subscriber_count = 0;
    memset(subscribers, 0, sizeof(subscribers));
    ESP_LOGI(TAG, "Message bus initialized");
}

void message_bus_subscribe(message_type_t type, message_handler_t handler) {
    if (subscriber_count >= MAX_SUBSCRIBERS) {
        ESP_LOGE(TAG, "Cannot subscribe - max subscribers reached");
        return;
    }
    for (int i = 0; i < subscriber_count; i++) {
        if (subscribers[i].type == type && subscribers[i].handler == handler) {
            ESP_LOGW(TAG, "Already subscribed to message type %d", type);
            return;
        }
    }
    
    subscribers[subscriber_count].type = type;
    subscribers[subscriber_count].handler = handler;
    subscriber_count++;
    
    ESP_LOGI(TAG, "Subscribed to message type %d", type);
}

void message_bus_publish(const message_t* message) {
    ESP_LOGI(TAG, "Publishing message type %d (topic: %s)", message->type, message->topic);
    
    for (int i = 0; i < subscriber_count; i++) {
        if (subscribers[i].type == message->type) {
            ESP_LOGI(TAG, "Calling handler for subscriber %d", i);
            subscribers[i].handler(message);
        }
    }
    
    if (subscriber_count == 0) {
        ESP_LOGW(TAG, "No subscribers for message type %d", message->type);
    }
}

void message_bus_unsubscribe(message_type_t type, message_handler_t handler) {
    for (int i = 0; i < subscriber_count; i++) {
        if (subscribers[i].type == type && subscribers[i].handler == handler) {
            subscribers[i] = subscribers[subscriber_count - 1];
            subscriber_count--;
            ESP_LOGI(TAG, "Unsubscribed from message type %d", type);
            return;
        }
    }
    ESP_LOGW(TAG, "Handler not found for unsubscribe (type %d)", type);
}


void message_bus_create_and_publish(message_type_t type, const char* topic, const char* data) {
    message_t msg = { .type = type };
    
    if (topic != NULL) {
        strncpy(msg.topic, topic, sizeof(msg.topic) - 1);
        msg.topic[sizeof(msg.topic) - 1] = '\0';
    } else {
        msg.topic[0] = '\0';
    }
    
    if (data != NULL) {
        strncpy(msg.data, data, sizeof(msg.data) - 1);
        msg.data[sizeof(msg.data) - 1] = '\0';
    } else {
        msg.data[0] = '\0';
    }
    
    message_bus_publish(&msg);
}