#pragma once
#include "IsomerObject.h"
#include "NodeManager.h"
#include "MultiTransport.h"
#include "Sequences.h"

class NodeData;

class GUIReceiver
{
    public:
        GUIReceiver() {};
         ~GUIReceiver();
         
        void setObjectPointers (MultiTransport&, Sequences&);
        
        // MASTER
        void masterScaleSelected (const String&);
        void masterKeySelected (const String&);
        void masterKeyNumSelected (const int);
        void masterBPMSelected (const double&);
    
        // TRANSPORT
        void startButtonPressed (const int);
        void stopButtonPressed (const int);
        void bpmLabelChanged (const int, const double&);
        
        const double& getBPM (const int); 
        
        // SEQUENCE
        
        void newSequenceButtonPressed();
        void openSequenceButtonPressed();
        void deleteSequenceButtonPressed();
        void copySequenceButtonPressed();
        void newSequenceUserIdLabelChanged (const String&);
        void numberOfNotesLabelChanged (const int);
        void lengthBeatsLabelChanged (const int);
        void lengthDivisionsSelected (const int);   
        void sequenceSelected (const String&);
    
        // NODE SELECTION
        void sendObjectSelected (const String&);
        void sendParameterSelected (const String&);
        void sendVIntSelected (const int);
        void sendVStringSelected (const String&);
        void sendVString2Selected (const String&);
        void receiveObjectSelected (const String&);
        void receiveParameterSelected (const String&);
        void receiveVIntSelected (const int);
        void receiveVStringSelected (const String&);
        void receiveVString2Selected (const String&);
        
        const String& getSendObject();
        const String& getSendParameter();
        const int getSendVInt();
        const String& getSendVString();
        const String& getSendVString2();
        const String& getReceiveObject();
        const String& getReceiveParameter();
        const int getReceiveVInt();
        const String& getReceiveVString();
        const String& getReceiveVString2();
        
        NodeData* createMapNodeIcon (const String&, const int, const int);
    
    private:  
        // OBJECT POINTERS
        ScopedPointer <MultiTransport> multiTransport;
        ScopedPointer <Sequences> sequences;
    
        // OBJECTS
        NodeManager nodeManager;
    
        // TRANSPORT
        Array <double> bpmArray;
        
        // SEQUENCE
        String selectedSequence = "";
              
        // NODE SELECTION
        String sendObject;
        String sendParameter;
        int sendVInt;
        String sendVString;
        String sendVString2;
        String receiveObject;
        String receiveParameter;
        int receiveVInt;
        String receiveVString;
        String receiveVString2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIReceiver)
};