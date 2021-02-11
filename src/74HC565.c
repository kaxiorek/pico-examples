#include "74HC565.h"

#include <pico/stdlib.h>

const uint DATA_PIN = 0;
const uint SHIFT_OUTPUT_PIN = 1;
const uint CLOCK_PIN = 2;
const uint SPEED_74HC565 = 2; // According to datasheet it should be atleast 1us

void init74HC565Pins()
{
    gpio_init(DATA_PIN);
    gpio_init(SHIFT_OUTPUT_PIN);
    gpio_init(CLOCK_PIN);

    gpio_set_dir(DATA_PIN, GPIO_OUT);
    gpio_set_dir(SHIFT_OUTPUT_PIN, GPIO_OUT);
    gpio_set_dir(CLOCK_PIN, GPIO_OUT);
}


void latch()
{
    gpio_put(SHIFT_OUTPUT_PIN, 1);
    sleep_us(SPEED_74HC565);
    gpio_put(SHIFT_OUTPUT_PIN, 0);
}

void sendBit(bool bit)
{
    gpio_put(DATA_PIN, bit);
    sleep_us(SPEED_74HC565);
    gpio_put(CLOCK_PIN, 1);
    sleep_us(SPEED_74HC565);
    gpio_put(CLOCK_PIN, 0);
    sleep_us(SPEED_74HC565);
    gpio_put(DATA_PIN, 0);
}

void sendByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        bool bit = byte & 0x80;
        byte = byte << 1;
        sendBit(bit);
    }
    latch();
}

void testAllDiodesAndByteSending()
{
    for (short i = 1; i <= 255; i++)
    {
        sendByte(i);
        sleep_ms(20);
    }
    sleep_ms(500);
}