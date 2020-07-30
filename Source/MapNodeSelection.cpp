#include "MapNodeSelection.h"

MapNodeDragSource::MapNodeDragSource    (   const String a, 
                                            Colour b
                                        ) : mapNodeDragSourceId (a),
                                            colour (b)                                                                   
{
}

MapNodeDragSource::~MapNodeDragSource()
{
    ddc.release();
}

void MapNodeDragSource::paint (Graphics& g)
{
    g.fillAll (colour);
}

void MapNodeDragSource::mouseDrag (const MouseEvent&)
{
    ddc->startDragging (mapNodeDragSourceId, this, Image(), false);
}

void MapNodeDragSource::parentHierarchyChanged()
{
    if (ddc == nullptr)
    {
        ddc = DragAndDropContainer::findParentDragContainerFor (this);
    };
}
    //-----MAPNODESELECTION-----\\
    
MapNodeSelection::MapNodeSelection()
{
    addComponents();
    initialiseComponents();
    addListeners();
}

MapNodeSelection::~MapNodeSelection()
{
    //mainVT.release();
}
    
void MapNodeSelection::addComponents()
{
    mapNodeDragSourceArray.add (new MapNodeDragSource ("nodeOutDragSource", Colours::lightblue));
    mapNodeDragSourceArray.add (new MapNodeDragSource ("nodeInDragSource", Colours::lightsalmon));
    
    for (auto& o : mapNodeDragSourceArray) addAndMakeVisible (o);
    
    addAndMakeVisible (sendObjectComboBox);
    addAndMakeVisible (sendParameterComboBox);
    addAndMakeVisible (sendVIntLabel);
    addAndMakeVisible (sendVStringComboBox);
    addAndMakeVisible (sendVString2ComboBox);
    addAndMakeVisible (receiveObjectComboBox);
    addAndMakeVisible (receiveParameterComboBox);
    addAndMakeVisible (receiveVIntLabel);
    addAndMakeVisible (receiveVStringComboBox);
    addAndMakeVisible (receiveVString2ComboBox);
    addAndMakeVisible (mapNodeSelectionGroup);   
}

void MapNodeSelection::initialiseComponents()
{
    mapNodeSelectionGroup.setText ("node selection");
}

void MapNodeSelection::resized()
{
    mapNodeSelectionGroup.setBounds (getLocalBounds().removeFromRight (getWidth() - 10).withRightX (getWidth() - 5));

    Rectangle <int> area = getLocalBounds().removeFromBottom (getHeight() - 15);
    
    Rectangle <int> topRow = area.removeFromTop (25).removeFromRight (getWidth() - 15);
    sendObjectComboBox.setBounds (topRow.removeFromLeft (160));
    topRow.removeFromLeft (5);
    sendParameterComboBox.setBounds (topRow.removeFromLeft (160));
    topRow.removeFromLeft (5);
    sendVIntLabel.setBounds (topRow.removeFromLeft (40));
    topRow.removeFromLeft (5);
    sendVStringComboBox.setBounds (topRow.removeFromLeft (160));
    topRow.removeFromLeft (5);
    sendVString2ComboBox.setBounds (topRow.removeFromLeft (160));
    topRow.removeFromLeft (5);
    mapNodeDragSourceArray.getUnchecked (0)->setBounds (topRow.removeFromLeft (25));
    
    area.removeFromTop (5);
    Rectangle <int> bottomRow = area.removeFromTop (25).removeFromRight (getWidth() - 15);
    receiveObjectComboBox.setBounds (bottomRow.removeFromLeft (160));
    bottomRow.removeFromLeft (5);
    receiveParameterComboBox.setBounds (bottomRow.removeFromLeft (160));
    bottomRow.removeFromLeft (5);
    receiveVIntLabel.setBounds (bottomRow.removeFromLeft (40));
    bottomRow.removeFromLeft (5);
    receiveVStringComboBox.setBounds (bottomRow.removeFromLeft (160));
    bottomRow.removeFromLeft (5);
    receiveVString2ComboBox.setBounds (bottomRow.removeFromLeft (160));
    bottomRow.removeFromLeft (5);
    mapNodeDragSourceArray.getUnchecked (1)->setBounds (bottomRow.removeFromLeft (25));
}

    //-----POPULATORS-----\\
    
void MapNodeSelection::populateSendObjectComboBox()
{
    sendObjectComboBox.clear();
    sendObjectComboBox.addItemList (getAllChildIds (mainVT->getChildWithName ("transportVT")), 1);
    sendObjectComboBox.addItemList (getAllChildIds (mainVT->getChildWithName ("sequenceVT")), 1);
}

void MapNodeSelection::populateReceiveObjectComboBox()
{
    receiveObjectComboBox.clear();
    receiveObjectComboBox.addItemList (getAllChildIds (mainVT->getChildWithName ("transportVT")), 1);
    receiveObjectComboBox.addItemList (getAllChildIds (mainVT->getChildWithName ("sequenceVT")), 1);
}

    //-----LISTENERS-----\\
    
void MapNodeSelection::addListeners()
{
    sendObjectComboBox.addListener (this);
    sendParameterComboBox.addListener (this);
    sendVIntLabel.addListener (this);
    sendVStringComboBox.addListener (this);
    sendVString2ComboBox.addListener (this);
    receiveObjectComboBox.addListener (this);
    receiveParameterComboBox.addListener (this);
    receiveVIntLabel.addListener (this);
    receiveVStringComboBox.addListener (this);
    receiveVString2ComboBox.addListener (this); 
}
    
void MapNodeSelection::comboBoxChanged (ComboBox* cb)
{
    if (cb == &sendObjectComboBox)
    {
        thisVT.setProperty ("sendObject", var (sendObjectComboBox.getText()), undoManager);
        guiReceiver->sendObjectSelected (sendObjectComboBox.getText());
    }
    
    else if (cb == &sendParameterComboBox)
    {
        thisVT.setProperty ("sendParameter", var (sendParameterComboBox.getText()), undoManager);
        guiReceiver->sendParameterSelected (sendParameterComboBox.getText());
    }
    
    else if (cb == &sendVStringComboBox)
    {
        thisVT.setProperty ("sendVString", var (sendVStringComboBox.getText()), undoManager);
        guiReceiver->sendVStringSelected (sendVStringComboBox.getText());
    }
    
    else if (cb == &sendVString2ComboBox)
    {
        thisVT.setProperty ("sendVString2", var (sendVString2ComboBox.getText()), undoManager);
        guiReceiver->sendVString2Selected (sendVString2ComboBox.getText());
    }
    
    else if (cb == &receiveObjectComboBox)       
    {
        thisVT.setProperty ("receiveObject", var (receiveObjectComboBox.getText()), undoManager);
        guiReceiver->receiveObjectSelected (receiveObjectComboBox.getText());
    }
    
    else if (cb == &receiveParameterComboBox)    
    {
        thisVT.setProperty ("receiveParameter", var (receiveParameterComboBox.getText()), undoManager);
        guiReceiver->receiveParameterSelected  (receiveParameterComboBox.getText());
    }
    
    else if (cb == &receiveVStringComboBox)
    {
        thisVT.setProperty ("receiveVString", var (receiveVStringComboBox.getText()), undoManager);
        guiReceiver->receiveVStringSelected (receiveVStringComboBox.getText());
    }
    
    else if (cb == &receiveVString2ComboBox)
    {
        thisVT.setProperty ("receiveVString2", var (receiveVString2ComboBox.getText()), undoManager);
        guiReceiver->receiveVString2Selected (receiveVString2ComboBox.getText());
    };
}

void MapNodeSelection::labelTextChanged (Label* l)
{
    if (l == &sendVIntLabel)
    {   
        if (isIntAndRange (sendVIntLabel.getText(), 1, 500))
        {
            thisVT.setProperty ("sendVInt", var (sendVIntLabel.getText()), undoManager);
            guiReceiver->sendVIntSelected (sendVIntLabel.getText().getIntValue());
        }
        
        else sendVIntLabel.setText (String (sendVInt), dontSendNotification);
    }
    
    else if (l == &receiveVIntLabel)
    {
        if (isIntAndRange (receiveVIntLabel.getText(), 1, 500))
        {
            thisVT.setProperty ("receiveVInt", var (receiveVIntLabel.getText()), undoManager);
            guiReceiver->receiveVIntSelected (receiveVIntLabel.getText().getIntValue());
        }
        
        else receiveVIntLabel.setText (String (receiveVInt), dontSendNotification);
    };
}

    //-----VALUETREE-----\\
    
void MapNodeSelection::updateValueTree()
{  
    ValueTree x = mainVT->getChildWithName ("guiVT").getChildWithName ("nodeSelectionGUIVT");
    
    if (x.isValid()) 
    {
        thisVT = x;
        updateVTProperties();
    }
    
    else  
    {
        thisVT = ValueTree ("nodeSelectionGUIVT");
        mainVT->getChildWithName ("guiVT").addChild (thisVT, -1, nullptr);
    }; 
}

void MapNodeSelection::valueTreeChildAdded (ValueTree&, ValueTree&)
{
    populateSendObjectComboBox();  
    populateReceiveObjectComboBox();
}

void MapNodeSelection::valueTreeChildRemoved (ValueTree&, ValueTree& , int)
{
    populateSendObjectComboBox();  
    populateReceiveObjectComboBox();
}

void MapNodeSelection::postUpdateValueTree()
{
    mainVT->addListener (this);
    populateSendObjectComboBox();
    populateReceiveObjectComboBox();
}

void MapNodeSelection::updateVTProperties()
{
    sendObjectComboBox.setText          (thisVT.getProperty ("sendObject").toString(), dontSendNotification);
    sendParameterComboBox.setText       (thisVT.getProperty ("sendParameter").toString(), dontSendNotification);
    sendVIntLabel.setText               (thisVT.getProperty ("sendVInt").toString(), dontSendNotification);
    sendVStringComboBox.setText         (thisVT.getProperty ("sendVString").toString(), dontSendNotification);
    sendVString2ComboBox.setText        (thisVT.getProperty ("sendVString2").toString(), dontSendNotification);
    receiveObjectComboBox.setText       (thisVT.getProperty ("receiveObject").toString(), dontSendNotification);
    receiveParameterComboBox.setText    (thisVT.getProperty ("receiveParameter").toString(), dontSendNotification);
    receiveVIntLabel.setText            (thisVT.getProperty ("receiveVInt").toString(), dontSendNotification);
    receiveVStringComboBox.setText      (thisVT.getProperty ("receiveVString").toString(), dontSendNotification);
    receiveVString2ComboBox.setText     (thisVT.getProperty ("receiveVString2").toString(), dontSendNotification);
}