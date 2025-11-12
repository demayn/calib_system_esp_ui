#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *screen_main;
    lv_obj_t *screen_positioning;
    lv_obj_t *screen_setting;
    lv_obj_t *screen_help;
    lv_obj_t *screen_calibration;
    lv_obj_t *kalibrierung;
    lv_obj_t *settings;
    lv_obj_t *positionierung;
    lv_obj_t *manuell_1;
    lv_obj_t *led_wifi;
    lv_obj_t *positionierung_start;
    lv_obj_t *positionierung_btnmatrix;
    lv_obj_t *button_back;
    lv_obj_t *positionierung_istwert;
    lv_obj_t *positionierung_not_used_istwert_label;
    lv_obj_t *setting_back;
    lv_obj_t *help_back;
    lv_obj_t *calibration_back;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SCREEN_MAIN = 1,
    SCREEN_ID_SCREEN_POSITIONING = 2,
    SCREEN_ID_SCREEN_SETTING = 3,
    SCREEN_ID_SCREEN_HELP = 4,
    SCREEN_ID_SCREEN_CALIBRATION = 5,
};

void create_screen_screen_main();
void tick_screen_screen_main();

void create_screen_screen_positioning();
void tick_screen_screen_positioning();

void create_screen_screen_setting();
void tick_screen_screen_setting();

void create_screen_screen_help();
void tick_screen_screen_help();

void create_screen_screen_calibration();
void tick_screen_screen_calibration();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/