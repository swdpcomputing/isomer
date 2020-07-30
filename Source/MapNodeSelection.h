#pragma once
#include "IsomerComponent.h"

class MapNodeDragSource :   public Component
{
    public:
        MapNodeDragSource (const String, const Colour);
        ~MapNodeDragSource();
        
    private:
        void paint (Graphics&) override;
        void parentHierarchyChanged() override;
        void mouseDrag (const MouseEvent&) override;
        
        ScopedPointer <DragAndDropContainer> ddc;
        const String mapNodeDragSourceId = "";
        const Colour colour;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapNodeDragSource);
};

class MapNodeSelection  :   public IsomerComponent,
                            public ComboBox::Listener,
                            public Label::Listener
{
    public:
        MapNodeSelection();
        ~MapNodeSelection();
        
        void updateValueTree() override;
        void postUpdateValueTree() override;
    
    private:
        void addComponents();
        void initialiseComponents();
        void resized() override;
        
        void populateSendObjectComboBox();
        void populateReceiveObjectComboBox();
        void addListeners();
        void comboBoxChanged (ComboBox*) override;
        void labelTextChanged (Label*) override;
        
        void updateVTProperties() override;

        void valueTreeChildAdded (ValueTree&, ValueTree&) override;
 	    void valueTreeChildRemoved (ValueTree&, ValueTree& , int) override;
    
        GroupComponent mapNodeSelectionGroup;
        
        ComboBox sendObjectComboBox;
        ComboBox sendParameterComboBox;
        Label sendVIntLabel;
        ComboBox sendVStringComboBox;
        ComboBox sendVString2ComboBox;
        ComboBox receiveObjectComboBox;
        ComboBox receiveParameterComboBox;
        Label receiveVIntLabel;
        ComboBox receiveVStringComboBox;
        ComboBox receiveVString2ComboBox;      
        
        OwnedArray <MapNodeDragSource> mapNodeDragSourceArray;
        
        int sendVInt = 0;
        int receiveVInt = 0;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapNodeSelection)          
};