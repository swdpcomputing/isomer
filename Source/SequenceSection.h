#pragma once
#include "IsomerComponent.h"
#include "IsomerScaleUser.h"

class SequenceSection   :   public IsomerComponent,
                            public Label::Listener,
                            public Button::Listener,
                            public ComboBox::Listener,
                            public IsomerScaleUser
{
    public:
        SequenceSection();
        ~SequenceSection();
        
        void postUpdateValueTree() override; 
        
    private:
        void paint (Graphics&) override;
        void resized() override;
        void addComponents();
        void initialiseComponents();
        void addListeners();
        void buttonClicked (Button*) override;
        void labelTextChanged (Label*) override;
        void comboBoxChanged (ComboBox*) override;
        
        void refreshSelectSequenceComboBox();
        
        void valueTreeChildAdded (ValueTree&, ValueTree&) override;
        void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override;
        
        GroupComponent sequenceGroup;
        Label newSequenceUserIdLabel;
        Label newSequenceNoteNumLabel;
        Label newSequenceLengthBeatsLabel;
        ComboBox newSequenceLengthDivisionsComboBox;
        ComboBox selectSequenceComboBox;
        TextButton newSequenceButton;
        TextButton openSequenceEditButton;
        TextButton deleteSequenceButton;
        TextButton copySequenceButton;
        
        int lengthBeats = 4;
        int numberOfNotes = 8;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceSection)
};