#pragma once
#include "IsomerObject.h"

class Directories
{
    public:
        static void setUserSaveDirectory (const String);
    
        static const String homeDirectory;
        static String userSaveDirectory;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Directories);
};