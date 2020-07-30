#pragma once
#include "IsomerObject.h"
#include "Scales.h"

class IsomerScaleUser
{
    public:
        IsomerScaleUser() {};
        ~IsomerScaleUser() {};
        
    protected:
        static ScopedPointer <Scales> scales;
    
        static const StringArray keys;
        static const StringArray midiNoteNumbers;
        static const StringArray zero2fifteen;
};