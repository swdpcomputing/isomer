#pragma once
#include "IsomerObject.h"
#include "IsomerComponent.h"
#include "IsomerScaleUser.h"
#include "IsomerCommandManager.h"
#include "MasterSection.h"
#include "TransportSection.h"
#include "SequenceSection.h"
#include "ValueTreeManager.h"
#include "MapWindow.h"
#include "Sequence.h"

class MainContentComponent   :  public IsomerComponent,
                                public MenuBarModel,
                                public ActionListener
{
    public:
        MainContentComponent();
        ~MainContentComponent();

    private:
        void paint (Graphics&) override;
        void addComponents();
        void resized() override;
        
        //-----APPLICATIONMANAGER
        static ApplicationCommandManager& getApplicationCommandManager();
        void handleAsyncUpdate() override;
        void actionListenerCallback (const String&) override;
        
        IsomerCommandManager isomerCommandManager;        
        
        //-----VALUETREE
        void populateVTULL();       
        ValueTreeManager valueTreeManager;
        
        //-----MENU
        StringArray getMenuBarNames() override;
        PopupMenu getMenuForIndex (int, const String&) override;
        void menuItemSelected (int, int) override {};
        
        ScopedPointer <MenuBarComponent> menuBar;
        
        //-----WINDOWS
        void openWindow (const String);
        
        MapWindow mapWindow;
    
        //-----COMPONENTS
        MasterSection masterSection;
        TransportSection transportSection;
        SequenceSection sequenceSection;
        
        //-----OBJECTS
        MultiTransport multiTransport;
        Sequences sequences;
       
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};