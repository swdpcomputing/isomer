#include "SequenceSection.h"

SequenceSection::SequenceSection()
{
    addComponents();
    addListeners();
    initialiseComponents();
}

SequenceSection::~SequenceSection()
{
}

void SequenceSection::paint (Graphics& g)
{
}

void SequenceSection::resized()
{
    sequenceGroup.setBounds (0, 0, 305, getHeight() - 5);
    newSequenceUserIdLabel.setBounds (10, 15, getWidth() - 25, 25);
    newSequenceNoteNumLabel.setBounds (10, 45, 65, 25);
    newSequenceLengthBeatsLabel.setBounds (80, 45, 65, 25);
    newSequenceLengthDivisionsComboBox.setBounds (150, 45, 65, 25);
    newSequenceButton.setBounds (220, 45, 25, 25);
    selectSequenceComboBox.setBounds (10, 75, getWidth() - 25, 25);
    openSequenceEditButton.setBounds (10, 105, 25, 25);
    copySequenceButton.setBounds (40, 105, 25, 25);
    deleteSequenceButton.setBounds (70, 105, 25, 25);
}

void SequenceSection::addComponents()
{
    addAndMakeVisible (sequenceGroup);
    addAndMakeVisible (newSequenceUserIdLabel);
    addAndMakeVisible (newSequenceNoteNumLabel);
    addAndMakeVisible (newSequenceLengthBeatsLabel);
    addAndMakeVisible (newSequenceLengthDivisionsComboBox);
    addAndMakeVisible (newSequenceButton);
    addAndMakeVisible (selectSequenceComboBox);
    addAndMakeVisible (openSequenceEditButton);
    addAndMakeVisible (copySequenceButton);
    addAndMakeVisible (deleteSequenceButton);
}

void SequenceSection::initialiseComponents()
{
    newSequenceUserIdLabel.setEditable (false, true);
    newSequenceNoteNumLabel.setEditable (false, true);
    newSequenceLengthBeatsLabel.setEditable (false, true);
    
    sequenceGroup.setText ("sequence");
    newSequenceButton.setButtonText ("N");
    openSequenceEditButton.setButtonText ("O");
    copySequenceButton.setButtonText ("C");
    deleteSequenceButton.setButtonText ("D");
    newSequenceUserIdLabel.setText ("newSequenceId", dontSendNotification);
    newSequenceNoteNumLabel.setText (String (numberOfNotes), dontSendNotification);
    newSequenceLengthBeatsLabel.setText (String (lengthBeats), dontSendNotification);
    
    newSequenceLengthDivisionsComboBox.addItemList (zero2fifteen, 1);
    newSequenceLengthDivisionsComboBox.setText ("0");
}

void SequenceSection::addListeners()
{
    newSequenceUserIdLabel.addListener (this);
    newSequenceNoteNumLabel.addListener (this);
    newSequenceLengthBeatsLabel.addListener (this);
    newSequenceLengthDivisionsComboBox.addListener (this);
    newSequenceButton.addListener (this);
    selectSequenceComboBox.addListener (this);
    openSequenceEditButton.addListener (this);
    deleteSequenceButton.addListener (this);
    copySequenceButton.addListener (this);
}

void SequenceSection::buttonClicked (Button* b)
{
    if      (b == &newSequenceButton)       guiReceiver->newSequenceButtonPressed();
    else if (b == &openSequenceEditButton)  guiReceiver->openSequenceButtonPressed();
    else if (b == &deleteSequenceButton)    guiReceiver->deleteSequenceButtonPressed();
    else if (b == &copySequenceButton)      guiReceiver->copySequenceButtonPressed();
}

void SequenceSection::labelTextChanged (Label* l)
{
    if (l == &newSequenceUserIdLabel)
    {
        guiReceiver->newSequenceUserIdLabelChanged (newSequenceUserIdLabel.getText());
    }
    
    else if (l == &newSequenceNoteNumLabel)
    {
        if (isIntAndRange (newSequenceNoteNumLabel.getText(), 0, 128))
        {
            numberOfNotes = newSequenceNoteNumLabel.getText().getIntValue();
            guiReceiver->numberOfNotesLabelChanged (numberOfNotes);
        }
    
        else newSequenceNoteNumLabel.setText (String (numberOfNotes), dontSendNotification);
    }
    
    else if (l == &newSequenceLengthBeatsLabel)
    {
        if (isIntAndRange (newSequenceLengthBeatsLabel.getText(), 0, 128))
        {
            lengthBeats = newSequenceLengthBeatsLabel.getText().getIntValue();
            guiReceiver->lengthBeatsLabelChanged (lengthBeats);
        }
    
        else newSequenceLengthBeatsLabel.setText (String (lengthBeats), dontSendNotification);
    };
}

void SequenceSection::comboBoxChanged (ComboBox* cb)
{
    if (cb == &newSequenceLengthDivisionsComboBox)
    {
        guiReceiver->lengthDivisionsSelected (newSequenceLengthDivisionsComboBox.getText().getIntValue());
    }
    
    else if (cb == &selectSequenceComboBox)
    {
        guiReceiver->sequenceSelected (selectSequenceComboBox.getText());
    };
}

void SequenceSection::refreshSelectSequenceComboBox()
{
    selectSequenceComboBox.clear();
    StringArray sa = getAllChildIds (mainVT->getChildWithName ("sequenceVT"));
        
    for (auto o : sa)
    {
        sa.set (sa.indexOf (o, false, 0), mainVT->getChildWithName ("sequenceVT").getChildWithName (o).getProperty ("sequenceUserId").toString());
    };
        
    selectSequenceComboBox.addItemList (sa, 1);
}

    //-----VALUETREE-----\\

void SequenceSection::postUpdateValueTree()
{
    mainVT->addListener (this);
}

void SequenceSection::valueTreeChildAdded (ValueTree& parentVT, ValueTree& addedVT)
{
    if (parentVT.getType().toString() == "sequenceVT") refreshSelectSequenceComboBox();
}

void SequenceSection::valueTreeChildRemoved (ValueTree& parentVT, ValueTree& addedVT, int index)
{
    if (parentVT.getType().toString() == "sequenceVT") refreshSelectSequenceComboBox();
}