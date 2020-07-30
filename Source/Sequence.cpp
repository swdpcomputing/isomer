#include "Sequence.h"

Sequence::Sequence  (   const String& a, 
                        const String& b, 
                        const int c, 
                        const int d, 
                        const int e
                    ) : sequenceId (a),
                        sequenceUserId (b),
                        numberOfNotes (c)
{
    calcLengthInTicks (d, e);
    initialiseArrays();
    constructVT();
}

Sequence::Sequence (ValueTree vt)
{
    initialiseFromVT (vt);
}

Sequence::~Sequence()
{
}

    //-----GETTERS-----\\
    
const String& Sequence::getSequenceId()
{
    return sequenceId;
}

const String& Sequence::getSequenceUserId()
{
    return sequenceUserId;
}

    //-----INITIALISATION-----\\

void Sequence::calcLengthInTicks (int a, int b)
{
    lengthInTicks = (a * 960) + (b * 60);
}

    //-----ARRAY INITIALISATION-----\\
    
void Sequence::initialiseArrays()
{
    initialisePitchArray();
    initialiseVelocityArray();
    initialiseNoteStartArray();
    initialiseNoteLengthArray();
    initialiseMidiChannelArray();
}  

void Sequence::initialisePitchArray()
{
    pitchArray.clear();
    pitchArray.insertMultiple (0, getMasterKeyNum(), numberOfNotes);
    //printIntArray (pitchArray);
}
        
void Sequence::initialiseVelocityArray()
{
    velocityArray.clear();
    velocityArray.insertMultiple (0, 100, numberOfNotes);
}
        
void Sequence::initialiseNoteStartArray()
{
    noteTimesArray.clear();
    int z = 960;
    calcSequenceDivision (z);
    for (int i = 0; i < numberOfNotes; ++i) noteTimesArray.add (i * z);
}

void Sequence::calcSequenceDivision (int& a) // Recursive
{
    if ((numberOfNotes * a) > lengthInTicks)
    {
        a = a / 2;
        calcSequenceDivision (a);
    };
}
        
void Sequence::initialiseNoteLengthArray()
{
    noteLengthArray.clear();
    noteLengthArray.insertMultiple (0, 240, numberOfNotes);
}
        
void Sequence::initialiseMidiChannelArray()
{
    midiChannelArray.clear();
    midiChannelArray.insertMultiple (0, 1, numberOfNotes);
}

    //-----VALUETREE-----\\

ValueTree Sequence::getSequenceVT()
{
    return thisVT;
}    

void Sequence::constructVT()
{
    thisVT = ValueTree (sequenceId);
    
    thisVT.setProperty ("sequenceId",           var (sequenceId),                   nullptr);
    thisVT.setProperty ("sequenceUserId",       var (sequenceUserId),               nullptr);
    thisVT.setProperty ("lengthInTicks",        var (lengthInTicks),                nullptr);
    thisVT.setProperty ("numberOfNotes",        var (numberOfNotes),                nullptr);
    thisVT.setProperty ("octave",               var (octave),                       nullptr);
   
    thisVT.setProperty ("pitchArray",           arrIntToVar (pitchArray),           nullptr);
    thisVT.setProperty ("velocityArray",        arrIntToVar (velocityArray),        nullptr);
    thisVT.setProperty ("noteTimesArray",       arrIntToVar (noteTimesArray),       nullptr);
    thisVT.setProperty ("noteLengthArray",      arrIntToVar (noteLengthArray),      nullptr);
    thisVT.setProperty ("midiChannelArray",     arrIntToVar (midiChannelArray),     nullptr);
    thisVT.setProperty ("locInPatternArray",    arrIntToVar (locInPatternArray),    nullptr);
    thisVT.setProperty ("percAlongArray",       arrDoubleToVar (percAlongArray),    nullptr);
    thisVT.setProperty ("yValPitchArray",       arrDoubleToVar (yValPitchArray),    nullptr);
    
    DBG ("1");
    printTree (thisVT);
    printSequenceValues();
}

void Sequence::initialiseFromVT (ValueTree vt)
{
    thisVT = vt;
    
    sequenceId = thisVT.getProperty ("sequenceId");
    sequenceUserId = thisVT.getProperty ("sequenceUserId");
    lengthInTicks = thisVT.getProperty ("lengthInTicks");
    numberOfNotes = thisVT.getProperty ("numberOfNotes");
    octave = thisVT.getProperty ("octave");
   
    pitchArray = varToArrInt (thisVT.getProperty ("pitchArray"));
    velocityArray = varToArrInt (thisVT.getProperty ("velocityArray"));
    noteTimesArray = varToArrInt (thisVT.getProperty ("noteTimesArray"));
    noteLengthArray = varToArrInt (thisVT.getProperty ("noteLengthArray"));
    midiChannelArray = varToArrInt (thisVT.getProperty ("midiChannelArray"));
    locInPatternArray = varToArrInt (thisVT.getProperty ("locInPatternArray"));
    percAlongArray = varToArrDouble (thisVT.getProperty ("percAlongArray"));
    yValPitchArray = varToArrDouble (thisVT.getProperty ("yValPitchArray"));
    
    DBG ("2");
    printTree (thisVT);
    printSequenceValues();
}

    //-----MISC-----\\
    
void Sequence::printSequenceValues()
{
    DBG ("noteSequenceId: " << sequenceId);
    DBG ("noteSequenceUserId: " << sequenceUserId);
    DBG ("lengthInTicks: " << lengthInTicks);
    DBG ("numberOfNotes: " << numberOfNotes);
    DBG ("octave: " << octave);
    DBG ("pitchArray: ");
    printIntArray (pitchArray);
    DBG ("velocityArray: ");
    printIntArray (velocityArray);
    DBG ("noteTimesArray: ");
    printIntArray (noteTimesArray);
    DBG ("noteLengthArray: ");
    printIntArray (noteLengthArray);
    DBG ("midiChannelArray: ");
    printIntArray (midiChannelArray);    
}