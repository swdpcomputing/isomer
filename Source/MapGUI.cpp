#include "MapGUI.h"

MapGUI::MapGUI()
{
    setLookAndFeel (isomerLookAndFeels->getCurrentIsomerLookAndFeel()); // Because top level component
    addComponents();
    initialiseComponents();
    setSize (width, height);
    addListeners();
    mapSelected();
}

MapGUI::~MapGUI()
{
}

void MapGUI::updateValueTree()
{
    mapNodeSelection.updateValueTree();
}

void MapGUI::postUpdateValueTree()
{
    mapNodeSelection.postUpdateValueTree();
}

void MapGUI::paint (Graphics& g)
{
    g.fillAll (isomerLookAndFeels->getCurrentIsomerLookAndFeel()->getCurrentColourScheme().getUIColour (juce::LookAndFeel_V4::ColourScheme::windowBackground));
}

void MapGUI::addComponents()
{
    for (int i = 0; i < 32; ++i) 
    {
        mapSelectionButtonArray.add (new TextButton);
        mapSelectionButtonArray.getLast()->setButtonText (String (i + 1));
        addAndMakeVisible (mapSelectionButtonArray.getLast());
    };

    addAndMakeVisible (mapSelectionButtonGroup);
    addAndMakeVisible (mapNodeSelection);
    addAndMakeVisible (mapAreaGroup);
    addAndMakeVisible (mapArea);
}

void MapGUI::resized()
{  
    Rectangle <int> area (getLocalBounds());
    Rectangle <int> top = area.removeFromTop (45).removeFromRight (getWidth() - 10);
    mapSelectionButtonGroup.setBounds (top.withRightX (getWidth() - 5));
    
    top.removeFromTop (15);
    top.removeFromBottom (10);
    top.removeFromLeft (5);
    
    for (auto& o : mapSelectionButtonArray) 
    {       
        o->setBounds (top.removeFromLeft (20));
        top.removeFromLeft (3);        
    };
    
    mapNodeSelection.setBounds (area.removeFromTop (80));
    area = area.withTrimmedLeft (5).withTrimmedRight(5).withTrimmedBottom (5);
    mapAreaGroup.setBounds (area);
    area.removeFromTop (10);
    mapArea.setBounds (area.reduced (10, 10));
}

void MapGUI::initialiseComponents()
{
    mapSelectionButtonGroup.setText ("selection");
    mapAreaGroup.setText ("map area");
}

    //-----LISTENERS-----\\

void MapGUI::addListeners()
{
    for (auto o : mapSelectionButtonArray) o->addListener (this);
}

void MapGUI::buttonClicked (Button* b)
{
    currentMapSelection = mapSelectionButtonArray.indexOf (b);
    mapSelected();
}

    //-----MAP SELECTION-----\\
    
void MapGUI::mapSelected()
{
    //setMapSelectedButtonColours();
    //setMapSelectedNodesVisible();
    //setMapSelectedMapArrowsVisible();
}
