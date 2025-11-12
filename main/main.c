#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_err.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "error_handler.h"  

// UI einbinden
#include "ui_events.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "wifi_controller.h"
#include "mqtt_controller.h"
// Module einbinden
#include "calibration.h"
#include "message_bus.h"
#include "settings.h"
#include "help.h"
#include "positioning.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing...");
    
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Error Handler initialisieren
    error_handler_init(); 


    // WiFi initialisieren 
    ESP_LOGI(TAG, "Initializing WiFi...");
    wifi_init_sta();

    // MQTT initialisieren
    ESP_LOGI(TAG, "Initializing MQTT...");
    mqtt_app_start();


    // Display initialisieren
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = true,
        },
    };
    
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();
    ESP_LOGI(TAG, "Display initialized");

    // LVGL Lock nehmen
    bsp_display_lock(0);

    
    // Message Bus initialisieren
    message_bus_init();


    // Ihre UI initialisieren
    lv_disp_set_rotation(lv_disp_get_default(), LV_DISP_ROTATION_270);
    ui_init();
    ui_events_init();
    
    // Module separat initialisieren
    positioning_init();
    calibration_init(); 
    settings_init();
    help_init();

    // Hauptscreen laden
    loadScreen(SCREEN_ID_SCREEN_MAIN);
    ESP_LOGI(TAG, "UI loaded");

    // LVGL Lock freigeben
    bsp_display_unlock();

    // Hauptloop
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        
        // UI Tick aufrufen (falls benötigt)
        bsp_display_lock(0);
        ui_tick();
        mqtt_process_ui_updates();
        bsp_display_unlock();
    }
}