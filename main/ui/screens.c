#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    lv_obj_set_style_transform_angle(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // kalibrierung
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.kalibrierung = obj;
            lv_obj_set_pos(obj, 647, 611);
            lv_obj_set_size(obj, 370, 117);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Kalibrierung");
                }
            }
        }
        {
            // settings
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings = obj;
            lv_obj_set_pos(obj, 259, 476);
            lv_obj_set_size(obj, 370, 117);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Einstellungen");
                }
            }
        }
        {
            // positionierung
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.positionierung = obj;
            lv_obj_set_pos(obj, 259, 611);
            lv_obj_set_size(obj, 370, 117);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Positionierung");
                }
            }
        }
        {
            // manuell_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.manuell_1 = obj;
            lv_obj_set_pos(obj, 647, 476);
            lv_obj_set_size(obj, 370, 117);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Hilfe");
                }
            }
        }
        {
            // led_wifi
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_wifi = obj;
            lv_obj_set_pos(obj, 1203, 36);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1204, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Wifi");
        }
    }
    
    tick_screen_screen_main();
}

void tick_screen_screen_main() {
}

void create_screen_screen_positioning() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_positioning = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // positionierung_start
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.positionierung_start = obj;
            lv_obj_set_pos(obj, 773, 205);
            lv_obj_set_size(obj, 100, 70);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Start");
                }
            }
        }
        {
            // positionierung_btnmatrix
            lv_obj_t *obj = lv_btnmatrix_create(parent_obj);
            objects.positionierung_btnmatrix = obj;
            lv_obj_set_pos(obj, 363, 275);
            lv_obj_set_size(obj, 410, 342);
            static const char *map[16] = {
                "7",
                "8",
                "9",
                "\n",
                "4",
                "5",
                "6",
                "\n",
                "1",
                "2",
                "3",
                "\n",
                "-",
                "0",
                "+",
                NULL,
            };
            lv_btnmatrix_set_map(obj, map);
        }
        {
            // button_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button_back = obj;
            lv_obj_set_pos(obj, 0, 700);
            lv_obj_set_size(obj, 250, 100);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff001bff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffc1788), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            // positionierung_istwert
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.positionierung_istwert = obj;
            lv_obj_set_pos(obj, 409, 169);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Istwert wird empfanegen...");
        }
    }
    
    tick_screen_screen_positioning();
}

void tick_screen_screen_positioning() {
}

void create_screen_screen_setting() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_setting = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // setting_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.setting_back = obj;
            lv_obj_set_pos(obj, 0, 700);
            lv_obj_set_size(obj, 250, 100);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
    }
    
    tick_screen_screen_setting();
}

void tick_screen_screen_setting() {
}

void create_screen_screen_help() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_help = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // help_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.help_back = obj;
            lv_obj_set_pos(obj, 0, 700);
            lv_obj_set_size(obj, 250, 100);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
    }
    
    tick_screen_screen_help();
}

void tick_screen_screen_help() {
}

void create_screen_screen_calibration() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_calibration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // calibration_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.calibration_back = obj;
            lv_obj_set_pos(obj, 0, 700);
            lv_obj_set_size(obj, 250, 100);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
    }
    
    tick_screen_screen_calibration();
}

void tick_screen_screen_calibration() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_screen_main,
    tick_screen_screen_positioning,
    tick_screen_screen_setting,
    tick_screen_screen_help,
    tick_screen_screen_calibration,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_screen_main();
    create_screen_screen_positioning();
    create_screen_screen_setting();
    create_screen_screen_help();
    create_screen_screen_calibration();
}
