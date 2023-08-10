#ifndef GATT_SERVER_H_INCLUDED
#define GATT_SERVER_H_INCLUDED

#include <stdint.h>

void gatt_server_init();
_Bool gatt_server_is_notify_enabled();
void gatt_server_send_notify(uint8_t *data, uint16_t len);

#endif
