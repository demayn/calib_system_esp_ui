#ifndef CALIBRATION_H
#define CALIBRATION_H

#ifdef __cplusplus
extern "C" {
#endif

void calibration_init(void);
void calibration_handle_message(const char* topic, const char* data);
void calibration_start(void);
void calibration_set_parameter(const char* parameter, const char* value);

#ifdef __cplusplus
}
#endif

#endif