#ifndef _74HC565_H_
#define _74HC565_H_

#include <pico/stdlib.h>

void init74HC565Pins();
void latch();
void sendBit(bool bit);
void sendByte(uint8_t byte);
void testAllDiodesAndByteSending();

#endif  // _74HC565_H_
