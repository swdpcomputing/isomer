#pragma once
#include "IsomerObject.h"

class IsomerLookAndFeel : public LookAndFeel_V4
{
    public:
        IsomerLookAndFeel (ColourScheme, const String);
        
        static ColourScheme getLightColourScheme(); 
        static ColourScheme getDarkColourScheme(); 
        const String& getColourSchemeId();
                
    private:
        void setupTextButton();
        Font getTextButtonFont (TextButton&, int) override;
        
        void setupLabel();
        void drawLabel (Graphics&, Label&) override;
        
        const String colourSchemeId;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IsomerLookAndFeel);
};

class IsomerLookAndFeels
{
    public:
        IsomerLookAndFeels();
        ~IsomerLookAndFeels() {};
        
        IsomerLookAndFeel* getCurrentIsomerLookAndFeel();
        void setLookAndFeelColourScheme (const String);
        
    private:
        void addLookAndFeels();
        
        OwnedArray <IsomerLookAndFeel> lookAndFeels;
        String currentIsomerLookAndFeel = "";
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IsomerLookAndFeels)
};