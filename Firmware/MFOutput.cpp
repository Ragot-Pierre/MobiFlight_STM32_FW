//
// Output.cpp
//
// (C) MobiFlight Project 2022
//

#include "MFOutput.hpp"

MFOutput::MFOutput(uint8_t pin)
{
    _pin   = pin;
    _value = false;

    if (_pin < MAX_LOCAL)
    {
        pinMode(_pin, OUTPUT); // set pin to input
        set(_value);
        _address = 0xFF;
    }
    else
    {
        _address = 0xFF;
    }
        
}

void MFOutput::set(uint8_t value)
{
    _value = value;
    analogWrite(_pin, _value);
}

void MFOutput::powerSavingMode(bool state)
{
    if (state)
        set(0);
    else
        set(_value);
}

// Output.cpp
