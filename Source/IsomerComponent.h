#pragma once
#include "IsomerObject.h"
#include "IsomerVTU.h"
#include "IsomerLookAndFeels.h"
#include "GUIReceiver.h"

class IsomerComponent   :   public IsomerVTU,
                            public Component
{
    public:
        IsomerComponent() {};
        ~IsomerComponent() {};
        
    protected:
        static ScopedPointer <GUIReceiver> guiReceiver; 
        static ScopedPointer <IsomerLookAndFeels> isomerLookAndFeels;
        
        static const bool isIntAndRange (const String& a, const int b, const int c)
        {
            int x = a.getIntValue();
            if (a.containsOnly ("0123456789") && x >= b && x <= c) return true;
            else return false;
        };
        
        static const bool isDoubleAndRange (const String a, const double b, const double c)
        {
            double x = a.getDoubleValue();
            if (a.containsOnly ("0123456789.") && x >= b && x <= c) return true;
            else return false;
        };
        
        void lookAndFeelChanged (const String s)
        {    
            isomerLookAndFeels->setLookAndFeelColourScheme (s);
            setLookAndFeel (isomerLookAndFeels->getCurrentIsomerLookAndFeel());
            repaint();
        };
};