#include "IsomerCommandManager.h"

ApplicationCommandTarget* IsomerCommandManager::getNextCommandTarget()
{
    return nullptr;
}

void IsomerCommandManager::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = {   IsomerCommandManager::save,
                                IsomerCommandManager::open,
                                IsomerCommandManager::undo,
                                IsomerCommandManager::redo,
                                IsomerCommandManager::skinLight,
                                IsomerCommandManager::skinDark,
                                IsomerCommandManager::mainWindow,
                                IsomerCommandManager::mapWindow,
                                IsomerCommandManager::envelopeWindow,
                                IsomerCommandManager::settingsWindow
                            };

    commands.addArray (ids, numElementsInArray (ids));
}

void IsomerCommandManager::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    const String stateCategory ("State");
    const String appearanceCategory ("Appearance");
    const String windowCategory ("Windows");

    switch (commandID)
    {
        case IsomerCommandManager::save:
            result.setInfo ("Save", "Saves the project", stateCategory, 0);
            result.addDefaultKeypress ('S', ModifierKeys::commandModifier);
            break;

        case IsomerCommandManager::open:
            result.setInfo ("Open", "Opens a project", stateCategory, 0);
            result.addDefaultKeypress ('O', ModifierKeys::commandModifier);
            break;
            
        case IsomerCommandManager::undo:
            result.setInfo ("Undo", "Undoes the last action", stateCategory, 0);
            result.addDefaultKeypress ('Z', ModifierKeys::commandModifier);
            break;

        case IsomerCommandManager::redo:
            result.setInfo ("Redo", "Redoes the last action", stateCategory, 0);
            result.addDefaultKeypress ('Y', ModifierKeys::commandModifier);
            break;
            
        case IsomerCommandManager::skinLight:
            result.setInfo ("Light", "Sets the light Colour Scheme", appearanceCategory, 0);
            break;
    
        case IsomerCommandManager::skinDark:
            result.setInfo ("Dark", "Sets the light Colour Scheme", appearanceCategory, 0);
            break; 
            
        case IsomerCommandManager::mainWindow:
            result.setInfo ("Main Window", "Brings the Main Window to the front", windowCategory, 0);
            result.addDefaultKeypress ('1', ModifierKeys::commandModifier);
            break;
            
        case IsomerCommandManager::mapWindow:
            result.setInfo ("Map Window", "Opens the Map Window", windowCategory, 0);
            result.addDefaultKeypress ('2', ModifierKeys::commandModifier);
            break; 
            
        case IsomerCommandManager::envelopeWindow:
            result.setInfo ("Envelope Window", "Opens the Envelope Window", windowCategory, 0);
            result.addDefaultKeypress ('3', ModifierKeys::commandModifier);
            break; 
            
        case IsomerCommandManager::settingsWindow:
            result.setInfo ("Settings Window", "Opens the Settings Window", windowCategory, 0);
            result.addDefaultKeypress ('4', ModifierKeys::commandModifier);
            break; 

        default:
            break;
    };
}

bool IsomerCommandManager::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case IsomerCommandManager::save:
            lastCommand = "save";
            break;
            
        case IsomerCommandManager::open:
            lastCommand = "open";;
            break;
            
        case IsomerCommandManager::undo:
            lastCommand = "undo";
            break;
            
        case IsomerCommandManager::redo:
            lastCommand = "redo";
            break;
            
        case IsomerCommandManager::skinLight:
            lastCommand = "skinLight";
            break;
            
        case IsomerCommandManager::skinDark:
            lastCommand = "skinDark";
            break;
            
        case IsomerCommandManager::mainWindow:
            lastCommand = "mainWindow";
            break;
            
        case IsomerCommandManager::mapWindow:
            lastCommand = "mapWindow";
            break;
            
        case IsomerCommandManager::envelopeWindow:
            lastCommand = "envelopeWindow";
            break;
            
        case IsomerCommandManager::settingsWindow:
            lastCommand = "settingsWindow";
            break;

        default:
            return false;
    };
    
    sendActionMessage (lastCommand);

    return true;
}