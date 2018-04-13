#ifndef FASTDIGITALPIN_H
#define FASTDIGITALPIN_H
#include <Arduino.h>

class FastDigitalPin {
    public:
        FastDigitalPin(uint8_t pinNumber);
        virtual ~FastDigitalPin();
        void pinMode(uint8_t mode);
        void digitalWrite(uint8_t value);
        void analogWrite(uint8_t value);
        uint8_t digitalRead();
        uint8_t value() {return m_state;}
        uint8_t mode() {return m_mode;}

    protected:

    private:
        uint8_t m_pin;
        uint8_t m_state = 0;
        uint8_t m_mode;
        volatile uint8_t *m_reg, *m_out;
        uint8_t m_bit, m_port;
};

#endif // DIGITALPIN_H
