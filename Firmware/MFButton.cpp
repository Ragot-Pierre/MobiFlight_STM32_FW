//
// MFButton.cpp
//
// (C) MobiFlight Project 2022
//

#include "MFButton.hpp"

buttonEvent MFButton::_handler = NULL;

MFButton::MFButton(uint8_t pin, const char *name)
{
    _pin   = pin;
    _name  = name;

    if (_address)
    {
        Serial1.write("R");
        Serial1.write(_address);
        Serial1.write(_pin);

        uint8_t sender = 0x00;
        uint8_t pin = 0x00;
        uint8_t value = 0x00;

        while (sender != _address)
        {
            while (!Serial1.available){}

            sender = Serial1.read();
            pin = Serial1.read();
            value = Serial1.read();
        }
        
        _state = value;
    }
    else
    {
        pinMode(_pin, INPUT_PULLUP);    // set pin to input
        _state = digitalRead(_pin);     // initialize on actual status
    }    
}

void MFButton::update()
{
    if (_address)
    {
        Serial1.write("R");
        Serial1.write(_address);
        Serial1.write(_pin);

        uint8_t sender = 0x00;
        uint8_t pin = 0x00;
        uint8_t value = 0x00;

        while (sender != _address)
        {
            while (!Serial1.available){}

            sender = Serial1.read();
            pin = Serial1.read();
            value = Serial1.read();
        }
        
        newState = value;
    }
    else
    {
        uint8_t newState = (uint8_t)digitalRead(_pin);
    }    
    
    if (newState != _state) {
        _state = newState;
        trigger(_state);
    }
}

void MFButton::trigger(uint8_t state)
{
    (state == LOW) ? triggerOnPress() : triggerOnRelease();
}

void MFButton::triggerOnPress()
{
    if (_handler && _state == LOW) {
        (*_handler)(btnOnPress, _pin, _name);
    }
}

void MFButton::triggerOnRelease()
{
    if (_handler && _state == HIGH) {
        (*_handler)(btnOnRelease, _pin, _name);
    }
}

void MFButton::attachHandler(buttonEvent newHandler)
{
    _handler = newHandler;
}

// MFButton.cpp