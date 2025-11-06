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
    {
        lv_obj_t *parent_obj = obj;
        {
            // kalibrierung
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.kalibrierung = obj;
            lv_obj_set_pos(obj, 456, 611);
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
            lv_obj_set_pos(obj, 68, 476);
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
            lv_obj_set_pos(obj, 843, 476);
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
            lv_obj_set_pos(obj, 456, 476);
            lv_obj_set_size(obj, 370, 117);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // help
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.help = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Hilfe");
                }
            }
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
    {
        lv_obj_t *parent_obj = obj;
        {
            // positionierung_start
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.positionierung_start = obj;
            lv_obj_set_pos(obj, 817, 165);
            lv_obj_set_size(obj, 100, 70);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // positionierung_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.positionierung_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Start");
                }
            }
        }
        {
            // button_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button_back = obj;
            lv_obj_set_pos(obj, 927, 669);
            lv_obj_set_size(obj, 256, 82);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button_back_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            // positionierung_spinnbox
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.positionierung_spinnbox = obj;
            lv_obj_set_pos(obj, 363, 165);
            lv_obj_set_size(obj, 410, 70);
            lv_spinbox_set_digit_format(obj, 5, 0);
            lv_spinbox_set_range(obj, -99999, 99999);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
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
        
    }
    
    tick_screen_screen_positioning();
}

void tick_screen_screen_positioning() {
}

void create_screen_screen_settinga() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_settinga = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    
    tick_screen_screen_settinga();
}

void tick_screen_screen_settinga() {
}

void create_screen_screen_help() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_help = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    
    tick_screen_screen_help();
}

void tick_screen_screen_help() {
}

void create_screen_screen_calibration() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.screen_calibration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1280, 800);
    
    tick_screen_screen_calibration();
}

void tick_screen_screen_calibration() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_screen_main,
    tick_screen_screen_positioning,
    tick_screen_screen_settinga,
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
    create_screen_screen_settinga();
    create_screen_screen_help();
    create_screen_screen_calibration();
}
