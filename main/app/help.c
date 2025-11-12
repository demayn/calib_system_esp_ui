#include "help.h"
#include "esp_log.h"
#include "string.h"

static const char *TAG = "help";
static int current_page = 0;

void help_init(void) {
    ESP_LOGI(TAG, "Help module initialized");
    current_page = 0;
}

void help_handle_message(const char* topic, const char* data) {
    ESP_LOGI(TAG, "Handling MQTT message - Topic: %s, Data: %s", topic, data);
    // Help kann später auch Messages verarbeiten
}

void help_show_page(int page) {
    ESP_LOGI(TAG, "Showing help page: %d", page);
    current_page = page;
}