#include "ui/screens.h"
#include "ui/ui.h"
#include "esp_log.h"

static const char *TAG = "ui_events";

// Event Callback für Buttons
static void button_event_handler(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    
    if (btn == objects.positionierung) {
        ESP_LOGI(TAG, "Positionierung button pressed");
        loadScreen(SCREEN_ID_POSITIONING);
    }
    else if (btn == objects.manuell) {
        ESP_LOGI(TAG, "Manuell button pressed");
        // Deine Aktion hier
    }
    else if (btn == objects.kalibrierung) {
        ESP_LOGI(TAG, "Kalibrierung button pressed");
        // Deine Aktion hier
    }
    else if (btn == objects.settings) {
        ESP_LOGI(TAG, "Settings button pressed");
        // Deine Aktion hier
    }
    else if (btn == objects.manuell_1) {  // Help button
        ESP_LOGI(TAG, "Help button pressed");
        // Deine Aktion hier
    }
    else if (btn == objects.positionierung_start) {
        ESP_LOGI(TAG, "Start button pressed");
        // Deine Aktion hier
    }
}

// Events registrieren
void ui_events_init(void)
{
    // Main Screen Buttons
    lv_obj_add_event_cb(objects.positionierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.manuell, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.kalibrierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.settings, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.manuell_1, button_event_handler, LV_EVENT_CLICKED, NULL);
    
    // Positioning Screen Buttons
    lv_obj_add_event_cb(objects.positionierung_start, button_event_handler, LV_EVENT_CLICKED, NULL);
}