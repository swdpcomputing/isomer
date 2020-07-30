#pragma once
#include "IsomerComponent.h"
#include "NodeData.h"

class MapNodeIcon : public IsomerComponent,
                    //public TextButton,
                    public DragAndDropTarget,
                    public Timer
{
    public:
        MapNodeIcon (NodeData*);
        MapNodeIcon (const String, IsomerObject*); 
        MapNodeIcon (ValueTree); 
        ~MapNodeIcon();
        
        void setValuesFromVT (ValueTree);
        ValueTree getMapNodeIconVT();
       
        void setFillColour (const String);
        void setMapPoint (const Array <int>);
        void setNodeImage (Image);
        void flashNode (const String);
                 
    private:  
        void paint (Graphics&) override;
        void resized() override {};
        void parentHierarchyChanged() override;
        
        void mouseDown (const MouseEvent&) override;
        void mouseDoubleClick (const MouseEvent&) override;
        void mouseDrag (const MouseEvent&) override;
        bool checkRightOrCtrl (const MouseEvent);
        
        bool isInterestedInDragSource (const SourceDetails&) override;
        void itemDropped (const SourceDetails&) override;        
               
        void timerCallback() override;  
        
        ScopedPointer <NodeData> nodeData;
        ScopedPointer <DragAndDropContainer> ddc;
    
        String fillColourId = "white";
        Colour fillColour = Colour (0xffffffff);
        
        Array <int> mapPoint;
        
        ImageComponent nodeImage;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapNodeIcon)
};