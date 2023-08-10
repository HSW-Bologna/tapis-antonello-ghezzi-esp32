#ifndef PROXIMITY_H_INCLUDED
#define PROXIMITY_H_INCLUDED

#include <stdint.h>

void proximity_init();
void proximity_manage();
uint32_t proximity_get_counter();

#endif
