#include "IsomerLookAndFeels.h"

    //-----ISOMERLOOKANDFEEL-----\\

IsomerLookAndFeel::IsomerLookAndFeel (ColourScheme cs, const String s)  :   colourSchemeId (s)
{
    this->setColourScheme (cs);
    setupLabel();
}

LookAndFeel_V4::ColourScheme IsomerLookAndFeel::getLightColourScheme()
{
    return
    {
        Colour (0xffffc9e3),    //windowBackground
        Colour (0xfff974b4),    //widgetBackground
        Colour (0xfff974b4),    //menuBackground
        Colour (0xff353535),    //outline
        Colour (0xff353535),    //defaultText
        Colour (0xfff974b4),    //defaultFill
        Colour (0xff000000),    //highlightedText
        Colour (0xfffffbfb),    //highlightedFill  
        Colour (0xff353535),    //menuText
    };
}

LookAndFeel_V4::ColourScheme IsomerLookAndFeel::getDarkColourScheme()
{
    return
    {
        Colours::blue,      //windowBackground
        Colours::lightgrey, //widgetBackground
        Colours::lightgrey, //menuBackground
        Colours::darkgrey,  //outline
        Colours::black,     //defaultText
        Colours::lightgrey, //defaultFill
        Colours::white,     //highlightedText
        Colours::darkgrey,  //highlightedFill  
        Colours::black,     //menuText
    };
}

const String& IsomerLookAndFeel::getColourSchemeId()
{
    return colourSchemeId;
}

void IsomerLookAndFeel::setupTextButton()
{
}

void IsomerLookAndFeel::setupLabel()
{
    setColour (Label::outlineColourId, Colours::darkgrey);
}

void IsomerLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));

    label.setJustificationType (Justification::centred);
    
    if (! label.isBeingEdited())
    {
        const Font font (getLabelFont (label));
        g.setFont (font);
        Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));

        g.drawFittedText (label.getText(), textArea, Justification::centred,
                          jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());
    }
    
    if (label.findParentComponentOfClass <ComboBox>() == nullptr) g.drawRect (label.getLocalBounds());
}

Font IsomerLookAndFeel::getTextButtonFont (TextButton& a, int b)
{
    int characterLength = a.getButtonText().length();
    double textHeight = 0.0f;
    double sizeMultiplier = static_cast <double> (b) - 8;
    
    switch (characterLength)
    {
        case (1):
            textHeight = 1.0f * sizeMultiplier; break;  
        case (2):
            textHeight = 0.88f * sizeMultiplier; break;
        case (3):
            textHeight = 0.76f * sizeMultiplier; break;
        case (4):
            textHeight = 0.64f * sizeMultiplier; break;  
        case (5):
            textHeight = 0.52f * sizeMultiplier; break;
        case (6):
            textHeight = 0.4f * sizeMultiplier; break;
        case (7):
            textHeight = 0.38f * sizeMultiplier; break;  
        case (8):
            textHeight = 0.26f * sizeMultiplier; break;
        case (9):
            textHeight = 0.14f * sizeMultiplier; break;
        default:
            textHeight = 12.0f * sizeMultiplier;            
    };
        
    return Font (textHeight);
}  

    //-----ISOMERLOOKANDFEELS-----\\
    
IsomerLookAndFeels::IsomerLookAndFeels()
{
    addLookAndFeels();
}
    
void IsomerLookAndFeels::addLookAndFeels()
{
    lookAndFeels.add (new IsomerLookAndFeel (IsomerLookAndFeel::getLightColourScheme(), "light"));
    lookAndFeels.add (new IsomerLookAndFeel (IsomerLookAndFeel::getDarkColourScheme(), "dark"));
    setLookAndFeelColourScheme ("light");
}
    
void IsomerLookAndFeels::setLookAndFeelColourScheme (const String s)
{
    currentIsomerLookAndFeel = s;
}

IsomerLookAndFeel* IsomerLookAndFeels::getCurrentIsomerLookAndFeel()
{
    for (auto& o : lookAndFeels) if (o->getColourSchemeId() == currentIsomerLookAndFeel) return o;
    assert (0); //should never not match the name of currentIsomerLookAndFeel
}