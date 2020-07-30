#include "MainComponent.h"

static ScopedPointer <ApplicationCommandManager> applicationCommandManager;

    //-----INITIALISE STATIC ELEMENTS-----\\
    
ScopedPointer <UndoManager> IsomerVTU::undoManager = new UndoManager();
ScopedPointer <GUIReceiver> IsomerComponent::guiReceiver = new GUIReceiver();
ScopedPointer <Scales> IsomerScaleUser::scales = new Scales(); 
ScopedPointer <IsomerLookAndFeels> IsomerComponent::isomerLookAndFeels = new IsomerLookAndFeels();

    //-----MAIN CONTENT COMPONENT-----\\

MainContentComponent::MainContentComponent()
{
    guiReceiver->setObjectPointers (multiTransport, sequences);
    addKeyListener (getApplicationCommandManager().getKeyMappings());
    isomerCommandManager.addActionListener (this);
    addComponents();
    populateVTULL();    
    setSize (455, 310); 
    setLookAndFeel (isomerLookAndFeels->getCurrentIsomerLookAndFeel());
    mapWindow.setApplicationCommandManager (getApplicationCommandManager());
    valueTreeManager.openFromFile (File ("/Users/louise/Dropbox/code/juce/Isomer2/saves/default.isf"));
}

void MainContentComponent::populateVTULL()
{
    valueTreeManager.setVTULL (masterSection);
    valueTreeManager.setVTULL (transportSection);
    valueTreeManager.setVTULL (sequenceSection);
    valueTreeManager.setVTULL (multiTransport);
    
    valueTreeManager.setVTULL (*dynamic_cast <IsomerVTU*> (mapWindow.getMapGUI()));
    
    valueTreeManager.setVTULL (sequences);
}

MainContentComponent::~MainContentComponent()
{
    undoManager = nullptr;
    //scales = nullptr;
    //isomerLookAndFeels = nullptr;
    applicationCommandManager = nullptr;
    guiReceiver = nullptr;
    menuBar = nullptr;
    
    #if JUCE_MAC
    MenuBarModel::setMacMainMenu (nullptr);
    #endif
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (isomerLookAndFeels->getCurrentIsomerLookAndFeel()->getCurrentColourScheme().getUIColour (juce::LookAndFeel_V4::ColourScheme::windowBackground));
}

void MainContentComponent::addComponents()
{
    addAndMakeVisible (masterSection);
    addAndMakeVisible (transportSection);
    addAndMakeVisible (sequenceSection);
    
    addAndMakeVisible (menuBar = new MenuBarComponent (this));
    
    #if JUCE_MAC
    //menuBar->setModel (nullptr);
    setMacMainMenu (this);
    #endif
}

void MainContentComponent::resized()
{
    Rectangle<int> area (getLocalBounds());
    menuBar->setBounds (area.removeFromTop (LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
 
    transportSection.setBounds (area.removeFromLeft (145));
    masterSection.setBounds (area.removeFromTop (55));
    sequenceSection.setBounds (area);
}

    //-----APPLICATION MANAGER-----\\

ApplicationCommandManager& MainContentComponent::getApplicationCommandManager()
{
    if (applicationCommandManager == nullptr)
        applicationCommandManager = new ApplicationCommandManager();

    return *applicationCommandManager;
}

void MainContentComponent::handleAsyncUpdate()
{
    auto& commandManager = getApplicationCommandManager();
    commandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());
    commandManager.registerAllCommandsForTarget (&isomerCommandManager);
    commandManager.setFirstCommandTarget (&isomerCommandManager);
}

void MainContentComponent::actionListenerCallback (const String& s)
{
    if      (s == "save")           valueTreeManager.save();
    else if (s == "open")           valueTreeManager.open();
    else if (s == "undo")           valueTreeManager.undo();
    else if (s == "redo")           valueTreeManager.redo();
    else if (s == "skinLight")      lookAndFeelChanged ("light");
    else if (s == "skinDark")       lookAndFeelChanged ("dark");
    else if (s == "mainWindow")     openWindow ("main");
    else if (s == "mapWindow")      openWindow ("map");
    else if (s == "envelopeWind")   openWindow ("envelope");
    else if (s == "settingsWindow") openWindow ("settings");
}

    //-----MENUS-----\\

StringArray MainContentComponent::getMenuBarNames()
{
    StringArray names = {"File", "Edit", "View", "Window"};
    return StringArray (names);
}

PopupMenu MainContentComponent::getMenuForIndex (int menuIndex, const String& /*menuName*/)
{
    ApplicationCommandManager* commandManager = &getApplicationCommandManager();
    PopupMenu menu;

    if      (menuIndex == 0)
    {
        menu.addCommandItem (commandManager, IsomerCommandManager::save);
        menu.addCommandItem (commandManager, IsomerCommandManager::open);
        menu.addSeparator();
        menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    }
    
    else if (menuIndex == 1)
    {
        menu.addCommandItem (commandManager, IsomerCommandManager::undo);
        menu.addCommandItem (commandManager, IsomerCommandManager::redo);
    }
    
    else if (menuIndex == 2)
    {
        PopupMenu skinsSubMenu;
        skinsSubMenu.addCommandItem (commandManager, IsomerCommandManager::skinLight);
        skinsSubMenu.addCommandItem (commandManager, IsomerCommandManager::skinDark);
        
        menu.addSubMenu ("Skins", skinsSubMenu, true);
    }
    
    else if (menuIndex == 3)
    {
        menu.addCommandItem (commandManager, IsomerCommandManager::mainWindow);
        menu.addCommandItem (commandManager, IsomerCommandManager::mapWindow);
        menu.addCommandItem (commandManager, IsomerCommandManager::envelopeWindow);
        menu.addCommandItem (commandManager, IsomerCommandManager::settingsWindow);
    };

    return menu;
}

    //-----WINDOWS-----\\

void MainContentComponent::openWindow (const String s)
{
    if      (s == "main") this->getPeer()->toFront (true);
    else if (s == "map") 
    {
        if (mapWindow.isVisible()) mapWindow.toFront (true);
        else mapWindow.setVisible (true);     
    };
}