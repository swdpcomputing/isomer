#include "Directories.h"

const String Directories::homeDirectory = File::getSpecialLocation (File::SpecialLocationType::userHomeDirectory).getFullPathName();
String Directories::userSaveDirectory = "/Users/louise/Dropbox/code/juce/Isomer2/saves";

void Directories::setUserSaveDirectory (const String s)
{
    userSaveDirectory = s;
}