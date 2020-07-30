#include "MapArea.h"

    //-----MAP CIRCLE-----\\
    
void MapCircle::setColour (const int a)
{
    colour = a;
}

void MapCircle::paint (Graphics& g)
{
    g.fillAll (Colour (0xffffff));
    
    if (colour == 0) 
    {
        g.drawEllipse (getLocalBounds().toFloat(), float (0.2));
        return;
    }
    
    else 
    {
        if      (colour == 1) g.setColour (Colours::lightblue);
        else if (colour == 2) g.setColour (Colours::lightsalmon);
        
        g.fillEllipse (getLocalBounds().toFloat()); 
        return;
    };
}

    //-----MAP AREA-----\\

MapArea::MapArea()  :   gridXLimit (numColumns - 1),
                        gridYLimit (numRows - 1)
{
    //addAndMakeVisible (mapCircle);
    addChildComponent (mapCircle);
}

MapArea::~MapArea()
{
    nodeData.release();
}

void MapArea::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
    g.setColour (Colours::darkgrey);
    g.drawRect (getLocalBounds(), 1);
    
    for (int i = 1; i < numColumns; ++i)
    {
        int x = roundToInt (static_cast <double> (i) * blockWidth);
        g.drawLine (x, 0, x, getHeight(), gridWeight);
    };
    
    for (int i = 1; i < numRows; ++i)
    {
        int y = roundToInt (static_cast <double> (i) * blockHeight);
        g.drawLine (0, y, getWidth(), y, gridWeight);
    };
}

void MapArea::resized()
{
    blockWidth = static_cast <double> (getWidth()) / static_cast <double> (numColumns);
    blockHeight = static_cast <double> (getHeight()) / static_cast <double> (numRows);
    
    int circleCirc = getWidth() / 60;
    mapCircle.setSize (circleCirc, circleCirc);
    
    mniCirc = getWidth() / 30;
    mniRad = mniCirc / 2;
    for (auto& o : mapNodeIconArray) o->setSize (mniCirc, mniCirc);
}

    //-----MOUSE AND DRAG-----\\

bool MapArea::isInterestedInDragSource (const SourceDetails& sd)
{
    if  (   sd.description.toString() == "nodeOutDragSource" ||
            sd.description.toString() == "nodeInDragSource"  ||
            sd.description.toString() == "mapNodeIcon"
        )   return true;
        
    else return false;
}

void MapArea::itemDragEnter (const SourceDetails& sd)
{
    if      (sd.description.toString() == "nodeOutDragSource") mapCircle.setColour (1);
    else if (sd.description.toString() == "nodeInDragSource") mapCircle.setColour (2);
    else if (sd.description.toString() == "mapNodeIcon") mapCircle.setColour (1);
    mapCircle.setVisible (true);
}

void MapArea::itemDragMove (const SourceDetails& sd)
{
    setMapCircleLocation();
}

void MapArea::itemDragExit (const SourceDetails& sd)
{
    mapCircle.setColour (0);
    mapCircle.setVisible (false);
}

void MapArea::itemDropped (const SourceDetails& sd)
{
    String dragDescription = sd.description.toString();
    
    if (dragDescription == "nodeOutDragSource") 
    {
        nodeData = guiReceiver->createMapNodeIcon ("NodeOut", gridMouseNumX, gridMouseNumY);
        createNode();
    }
    
    else if (dragDescription == "nodeInDragSource") 
    {
        nodeData = guiReceiver->createMapNodeIcon ("NodeIn", gridMouseNumX, gridMouseNumY);
        createNode();
    }
    
    else if (dragDescription == "mapNodeIcon")
    {
        locateMapNodeIcon (dynamic_cast <MapNodeIcon*> (sd.sourceComponent.get()));
    };
    
    mapCircle.setColour (0);
}

bool MapArea::shouldDrawDragImageWhenOver()
{
    return false;
}

void MapArea::mouseEnter (const MouseEvent&)
{
    mapCircle.setVisible (true);
}

void MapArea:: mouseExit (const MouseEvent&)
{
    mapCircle.setVisible (false);
}

void MapArea::mouseMove (const MouseEvent&)
{
    setMapCircleLocation();
}

    //-----NODE CREATION-----||
    
void MapArea::createNode()
{
    if (nodeData == nullptr) // Change to !nullptr later
    {
        mapNodeIconArray.add (new MapNodeIcon (nodeData.get()));
        addAndMakeVisible (mapNodeIconArray.getLast());
        locateMapNodeIcon (mapNodeIconArray.getLast());
    };
}

    //-----NODE CIRCLE-----\\

void MapArea::setMapCircleLocation()
{
    mapCircle.setCentrePosition (   roundToMultiple (gridMouseNumX, gridXLimit, static_cast <double> (getMouseXYRelative().getX()), blockWidth),
                                    roundToMultiple (gridMouseNumY, gridYLimit, static_cast <double> (getMouseXYRelative().getY()), blockHeight)
                                );
}

const int MapArea::roundToMultiple (int& gridMouseNum, const int& gridLimit, const double& toRound, const double& multiple)
{
    gridMouseNum = jlimit (1, gridLimit, roundToInt (toRound / multiple));
    return roundToInt (static_cast <double> (gridMouseNum) * multiple);
}

    //-----NODE LOCATION-----\\
    
void MapArea::locateMapNodeIcon (MapNodeIcon* mni)
{
    mni->setBounds  (   (static_cast <double> (gridMouseNumX) * blockWidth) - mniRad, 
                        (static_cast <double> (gridMouseNumY) * blockHeight) - mniRad, 
                        mniCirc, 
                        mniCirc
                    );
}