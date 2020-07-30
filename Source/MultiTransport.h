#pragma once
#include "IsomerObject.h"
#include "Transport.h"

class MultiTransport :  public HighResolutionTimer,
                        public IsomerVTU
{
    public:
        MultiTransport();
        ~MultiTransport();
        
        void updateValueTree() override;
        void postUpdateValueTree() override;
        
        const double getTickDiv (const String);  // Need?
        
        //void routeAddLink (LinkWrapper*);
        void setMasterBPM (const double& a);
        void routeChangeBPMPerc (const int, const double);
        void routeStartTransport (const int);
        void routeStopTransport (const int);

        IsomerObject* getTransportPtrIO (const int);
        //LinkParent* getLinkParentPtr (const String);
        
        void stopAllTransports();
        
    private:       
        Transport* getTransportPtr (const int); // Need?
    
        //void preDesignateStringGet (LinkWrapper*);
        void designateTransportPtr (const int);   
        void createTransports();
        void hiResTimerCallback() override;
        
        void checkNewLinkWrapper (String);                     
        //void routeCreateTimePointLink (LinkWrapper*);
        //void routeCreatePulseLink (LinkWrapper*);
        
        OwnedArray <Transport> transportArray;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiTransport)
};
