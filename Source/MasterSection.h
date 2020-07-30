#pragma once
#include "IsomerComponent.h"
#include "IsomerScaleUser.h"

class MasterSection    :    public IsomerComponent,
                            public Label::Listener,
                            public ComboBox::Listener,
                            public IsomerScaleUser
                            
{
    public:
        MasterSection();
        ~MasterSection();
        
        void updateValueTree() override;
        
    private:
        void updateVTProperties() override;
    
        void paint (Graphics&) override {};
        void resized() override;
        void addComponents();
        void initialiseComponents();
        
        void addListeners();
        void comboBoxChanged (ComboBox*) override;
        void labelTextChanged (Label*) override;
        
        GroupComponent masterGroup;
        Label masterBPMLabel;
        ComboBox masterScaleComboBox;
        ComboBox masterKeyComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterSection)
};