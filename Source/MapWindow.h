#pragma once
#include "MapGUI.h"

class MapWindow :   public DocumentWindow
{
    public:
        MapWindow() : DocumentWindow    (   "Map",
                                            Colours::lightgrey,
                                            DocumentWindow::allButtons
                                        )
        {
            setUsingNativeTitleBar (true);
            setCentrePosition (600, 90);
            setContentOwned (new MapGUI, true);
            setResizable (true, true);            
            setResizeLimits (760, 555, 1520, 1110);
        }

        ~MapWindow() {}

        void closeButtonPressed()
        {
            this->setVisible (false);
        }
    
        void setApplicationCommandManager (ApplicationCommandManager& a)
        {
             addKeyListener (a.getKeyMappings());
        }
        
        Component* getMapGUI()
        {
            return getContentComponent();
        }
        
    private:
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MapWindow);
};