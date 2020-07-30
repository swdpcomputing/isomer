#include "MapNodeIcon.h"
//#include "MapArrow.h"

MapNodeIcon::MapNodeIcon (NodeData* nd) :   nodeData (nd)
{
    //addAndMakeVisible (nodeImage);
}

MapNodeIcon::~MapNodeIcon()
{
    stopTimer();
    nodeData.release();
    ddc.release();
}
 
void MapNodeIcon::paint (Graphics& g)
{
    g.setColour (Colours::darkgrey);
    g.drawEllipse (0, 0, getWidth(), getHeight(), 1.0);
    g.setColour (fillColour);
    g.fillEllipse (1, 1, getWidth() - 2, getHeight() - 2);
    nodeImage.setBounds (2, 2, getWidth() - 4, getHeight() - 4);
} 

void MapNodeIcon::parentHierarchyChanged()
{
    if (ddc == nullptr)
    {
        ddc = DragAndDropContainer::findParentDragContainerFor (this);
    };
}

void MapNodeIcon::setFillColour (const String a)      
{
    fillColourId = a;
    fillColour = Colours::findColourForName (fillColourId, Colour (0xffffffff));
}

void MapNodeIcon::setNodeImage (Image a)
{
    nodeImage.setImage (a);
}

void MapNodeIcon::setMapPoint (const Array <int> a)
{
    mapPoint = a;
}

void MapNodeIcon::mouseDown (const MouseEvent& e)
{
}

bool MapNodeIcon::checkRightOrCtrl (const MouseEvent e)
{
    if (e.mods.isRightButtonDown() == true || e.mods.isCtrlDown() == true) return false;
    else return true;
}   

void MapNodeIcon::mouseDoubleClick (const MouseEvent& e)
{
}

void MapNodeIcon::mouseDrag (const MouseEvent& e)
{
    ddc->startDragging ("mapNodeIcon", this, Image(), false);
}

bool MapNodeIcon::isInterestedInDragSource (const SourceDetails& dSD)
{
    String x = dSD.description.toString();
    
    if      (x == "mapNodeIcon") return true;
    else return false;
}

void MapNodeIcon::itemDropped (const SourceDetails& dSD)
{
    String dragDescription = dSD.description.toString();

    if (dragDescription == "MapNodeIcon" && dSD.sourceComponent != this)
    {
        //mapGUIPtr->nodeDroppedOnNode (dSD.sourceComponent.get(), this);
    };
}

    //-----NODE FUNCTIONS-----\\

void MapNodeIcon::flashNode (const String a)
{
    if (isTimerRunning() != true) startTimer (100);
    fillColour = Colours::findColourForName (a, Colour (0xffffffff));
    //repaint();
}

void MapNodeIcon::timerCallback()
{
    stopTimer();
    fillColour = Colour (0xffffffff);
    //repaint();
}