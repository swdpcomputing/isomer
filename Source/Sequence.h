#pragma once
#include "IsomerObject.h"
#include "IsomerVTU.h"

class Sequence  :   public IsomerVTU
{
    public:
        Sequence (const String&, const String&, const int, const int, const int);
        Sequence (ValueTree);
        ~Sequence();
        
        // GETTERS
        const String& getSequenceId();
        const String& getSequenceUserId();
        
        ValueTree getSequenceVT();
    
    private:
        // INITIALISATION
        void calcLengthInTicks (int, int);
        
        // ARRAY INITIALISATION
        void initialiseArrays();
        void initialisePitchArray();
        void initialiseVelocityArray();
        void initialiseNoteStartArray();
        void calcSequenceDivision (int& a); // Recursive
        void initialiseNoteLengthArray();
        void initialiseMidiChannelArray();
        
        // VALUETREE
        void constructVT();
        void initialiseFromVT (ValueTree);
        
        // MISC
        void printSequenceValues();
    
        // OBJECTS
        String sequenceId;
        String sequenceUserId;
        int numberOfNotes;
        int lengthInTicks;
        int octave = 4;
                
        Array <int> pitchArray;
        Array <int> velocityArray;
        Array <int> noteTimesArray;
        Array <int> noteLengthArray;
        Array <int> midiChannelArray; 
        Array <int> locInPatternArray;        
        Array <double> percAlongArray;
        Array <double> yValPitchArray;

    JUCE_LEAK_DETECTOR (Sequence);
};