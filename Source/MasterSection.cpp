#include "MasterSection.h"

const StringArray IsomerScaleUser::keys = StringArray {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const StringArray IsomerScaleUser::midiNoteNumbers = StringArray {"-1", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
const StringArray IsomerScaleUser::zero2fifteen = StringArray {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

MasterSection::MasterSection()
{
    setSize (getWidth(), getHeight());
    addComponents();
    initialiseComponents();
    addListeners();
}

MasterSection::~MasterSection()
{
}

void MasterSection::updateValueTree()
{
    ValueTree x = mainVT->getChildWithName ("guiVT").getChildWithName ("masterSection");
    
    if (x.isValid()) 
    {
        thisVT = x;
        updateVTProperties();
    }
    
    else  
    {
        thisVT = ValueTree ("masterSection");
        mainVT->getChildWithName ("guiVT").addChild (thisVT, -1, nullptr);
    };   
}

void MasterSection::updateVTProperties()
{
    masterBPMLabel.setText      (thisVT.getProperty ("masterBPM").toString(), dontSendNotification);
    masterScaleComboBox.setText (thisVT.getProperty ("masterScale").toString(), dontSendNotification);
    masterKeyComboBox.setText   (thisVT.getProperty ("masterKey").toString(), dontSendNotification);
}

void MasterSection::addComponents()
{
    addAndMakeVisible (masterGroup);
    addAndMakeVisible (masterBPMLabel);
    addAndMakeVisible (masterScaleComboBox);
    addAndMakeVisible (masterKeyComboBox);
}

void MasterSection::resized()
{
    masterGroup.setBounds (0, 5, 305, 50);
    masterBPMLabel.setBounds (10, 20, 65, 25);;
    masterScaleComboBox.setBounds (80, 20, 145, 25);
    masterKeyComboBox.setBounds (230, 20, 65, 25);
}

void MasterSection::initialiseComponents()
{
    masterGroup.setText ("master");
    masterBPMLabel.setEditable (false, true);
    masterKeyComboBox.addItemList (keys, 1);
    masterScaleComboBox.addItemList (scales->getScaleIds(), 1);
}

void MasterSection::addListeners()
{
    masterBPMLabel.addListener (this);
    masterScaleComboBox.addListener (this);
    masterKeyComboBox.addListener (this); 
}
    
void MasterSection::comboBoxChanged (ComboBox* cb)
{
    if (cb == &masterScaleComboBox)
    {
        thisVT.setProperty ("masterScale", var (masterScaleComboBox.getText()), undoManager);
        guiReceiver->masterScaleSelected (masterScaleComboBox.getText());
    }
    
    else if (cb == &masterKeyComboBox)
    {
        thisVT.setProperty ("masterKey", var (masterKeyComboBox.getText()), undoManager);
        thisVT.setProperty ("masterKeyNum", var (masterKeyComboBox.getSelectedItemIndex()), undoManager);
        guiReceiver->masterKeySelected (masterKeyComboBox.getText());
        guiReceiver->masterKeyNumSelected (masterKeyComboBox.getSelectedItemIndex());
    };
}

void MasterSection::labelTextChanged (Label* l)
{
    if (l == &masterBPMLabel)
    {
        if (isDoubleAndRange (masterBPMLabel.getText(), 10.0, 300.0))
        {
            thisVT.setProperty ("masterBPM", var (masterBPMLabel.getText()), undoManager);
            guiReceiver->masterBPMSelected (masterBPMLabel.getText().getDoubleValue());
        }
        
        else masterBPMLabel.setText (thisVT.getProperty ("masterBPM"), dontSendNotification);
    };
}