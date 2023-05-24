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

    if (_address)
    {
        Serial1.write("W");
        Serial1.write(_address);
        Serial1.write(_pin);
        Serial1.write(_value);
    }
    else
    {
        pinMode(_pin, OUTPUT); // set pin to input
        set(_value);
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
