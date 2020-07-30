#pragma once
#include "IsomerVTU.h"
//#include "Sequence.h"

class Transport :   public IsomerVTU
{
    public:
        Transport (const String);
        ~Transport();   
        
        void updateValueTree() override;
        const String getTransportID();
        
        //void createTimePointLink (LinkParent*, LinkWrapper*);
        //void createPulseLink (LinkParent*, LinkWrapper*);
                
        void startTransport();
        void startTransport (const int);
        void stopTransport();    
        void setMasterBPM (const double& a);  
        void setBPMPerc (const double a);  
        void masterCountFunc();

        //void linkCall (LinkWrapper*) override;
        
        const double getBPM();
        const bool getIsTransportRunning();
        const double getTickDiv();
        
        //void addSequence (Sequence*);
        //void removeSequence (Sequence*);
                
    private:  
        void updateVTProperties() override;
    
        void countFunc();
        void setIndBPM(); 
        void checkExtra();
        
        const String transportID;     
        const String bpmPropertyID;
        
        int count = 0;
        Value countValue;
        
        double bPMPerc = 1.0;
        double masterBPM = 0.0;
        double masterCount = 0.0;
        double indBPM = 0.0;     
        double dMsPerQBeat = 0.0;
        double dMsPer16thBeat = 0.0;
        double tickDiv = 0.0;
        double tickDivInterval = 0.0;
        
        bool isTransportRunning = false;
        
        //ListenerList <Sequence> sequenceLL;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Transport);
};