#include <FastDigitalPin.h>

FastDigitalPin led1(12);
FastDigitalPin button(5);

void setup() {
    led1.pinMode(OUTPUT);
    button.pinMode(INPUT);
}

void loop() {
    // Write the value of the button to the LED.
    led1.digitalWrite(button.digitalRead());
}
