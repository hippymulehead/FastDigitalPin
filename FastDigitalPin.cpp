#include <Arduino.h>
#include "wiring_private.h"
#include "pins_arduino.h"
#include "FastDigitalPin.h"

FastDigitalPin::FastDigitalPin(uint8_t pinNumber) {
    m_pin = pinNumber;
    m_bit = digitalPinToBitMask(m_pin);
    m_port = digitalPinToPort(m_pin);
    if (m_port == NOT_A_PIN) return;
    m_reg = portModeRegister(m_port);
    m_out = portOutputRegister(m_port);
}

FastDigitalPin::~FastDigitalPin() {
}

void FastDigitalPin::pinMode(uint8_t mode) {
    m_mode = mode;
	if (mode == INPUT) {
		uint8_t oldSREG = SREG;
                cli();
		*m_reg &= ~m_bit;
		*m_out &= ~m_bit;
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
                cli();
		*m_reg &= ~m_bit;
		*m_out |= m_bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
                cli();
		*m_reg |= m_bit;
		SREG = oldSREG;
	}
}

void FastDigitalPin::digitalWrite(uint8_t value) {
    switch (m_mode) {
        case OUTPUT: {
            m_state = value;
            if (m_state == LOW) {
        		*m_out &= ~m_bit;
        	} else {
        		*m_out |= m_bit;
        	}
        }
    }
}

uint8_t FastDigitalPin::digitalRead() {
    switch (m_mode) {
        case INPUT: {
            if (m_out) {
                return HIGH;
            } else {
                return LOW;
            }
        }
        case INPUT_PULLUP: {
            if (m_out) {
                return HIGH;
            } else {
                return LOW;
            }
        }
        default: {return LOW;}
    }
}

void FastDigitalPin::analogWrite(uint8_t value) {
    switch (m_mode) {
        case OUTPUT: {
            m_state = value;
            if (m_state == 0) {
                digitalWrite(LOW);
            } else if (m_state == 255) {
                digitalWrite(HIGH);
            } else {
                switch(digitalPinToTimer(m_pin)) {
                    #if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
                    case TIMER0A:
                        sbi(TCCR0, COM00);
                        OCR0 = m_state;
                        break;
                    #endif

                    #if defined(TCCR0A) && defined(COM0A1)
                    case TIMER0A:
                        sbi(TCCR0A, COM0A1);
                        OCR0A = m_state;
                        break;
                    #endif

                    #if defined(TCCR0A) && defined(COM0B1)
                    case TIMER0B:
                        sbi(TCCR0A, COM0B1);
                        OCR0B = m_state;
                        break;
                    #endif

                    #if defined(TCCR1A) && defined(COM1A1)
                    case TIMER1A:
                        sbi(TCCR1A, COM1A1);
                        OCR1A = m_state;
                        break;
                    #endif

                    #if defined(TCCR1A) && defined(COM1B1)
                    case TIMER1B:
                        sbi(TCCR1A, COM1B1);
                        OCR1B = m_state;
                        break;
                    #endif

                    #if defined(TCCR2) && defined(COM21)
                    case TIMER2:
                        sbi(TCCR2, COM21);
                        OCR2 = m_state;
                        break;
                    #endif

                    #if defined(TCCR2A) && defined(COM2A1)
                    case TIMER2A:
                        sbi(TCCR2A, COM2A1);
                        OCR2A = m_state;
                        break;
                    #endif

                    #if defined(TCCR2A) && defined(COM2B1)
                    case TIMER2B:
                        sbi(TCCR2A, COM2B1);
                        OCR2B = m_state;
                        break;
                    #endif

                    #if defined(TCCR3A) && defined(COM3A1)
                    case TIMER3A:
                        sbi(TCCR3A, COM3A1);
                        OCR3A = m_state;
                        break;
                    #endif

                    #if defined(TCCR3A) && defined(COM3B1)
                    case TIMER3B:
                        sbi(TCCR3A, COM3B1);
                        OCR3B = m_state;
                        break;
                    #endif

                    #if defined(TCCR3A) && defined(COM3C1)
                    case TIMER3C:
                        sbi(TCCR3A, COM3C1);
                        OCR3C = m_state;
                        break;
                    #endif

                    #if defined(TCCR4A)
                    case TIMER4A:
                        sbi(TCCR4A, COM4A1);
                        #if defined(COM4A0)
                        cbi(TCCR4A, COM4A0);
                        #endif
                        OCR4A = m_state;
                        break;
                    #endif

                    #if defined(TCCR4A) && defined(COM4B1)
                    case TIMER4B:
                        sbi(TCCR4A, COM4B1);
                        OCR4B = m_state;
                        break;
                    #endif

                    #if defined(TCCR4A) && defined(COM4C1)
                    case TIMER4C:
                        sbi(TCCR4A, COM4C1);
                        OCR4C = m_state;
                        break;
                    #endif

                    #if defined(TCCR4C) && defined(COM4D1)
                    case TIMER4D:
                        sbi(TCCR4C, COM4D1);
                        #if defined(COM4D0)
                        cbi(TCCR4C, COM4D0);
                        #endif
                        OCR4D = m_state;
                        break;
                    #endif


                    #if defined(TCCR5A) && defined(COM5A1)
                    case TIMER5A:
                        sbi(TCCR5A, COM5A1);
                        OCR5A = m_state;
                        break;
                    #endif

                    #if defined(TCCR5A) && defined(COM5B1)
                    case TIMER5B:
                        sbi(TCCR5A, COM5B1);
                        OCR5B = m_state;
                        break;
                    #endif

                    #if defined(TCCR5A) && defined(COM5C1)
                    case TIMER5C:
                        sbi(TCCR5A, COM5C1);
                        OCR5C = m_state;
                        break;
                    #endif

                    case NOT_ON_TIMER:
                    default:
                    if (m_state < 128) {
                        digitalWrite(LOW);
                    } else {
                        digitalWrite(HIGH);
                    }
                }
            }
        }
    }
}
