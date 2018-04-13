FastDigitalPin

This is part of my rewritten fast GPIO libs.  This is FastDigitalPin.

// Create a new digital pin
FastDigitalPin led(12);
// Just takes the pin number

// Set the mode
led.PinMode(OUTPUT);

// Blink it
led.digitalWrite(led.value());
// Each pin has it's own state stored so no need to create an extra var to store state.

This uses my reworked digital IO code.  Has methods...
digitalWrite(pinNumber);
digitalWrite(value);
analogWrite(value);

The Arduino versions of the above do a LOT of the same code every time you use them just to figure out what register and port you're trying to write to.  Since this is based in C++, I moved all that code in to the initializer so when you write or read, it's direct to the port!