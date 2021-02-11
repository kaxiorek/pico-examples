#ifndef DTH11_H_
#define DTH11_H_
#include "pico/stdlib.h"


typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void initDth();
bool read_from_dht(dht_reading *result);

#endif  // DTH11_H_
