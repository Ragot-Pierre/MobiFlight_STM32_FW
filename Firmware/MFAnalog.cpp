//
// MFAnalog.cpp
//
// (C) MobiFlight Project 2022
//

#include "MFAnalog.hpp"

analogEvent MFAnalog::_handler = NULL;

MFAnalog::MFAnalog(uint8_t pin, const char *name, uint8_t sensitivity)
{
    _sensitivity = sensitivity;
    _pin         = pin;
    _name        = name;

    if (!_address)
    {
        pinMode(_pin, INPUT_PULLUP); // set pin to input. Could use OUTPUT for analog, but shows the intention :-)
    }
    
    // Fill averaging buffers with initial reading
    for (uint8_t i = 0; i < ADC_MAX_AVERAGE; i++) {
        readBuffer();
    }
    // and set initial value from buffers
    _lastValue = ADC_Average_Total >> ADC_MAX_AVERAGE_LOG2;
}

bool MFAnalog::valueHasChanged(int16_t newValue)
{
    return (abs(newValue - _lastValue) >= _sensitivity);
}

void MFAnalog::readChannel(uint8_t alwaysTrigger)
{
    int16_t newValue = ADC_Average_Total >> ADC_MAX_AVERAGE_LOG2;
    if (alwaysTrigger || valueHasChanged(newValue)) {
        _lastValue = newValue;
        if (_handler != NULL) {
            (*_handler)(_lastValue, _pin, _name);
        }
    }
}

void MFAnalog::update()
{
    readChannel(false);
}

void MFAnalog::retrigger()
{
    readChannel(true);
}

void MFAnalog::readBuffer()
{                                                           // read ADC and calculate floating average, call it every ~10ms
    ADC_Average_Total -= ADC_Buffer[(ADC_Average_Pointer)]; // subtract oldest value to save the newest value

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
        
        ADC_Buffer[ADC_Average_Pointer] = value;
    }
    else
    {
        ADC_Buffer[ADC_Average_Pointer] = analogRead(_pin);     // store read in, must be subtracted in next loop
    }
    

    ADC_Average_Total += ADC_Buffer[ADC_Average_Pointer];   // add read in for floating average
    ADC_Average_Pointer++;                                  // prepare for next loop
    ADC_Average_Pointer &= (ADC_MAX_AVERAGE - 1);           // limit max. values for floating average
}

void MFAnalog::attachHandler(analogEvent newHandler)
{
    _handler = newHandler;
}

// MFAnalog.cpp