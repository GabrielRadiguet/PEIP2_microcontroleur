/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "LM75B.h"
#include "C12832.h"

AnalogIn pot1(p19);
AnalogIn pot2(p20);

LM75BD term(p28, p27);

DigitalOut led(LED1);

void ResetLeds(){
    for(int i = 0; i < 4; i++) leds[i] = 0;
}

void DisplayIntLeds(int i){
    int j = 3;
    while(j >= 0){
        leds[j] = (i & 1);
        i >>= 1;
        j--;
    }
}

int main()
{
    // Initialise the digital pin LED1 as an output
    ResetLeds();

    int i = 0;
    while (true) {
        i = ++i % 16;

        DisplayIntLeds(i);

        wait_us(500000);
    }
}
