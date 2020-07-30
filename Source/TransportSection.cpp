#include "TransportSection.h"

    //-----TRANSPORT CONTROL-----\\

TransportControl::TransportControl (const int a)    :   num (a),
                                                        stringNum (String (num)),
                                                        vtID ("transportControl" + stringNum),
                                                        bpmPropertyID ("transportControlBPM" + stringNum)                                                        
{
    addComponents();
    setComponents();
    addListeners();
}

TransportControl::~TransportControl()
{
}

void TransportControl::updateValueTree()
{
    ValueTree x = mainVT->getChildWithName ("guiVT").getChildWithName (vtID);
    
    if (x.isValid()) 
    {
        thisVT = x;
        updateVTProperties();
    }
    
    else  
    {
        thisVT = ValueTree (vtID);
        mainVT->getChildWithName ("guiVT").addChild (thisVT, -1, nullptr);
    };   
}

void TransportControl::updateVTProperties()
{
    bpmValue = thisVT.getProperty (bpmPropertyID).operator int();
    transportBPMLabel.setText (String (bpmValue), dontSendNotification);
}

void TransportControl::paint (Graphics& g)
{
}

void TransportControl::addComponents()
{
    addAndMakeVisible (startTransportButton);
    addAndMakeVisible (stopTransportButton);
    addAndMakeVisible (transportBPMLabel);
}

void TransportControl::setComponents()
{
    startTransportButton.setButtonText (String (num));
    transportBPMLabel.setEditable (false, true);
}

void TransportControl::resized()
{
    startTransportButton.setBounds (0, 0, 25, 25);
    stopTransportButton.setBounds (30, 3, 20, 20);
    transportBPMLabel.setBounds (55, 0, 60, 25);
}

void TransportControl::addListeners()
{
    startTransportButton.addListener (this);
    stopTransportButton.addListener (this);
    transportBPMLabel.addListener (this);
}
    
void TransportControl::buttonClicked (Button* b)
{
    if      (b == &startTransportButton)    guiReceiver->startButtonPressed (num);
    else if (b == &stopTransportButton)     guiReceiver->stopButtonPressed (num);
}

void TransportControl::labelTextChanged (Label* l)
{
    if (isDoubleAndRange (transportBPMLabel.getText(), 10, 500))
    {
        bpmValue = transportBPMLabel.getText().getDoubleValue();
        thisVT.setProperty (bpmPropertyID, var (bpmValue), undoManager);
        guiReceiver->bpmLabelChanged (num, bpmValue);
    }
    
    else transportBPMLabel.setText (String (bpmValue), dontSendNotification);
}

const double TransportControl::getBPMLabelValue()
{
    return transportBPMLabel.getText().getIntValue();
}

    //-----TRANSPORT SECTION-----\\

TransportSection::TransportSection()
{
    transportGroup.setText ("transport");
    addComponents();
}

TransportSection::~TransportSection()
{
}

void TransportSection::updateValueTree()
{
    for (auto& o : tCArray) o->updateValueTree();
}

void TransportSection::paint (Graphics& g)
{
}

void TransportSection::addComponents()
{
    for (int i = 0; i < 9; ++i)
    {
        tCArray.add (new TransportControl (i));
        addAndMakeVisible (tCArray.getLast());
    };
    
    addAndMakeVisible (transportGroup);
}

void TransportSection::resized()
{
    Rectangle<int> area = getLocalBounds();
    transportGroup.setBounds (area.reduced (5, 5));
    
    area.removeFromTop (20);
    area.removeFromLeft (15);
    
    for (auto& o : tCArray) 
    {
        o->setBounds (area.removeFromTop (25));
        area.removeFromTop (3);
    };
}
/*
void TransportSection::setVTULL (ListenerList <IsomerObject>& a)
{
    for (auto& o : tCArray) a.add (o);
}
*/