#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

#include "74HC565.h"
#include "dth11.h"

const uint EXTERNAL_LED_PIN = 14;
const uint BUTTON_PIN = 13;

static int binaryCounter = 0;

bool binaryCouterCallback(struct repeating_timer *t)
{
        sendByte(binaryCounter);
        binaryCounter++;
        if (binaryCounter == 256) binaryCounter = 0;
        return true;
}

int main() {
    stdio_init_all();
    gpio_init(EXTERNAL_LED_PIN);
    gpio_init(BUTTON_PIN);

    init74HC565Pins();
    initDth();

    gpio_set_dir(EXTERNAL_LED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // struct repeating_timer timer;
    // add_repeating_timer_ms(100, binaryCouterCallback, NULL, &timer);
    
    dht_reading reading;
    testAllDiodesAndByteSending();
        
    gpio_put(EXTERNAL_LED_PIN, 0);
    for (int i = 0; i < 8; ++i)
    {
        sendBit(0);
        latch();
        sleep_ms(100);
    }

    while (1) 
    {
        if (gpio_get(BUTTON_PIN) == 1) gpio_put(EXTERNAL_LED_PIN, 1);
        else gpio_put(EXTERNAL_LED_PIN, 0);

        bool readSuccessful = read_from_dht(&reading);
        if(readSuccessful)
        {
            gpio_put(25, 1);
            uint8_t temp = reading.temp_celsius;
            uint8_t humi = reading.humidity;

            printf("temp %d humi %d\n", temp, humi);
            gpio_put(EXTERNAL_LED_PIN, 1);
            sendByte(temp);
            sleep_ms(10000);
            gpio_put(EXTERNAL_LED_PIN, 0);
            sendByte(humi);
            sleep_ms(10000);
            gpio_put(25, 0);
        }
        else
        {
            uint8_t temp = reading.temp_celsius * 10;
            sendByte(1+4+16+64);
            sleep_ms(1000);
            sendByte(2+8+32+128);
            sleep_ms(1000);
            sendByte(0);
        }
    }
}
