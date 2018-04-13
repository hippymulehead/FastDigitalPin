#include <FastDigitalPin.h>

//Setup a digital pin for use
FastDigitalPin led1(13);

void setup() {
    // Set the pin's mode same as normal just using a method
    led1.pinMode(OUTPUT);
}

void loop() {
    // write to the pin using the state of the last write or read
    led1.digitalWrite(!led1.value());
    delay(100);
}
