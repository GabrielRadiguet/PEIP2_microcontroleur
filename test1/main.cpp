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

LM75B term(p28, p27);
C12832 LCD(p5, p7, p6, p8, p11);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

DigitalOut leds[4] = {led1, led2, led3, led4};

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

int patern[5] = {0, 1, 3, 7, 15};

int AnalogIn2Index(float v, int n){
    return (int)(v * n);
}

int main()
{
    float temp;
    float pot1v;
    float pot2v;

    while(true){
        temp = term.temp();
        pot1v = pot1.read();
        pot2v = pot2.read();

        LCD.locate(0, 0);
        LCD.printf("temp : %f", temp);

        LCD.locate(0, LCD.height()/3);
        LCD.printf("pot1 : %f %d", pot1v, AnalogIn2Index(pot1v, 5));

        LCD.locate(0, 2 * LCD.height()/3);
        LCD.printf("pot2 : %f", pot2v);

        DisplayIntLeds(patern[AnalogIn2Index(pot1v, 5)]);
    }
}
