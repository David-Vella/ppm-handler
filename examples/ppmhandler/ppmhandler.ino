/*
 * Simple example using the ppmHandler library
 * 
 * Written by David Vella, Apr 2020
 */ 

#include <ppmHandler.h>

// Arduino pin connected to ppm signal
// NOTE: this pin must support interrupts. 
// On ATmega328 based boards these should be pins 2 and 3
// Check the data sheet for your specific board
const int pin = 2;

// Create and instance of the ppmHandler class
ppmHandler ppm;

void setup()
{
    // Associate and instance of the ppmHandler with a physical pin
    assignPpmHandlerToPin(ppm, pin);

    Serial.begin(9600);
}

void loop()
{
    // Must be called at least once after assigning a handler to a pin.
    // Recommended to include in loop for noise immunity 
    ppm.sync();
    
    // Use to handler.get(channel number) to get the pulse width a ppm channel. 
    // The channel numbers are integers 1 - 6
    Serial.print(ppm.get(1));
    Serial.print(' ');
    Serial.print(ppm.get(2));
    Serial.print(' ');
    Serial.print(ppm.get(3));
    Serial.print(' ');
    Serial.print(ppm.get(4));
    Serial.print(' ');
    Serial.print(ppm.get(5));
    Serial.print(' ');
    Serial.println(ppm.get(6));

    delay(1000);
}