#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MSG_POSITIONING_ISTWERT,
    MSG_CALIBRATION_STATUS,
    MSG_SETTINGS_UPDATE,
    MSG_POSITIONING_START,
    MSG_CALIBRATION_START
} message_type_t;

typedef struct {
    message_type_t type;
    const char* topic;
    const char* data;
} message_t;

typedef void (*message_handler_t)(const message_t* message);

void message_bus_init(void);
void message_bus_subscribe(message_type_t type, message_handler_t handler);
void message_bus_publish(const message_t* message);

#ifdef __cplusplus
}
#endif

#endif