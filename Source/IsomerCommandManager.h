#pragma once
#include "IsomerObject.h"

class IsomerCommandManager  :   public ApplicationCommandTarget,
                                public ActionBroadcaster
{   
    public:
        IsomerCommandManager() {};
        ~IsomerCommandManager() {};
        
        enum CommandIDs
        {
            save            = 0x2100,
            open            = 0x2101,
            undo            = 0x2102,
            redo            = 0x2103,
            
            skinLight       = 0x2104,
            skinDark        = 0x2105,
            
            mainWindow      = 0x2106,
            mapWindow       = 0x2107,
            envelopeWindow  = 0x2108,
            settingsWindow  = 0x2109
        };
        
    private:
        ApplicationCommandTarget* getNextCommandTarget() override;
        void getAllCommands (Array <CommandID>&) override;
        void getCommandInfo (CommandID, ApplicationCommandInfo&) override;
        bool perform (const InvocationInfo&) override;
        
        String lastCommand = "";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IsomerCommandManager)
};