#include <FastDigitalPin.h>

// Setup your digital pin
FastDigitalPin pwdled(9);

void setup() {
    // Set the pin's mode same as normal just using a method
    pwmled.pinMode(OUTPUT);
}

void loop() {
    // analogWrite through all the possible values.
    for (int i = 0; i < 256; i++) {
        pwmled.analogWrite(i);
        delay(10);
    }
    for (int i = 255; i >= 0; i--) {
        pwmled.analogWrite(i);
        delay(10);
    }
}
