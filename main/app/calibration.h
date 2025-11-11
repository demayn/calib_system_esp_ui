#ifndef CALIBRATION_H
#define CALIBRATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*calibration_callback_t)(const char* parameter, const char* value);

void calibration_init(calibration_callback_t callback);
void calibration_handle_mqtt_message(const char* topic, const char* data);
void calibration_start(void);
void calibration_stop(void);
void calibration_set_parameter(const char* parameter, const char* value);

#ifdef __cplusplus
}
#endif
#endif