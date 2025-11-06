#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_memory_utils.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"

// Deine UI einbinden
#include "ui/ui.h"
#include "ui/screens.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing...");
    
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

    lv_disp_set_rotation(lv_disp_get_default(), LV_DISP_ROTATION_270);
    // Deine UI initialisieren
    ui_init();

    // Events initialisieren
    extern void ui_events_init(void);
    ui_events_init();
    
    // Hauptscreen laden
    loadScreen(SCREEN_ID_MAIN);

    ESP_LOGI(TAG, "UI loaded");

    // LVGL Lock freigeben
    bsp_display_unlock();

    // Hauptloop
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        
        // UI Tick aufrufen (falls benötigt)
        bsp_display_lock(0);
        ui_tick();
        bsp_display_unlock();
    }
}