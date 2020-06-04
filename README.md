# About

Interrupt based Arduino library for reading PPM signals. Developed for use with the OrangeRx R617XL radio frequency receiver. Tested extensively with the Arduino Nano. Should work with other ATmega328 based boards.

# Installation

1. Download and extract the files. 
2. Rename the directory to ```ppmHandler```. 
3. Make sure the files above are in the first level of ```ppmHandler```. 
4. Move ```ppmHandler``` to ```{your path}/Arduino/libraries```.
5. Restart Arduino IDE. ```Sketch > Include Library``` ppmHandler should be listed under contributed libraries 

# Example

After installing you can open the example in the Arduino IDE ```File > Examples > ppmHandler > ppmHandler```

```cpp
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
    
    // Use handler.get(channel number) to get the pulse width of a ppm channel. 
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
```

# Configuration

By default the handler is configured to read ppm signals with 6 channels. Additionally the handler constrains the output of the get(). These settings can be adjusted by the macro definitions at the top of ```ppmhandler.h```.