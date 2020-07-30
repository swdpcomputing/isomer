#pragma once
#include "IsomerComponent.h"
#include "MapNodeSelection.h"
#include "MapArea.h"

class MapGUI :  public IsomerComponent,
                public Button::Listener,
                public DragAndDropContainer
{
    public: 
        MapGUI();
        ~MapGUI();
        
        void updateValueTree() override;
        void postUpdateValueTree() override;
    
    private:        
        void paint (Graphics&) override;
        void resized() override;
        void initialiseComponents();
        void addComponents();
        void addListeners();
        void buttonClicked (Button*) override;
        void mapSelected();

        MapNodeSelection mapNodeSelection;
        MapArea mapArea;
        
        OwnedArray <Button> mapSelectionButtonArray;
        
        GroupComponent mapSelectionButtonGroup;
        GroupComponent mapAreaGroup;
            
        int currentMapSelection = 0;
        int width = 760;
        int height = 555;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapGUI)    
};
