set(LV_DEMO_DIR ../managed_components/lvgl__lvgl/demos)
file(GLOB_RECURSE LV_DEMOS_SOURCES ${LV_DEMO_DIR}/*.c)

# UI Dateien hinzufügen
set(UI_SOURCES
    ui/screens.c
    ui/ui.c
    ui/images.c
    ui/styles.c
    ui_events.c
)

# WiFi Controller
set(CONTROLLER_SOURCES
    wifi_controller.c
    mqtt_controller.c
)

#Buissness Logic
set(APP_SOURCES
    app/positioning.c
)

idf_component_register(
    SRCS main.c ${UI_SOURCES} ${APP_SOURCES} ${CONTROLLER_SOURCES} ${LV_DEMOS_SOURCES}
    INCLUDE_DIRS . ui app ${LV_DEMO_DIR}
)

idf_component_get_property(LVGL_LIB lvgl__lvgl COMPONENT_LIB)
target_compile_options(
    ${LVGL_LIB} 
    PRIVATE
        -DLV_LVGL_H_INCLUDE_SIMPLE
        -DLV_USE_DEMO_MUSIC
)