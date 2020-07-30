#pragma once
#include "IsomerObject.h"
#include "IsomerVTU.h"
#include "Sequence.h"

//class LinkWrapper;

class Sequences :   public IsomerVTU
{
    public:
        Sequences();
        ~Sequences();
        
        void updateValueTree() override;    
        void postUpdateValueTree() override;
//        void updateSequenceEditGUIPtr();
//        void setValueTree (ValueTree&) override;
//        
        void addSequenceNew();
        void deleteSequence (const String&);
//        void deleteSequenceNew (const String) override;
//        void copySequence (const String, const String);
//        void changeSequenceNew (Sequence*, const String) override;
//        void addSequencesFromVT() override;
//        void routeAddLink (LinkWrapper*) override;
//        
//        const String getIdFromUserId (const String) override;
//        
//        Sequence* getSequenceFromUserId (const String);
//        int getIndSequenceNumNotes (String);
//        LinkParent* getLinkParentPtr (const String) override;
        void setNewSequenceUserId (const String&);
        void setNewSequenceNumNotes (const int);
        void setNewSequenceLengthBeats (const int);       
        void setNewSequenceLengthDivisions (const int);  
//        
//        void sendUserIdsToGUI() override;
//        
    private:
        const bool checkIfSequenceUserIdExists();
        const String getNewSequenceId();
        void valueTreeChildAdded (ValueTree&, ValueTree&) override;
//        void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
        void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
        
        void addSequenceRedo (ValueTree);
//          
//        void addSequenceVT (ValueTree);
//        void addSequenceRedo (ValueTree);
//        void deleteSequenceRedo (ValueTree);
//        void deleteSequenceVT (const String);
//        void changeSequenceRedo (const String, ValueTree, const String);
//        
//        const String createNewSequenceId();
//        const String checkNewSequenceUserId (const String);
//                   
//        void routeCreateNotePlayedLink (LinkWrapper*);
//        
//        Sequence* getSequence (const String);
//        ValueTree getSequenceVT (const String);
//        
//            //-----OBJECTS-----\\
//        
        OwnedArray <Sequence> sequenceArray;
       
        //int numSequencesCreated = 0;   
        int newSequenceNumNotes = 4;
        int newSequenceLengthBeats = 4;
        int newSequenceLengthDivisions = 0;
//            
        String newSequenceUserId = "newSequenceId";
//        StringArray sequenceUserIds;
//        
//        bool newAddSequenceTransaction = false;
//        bool newDeleteSequenceTransaction = false;
//        bool newChangeSequenceTransaction = false;
        bool isNewTransaction = false;
//        
//        Value globalKey;
//        Value globalScale;
//        Value masterBPM;
//        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequences);    
};