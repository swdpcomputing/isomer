#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class IsomerObject
{
    public:
        IsomerObject();
        ~IsomerObject(); 
        
        static const String genAN (const int a)
        {
            String all = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            String result = "";
            for (int i = 0; i < a; ++i)
            {
                int randomInt = Random::getSystemRandom().nextInt (all.length());
                result += all.substring (randomInt, randomInt + 1);
            }
            return result;
        };
};  