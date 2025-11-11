#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "freertos/event_groups.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Event Group Bits */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/**
 * @brief Initialisiert und startet WiFi im Station-Mode
 */
void wifi_init_sta(void);

/**
 * @brief Gibt den WiFi Event Group Handle zurück
 */
EventGroupHandle_t wifi_get_event_group(void);

/**
 * @brief Prüft ob WiFi verbunden ist
 */
bool wifi_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_CONTROLLER_H */