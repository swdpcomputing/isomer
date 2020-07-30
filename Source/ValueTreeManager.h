#pragma once
#include "IsomerObject.h"
#include "IsomerVTU.h"
#include "Directories.h"
#include "Save.h"

class ValueTreeManager  :   public IsomerVTU
{
    public:
        ValueTreeManager();
        ~ValueTreeManager();
        
        ValueTree getMainValueTree();
        void setVTULL (IsomerVTU&);
        void save();
        void open();
        void openFromFile ( const File&);
        void undo();
        void redo();
        
    private:
        void addValueTrees();
    
        ValueTree mainVTObject; //SOME OF THESE NOT ADDED IN CPP WHY?
        ValueTree guiVT;
        ValueTree nodeSelectionGUIVT;
        ValueTree transportVT;
        ValueTree sequenceVT;
        
        ListenerList <IsomerVTU> valueTreeUserLL;
        
        Save saveObject;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ValueTreeManager);
};