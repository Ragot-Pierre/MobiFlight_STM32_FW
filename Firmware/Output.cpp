//
// Output.cpp
//
// (C) MobiFlight Project 2022
//

#include "mobiflight.hpp"
#include "MFOutput.hpp"
#include "Output.hpp"

namespace Output
{
    MFOutput *outputs[MAX_OUTPUTS];
    uint8_t outputsRegistered = 0;

    void Add(uint8_t pin)
    {
        if (outputsRegistered == MAX_OUTPUTS)
            return;

        if (!FitInMemory(sizeof(MFOutput))) {
            // Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Output does not fit in Memory"));
            return;
        }
        outputs[outputsRegistered] = new (allocateMemory(sizeof(MFOutput))) MFOutput(pin);
        outputsRegistered++;
#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kDebug, F("Added output"));
#endif
    }

    void Clear()
    {
        outputsRegistered = 0;
#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kDebug, F("Cleared outputs"));
#endif
    }

    void OnSet()
    {
        // Read led state argument, interpret string as boolean
        int pin = cmdMessenger.readInt16Arg();
        int state = cmdMessenger.readInt16Arg();

        if (pin < MAX_LOCAL)
        {
            // Set led
            analogWrite(pin, state); // why does the UI sends the pin number and not the x.th output number like other devices?
                                    //  output[pin]->set(state);      // once this is changed uncomment this
        }
        else
        {
            Serial1.write(0x42);
            Serial1.write(pin);
            Serial1.write(state);
        }

        setLastCommandMillis();
    }

    void PowerSave(bool state)
    {
        for (uint8_t i = 0; i < outputsRegistered; ++i) {
            outputs[i]->powerSavingMode(state);
        }
    }
} // namespace

// Output.cpp
