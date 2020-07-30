#pragma once
#include "IsomerComponent.h"
#include "MapNodeIcon.h"
#include "NodeData.h"

class MapCircle :   public IsomerComponent
{
    public:
        MapCircle() {};
    
        void setColour (const int);

    private:
        void paint (Graphics&) override;
        int colour = 0;
};

class MapArea   :   public IsomerComponent,
                    public DragAndDropTarget
{
    public:
        MapArea();
        ~MapArea();
    
    private:
        void paint (Graphics&) override;
        void resized() override;
    
        bool isInterestedInDragSource (const SourceDetails&) override;
        void itemDragEnter (const SourceDetails&) override;
        void itemDragMove (const SourceDetails&) override;
        void itemDragExit (const SourceDetails&) override;
        void itemDropped (const SourceDetails&) override;
        bool shouldDrawDragImageWhenOver() override;
        
        void mouseEnter (const MouseEvent&) override;
        void mouseExit (const MouseEvent&) override;
        void mouseMove (const MouseEvent&) override;
        
        // NODE CREATION
        void setMapCircleLocation();
        const int roundToMultiple (int&, const int&, const double&, const double&);
        
        // NODE CREATION
        void createNode();
        
        // NODE LOCATION
        void locateMapNodeIcon (MapNodeIcon*);
        
        // OBJECTS
        MapCircle mapCircle;
        OwnedArray <MapNodeIcon> mapNodeIconArray;
        ScopedPointer <NodeData> nodeData = nullptr;
        
        const int numColumns = 24;
        const int numRows = 16;
        const int gridXLimit;
        const int gridYLimit;
        const float gridWeight = 0.2;
        double blockWidth;
        double blockHeight;
        int gridMouseNumX;
        int gridMouseNumY;
        int mniCirc;
        int mniRad;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapArea);
};