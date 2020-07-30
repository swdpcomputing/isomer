#pragma once
#include "IsomerObject.h"

class Scale
{
    public:
        Scale (String, int, int, int, int);
        Scale (String, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int, int, int, int, int);
        Scale (String, int, int, int, int, int, int, int, int, int, int, int);
        ~Scale();
        
        const String getScaleId();
        const Array <int>& getScale();
    
    private:
        String scaleId = "";
        Array <int> scaleArray;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scale);
};

//-----

class Scales
{
    public:
        Scales();
        ~Scales();
        
        const Array <int>& getScale (const String);
        const StringArray& getScaleIds();
        const StringArray& getKeyIDs();
        const StringArray& getMidiNoteNumbers();
        const StringArray& getMidiNoteIDs();
    
    private:
        OwnedArray <Scale> scaleArray;
        StringArray scaleIds;
        
        StringArray keyIds;
        StringArray midiNoteNumbers;
        StringArray midiNoteIDs;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scales);
};