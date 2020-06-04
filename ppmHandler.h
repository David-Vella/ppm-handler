/*
 * Interrupt based Arduino library for reading PPM signals. Developed
 * for use with the OrangeRx R617XL radio frequency receiver.
 * 
 * Written by David Vella, Apr 2020
 */ 

#ifndef PPM_H
#define PPM_H

#include <Arduino.h>


// Upper bound on the return value of get() method
#define MAXIMUM_PPM_PULSEWIDTH 1700

// Lower bound on the return value of get() method
#define MINIMUM_PPM_PULSEWIDTH 700

// Used by sync() method to determine the synchronization pulse
#define MINIMUM_SYNC_PULSEWIDTH 10000

// Limits attempts made by sync() method to find the synchronization pulse
#define MAXIMUM_RESYNC_ATTEMPTS 5

#define RECEIVER_CHANNELS 6
#define PPM_DATA_ARRAY_SIZE (RECEIVER_CHANNELS + 1) * 2


class ppmHandler 
{
    public:
        ppmHandler();

        // Checks if the sync_ptr is pointing to the sync channel in the 
        // data array. If not, the data array is traversed until the 
        // sync channel is found. MAXIMUM_RESYNC_ATTEMPTS limits the 
        // number of array traversals.
        void sync();

        // Returns the pulsewidth of the corresponding receiver channel 
        // in milliseconds.
        uint16_t get(uint8_t chan);

        // Updates the data array. Called by interrupt routine
        void toggle();

    private:
        volatile uint16_t data[PPM_DATA_ARRAY_SIZE];

        volatile uint16_t* chan_ptr;
        volatile uint16_t* sync_ptr;

        volatile unsigned long timer;
};

// Associates an instance of the ppmDecoder class with a pin.
// Macro defined so compiler can deduce instance of ppmDecoder class
#define assignPpmHandlerToPin(handler, pin) \
    pinMode(pin, INPUT_PULLUP); \
    attachInterrupt( \
        digitalPinToInterrupt(pin), \
        [](void){ handler.toggle(); }, \
        CHANGE \
    );

// Disassociates an instance of the ppmDecoder class with a pin
#define removePpmHandlerFromPin(handler, pin) \
    detachInterrupt(pin);

#endif