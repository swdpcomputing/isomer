#pragma once
#include "IsomerComponent.h"

class TransportControl  :   public IsomerComponent,
                            public Button::Listener,
                            public Label::Listener
{
    public:
        TransportControl (const int);
        ~TransportControl();
        
       void setBPMLabel (const double a); 
       const double getBPMLabelValue();
       
       void updateValueTree() override;
    
    private:
        void paint (Graphics&) override;
        void resized() override;
        void addComponents();
        void setComponents();
        void addListeners();
        void buttonClicked (Button*) override;
        void labelTextChanged (Label*) override;
        void updateVTProperties() override;
        
        const int num;
        const String stringNum;
        const String vtID;
        const String bpmPropertyID;
        double bpmValue;
    
        TextButton startTransportButton;
        TextButton stopTransportButton;
        Label transportBPMLabel;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportControl)
};

class TransportSection  :   public IsomerComponent
{
    public:
        TransportSection();
        ~TransportSection();
        
        void updateValueTree() override;
        
    private:
        void paint (Graphics&) override;
        void resized() override;
        void addComponents();
        
        GroupComponent transportGroup;
        OwnedArray <TransportControl> tCArray;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportSection)
};
