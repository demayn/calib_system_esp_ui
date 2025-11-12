#include "ui/screens.h"
#include "ui/ui.h"
#include "esp_log.h"
#include "string.h"
#include "message_router.h"
#include "error_handler.h"
#include "positioning.h"  
#include "message_bus.h"

static const char *TAG = "ui_events";

static void ui_message_handler(const message_t* msg)
{
    switch(msg->type) {
        case MSG_POSITIONING_ISTWERT:
            ESP_LOGI(TAG, "UI: Received istwert update: %s", msg->data);
            if (objects.positionierung_istwert != NULL) {
                lv_label_set_text(objects.positionierung_istwert, msg->data);
                ESP_LOGI(TAG, "UI: Istwert updated to: %s", msg->data);
            } else {
                ESP_LOGE(TAG, "UI: positionierung_istwert is NULL!");
            }
            break;
            
        case MSG_CALIBRATION_STATUS:
            ESP_LOGI(TAG, "UI: Calibration status: %s", msg->data);
            // Hier später Kalibrierungs-UI updaten
            break;
            
        case MSG_SETTINGS_UPDATE:
            ESP_LOGI(TAG, "UI: Settings update: %s", msg->data);
            // Hier später Settings-UI updaten
            break;
            
        default:
            ESP_LOGW(TAG, "UI: Unknown message type: %d", msg->type);
            break;
    }
}



// Vereinfachter Button Handler
static void button_event_handler(lv_event_t * e) {
    lv_obj_t * btn = lv_event_get_target(e);
    
    // Hauptbildschirm Buttons
    if (btn == objects.positionierung) {
        ESP_LOGI(TAG, "Positionierung button pressed");
        loadScreen(SCREEN_ID_SCREEN_POSITIONING);
    }
    else if (btn == objects.kalibrierung) {
        ESP_LOGI(TAG, "Kalibrierung button pressed");
        loadScreen(SCREEN_ID_SCREEN_CALIBRATION);
    }
    else if (btn == objects.settings) {
        ESP_LOGI(TAG, "Settings button pressed");
        loadScreen(SCREEN_ID_SCREEN_SETTING);
    }
    else if (btn == objects.manuell_1) {  
        ESP_LOGI(TAG, "Help button pressed");
        loadScreen(SCREEN_ID_SCREEN_HELP);
    }

    // Navigation Buttons
    else if (btn == objects.button_back || 
             btn == objects.calibration_back || 
             btn == objects.setting_back || 
             btn == objects.help_back) {
        ESP_LOGI(TAG, "Back button pressed");
        loadScreen(SCREEN_ID_SCREEN_MAIN);
    }

    // Modul-spezifische Actions
    else if (btn == objects.positionierung_start) {
        ESP_LOGI(TAG, "Positioning Start button pressed");
        positioning_start();  // Einzige direkte Abhängigkeit!
    }
}

static void button_matrix_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
    
    if(btn_id == LV_BTNMATRIX_BTN_NONE) return;
    
    const char * txt = lv_btnmatrix_get_btn_text(obj, btn_id);
    ESP_LOGI(TAG, "Button matrix pressed: %s", txt);
    
    if(strcmp(txt, "1") == 0) {
        ESP_LOGI(TAG, "1 gedrückt");
    }
    else if(strcmp(txt, "2") == 0) {
        ESP_LOGI(TAG, "2 gedrückt");
    }
    else if(strcmp(txt, "3") == 0) {
        ESP_LOGI(TAG, "3 gedrückt");
    }
    else if(strcmp(txt, "4") == 0) {
        ESP_LOGI(TAG, "4 gedrückt");
    }
    else if(strcmp(txt, "5") == 0) {
        ESP_LOGI(TAG, "5 gedrückt");
    }
    else if(strcmp(txt, "6") == 0) {
        ESP_LOGI(TAG, "6 gedrückt");
    }
    else if(strcmp(txt, "7") == 0) {
        ESP_LOGI(TAG, "7 gedrückt");
    }
    else if(strcmp(txt, "8") == 0) {
        ESP_LOGI(TAG, "8 gedrückt");
    }
    else if(strcmp(txt, "9") == 0) {
        ESP_LOGI(TAG, "9 gedrückt");
    }
    else if(strcmp(txt, "0") == 0) {
        ESP_LOGI(TAG, "0 gedrückt");
    }
    else if(strcmp(txt, "+") == 0) {
        ESP_LOGI(TAG, "+ gedrückt");
    }
    else if(strcmp(txt, "-") == 0) {
        ESP_LOGI(TAG, "- gedrückt");
    }
}


void ui_handle_mqtt_message(const char* topic, const char* data) {
    ESP_LOGI(TAG, "UI received MQTT message");
    message_router_handle(topic, data);
}

void ui_events_init(void) {
    
    message_bus_subscribe(MSG_POSITIONING_ISTWERT, ui_message_handler);
    message_bus_subscribe(MSG_CALIBRATION_STATUS, ui_message_handler);
    message_bus_subscribe(MSG_SETTINGS_UPDATE, ui_message_handler);
    ESP_LOGI(TAG, "UI subscribed to message bus");
    
    // Nur reine UI-Event-Registrierung
    lv_obj_add_event_cb(objects.positionierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.kalibrierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.settings, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.manuell_1, button_event_handler, LV_EVENT_CLICKED, NULL);
    
    lv_obj_add_event_cb(objects.positionierung_start, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.button_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.positionierung_btnmatrix, button_matrix_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.calibration_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.setting_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.help_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    
    ESP_LOGI(TAG, "UI events initialized");
}


