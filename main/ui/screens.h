#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *positioning;
    lv_obj_t *kalibrierung;
    lv_obj_t *manuell;
    lv_obj_t *settings;
    lv_obj_t *positionierung;
    lv_obj_t *manuell_1;
    lv_obj_t *help;
    lv_obj_t *positionierung_start;
    lv_obj_t *positionierung_button_label;
    lv_obj_t *positionierung_spinnbox;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_POSITIONING = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_positioning();
void tick_screen_positioning();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/