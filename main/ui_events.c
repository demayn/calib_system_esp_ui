#include "ui.h"
#include "esp_log.h"
#include "string.h"
#include "error_handler.h"
#include "positioning.h"  //für befehle
#include "message_bus.h" //für Ereignisse

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
            break;
            
        case MSG_SETTINGS_UPDATE:
            ESP_LOGI(TAG, "UI: Settings update: %s", msg->data);
            break;
            
        default:
            ESP_LOGW(TAG, "UI: Unknown message type: %d", msg->type);
            break;
    }
}

//Sollwert im UI aktualisieren
static void update_sollwert_display(void)
{
    if (objects.positioning_sollwert_eingabe != NULL) {
        const char* sollwert = positioning_get_current_sollwert();
        lv_label_set_text(objects.positioning_sollwert_eingabe, 
                         strlen(sollwert) > 0 ? sollwert : "eingeben...");
        ESP_LOGI(TAG, "Sollwert Display updated: %s", sollwert);
    }
}

static void button_matrix_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
    
    if(btn_id == LV_BTNMATRIX_BTN_NONE) return;
    
    const char * txt = lv_btnmatrix_get_btn_text(obj, btn_id);
    ESP_LOGI(TAG, "Button matrix pressed: %s", txt);
    
    // Nur Zahlen 0-9 verarbeiten, + und - ignorieren
    if(strcmp(txt, "0") == 0 || strcmp(txt, "1") == 0 || strcmp(txt, "2") == 0 ||
       strcmp(txt, "3") == 0 || strcmp(txt, "4") == 0 || strcmp(txt, "5") == 0 ||
       strcmp(txt, "6") == 0 || strcmp(txt, "7") == 0 || strcmp(txt, "8") == 0 ||
       strcmp(txt, "9") == 0) {
        
        // Aktuellen Sollwert holen und neue Zahl anhängen
        const char* current = positioning_get_current_sollwert();
        char new_sollwert[32];
        snprintf(new_sollwert, sizeof(new_sollwert), "%s%s", current, txt);
        
        // Sollwert setzen und Display aktualisieren
        positioning_set_sollwert(new_sollwert);
        update_sollwert_display();
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

        
    // Delete Button
    else if (btn == objects.positionierung_sollwert_delete) {
        ESP_LOGI(TAG, "Delete button pressed");
        positioning_clear_sollwert();
        update_sollwert_display();
    }
    // Send_x Button
    else if (btn == objects.positionierung_sollwert_send_x) {
        ESP_LOGI(TAG, "Send button pressed");
        positioning_send_sollwert_x();
        update_sollwert_display(); 
    }
    // Send_y Button
    else if (btn == objects.positionierung_sollwert_send_y) {
        ESP_LOGI(TAG, "Send Y button pressed");
        positioning_send_sollwert_y();
        update_sollwert_display(); 
    }
}

void ui_events_init(void) {
    
    message_bus_subscribe(MSG_POSITIONING_ISTWERT, ui_message_handler);
    message_bus_subscribe(MSG_CALIBRATION_STATUS, ui_message_handler);
    message_bus_subscribe(MSG_SETTINGS_UPDATE, ui_message_handler);
    ESP_LOGI(TAG, "UI subscribed to message bus");
    
    // Event Handler registrieren
    lv_obj_add_event_cb(objects.positionierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.kalibrierung, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.settings, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.manuell_1, button_event_handler, LV_EVENT_CLICKED, NULL);
    
    lv_obj_add_event_cb(objects.button_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.positionierung_btnmatrix, button_matrix_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.calibration_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.setting_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.help_back, button_event_handler, LV_EVENT_CLICKED, NULL);
    
    lv_obj_add_event_cb(objects.positionierung_sollwert_delete, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.positionierung_sollwert_send_x, button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.positionierung_sollwert_send_y, button_event_handler, LV_EVENT_CLICKED, NULL);
    ESP_LOGI(TAG, "UI events initialized");
}