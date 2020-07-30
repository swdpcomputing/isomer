#pragma once
#include "IsomerObject.h"
#include "Directories.h"

class Save :    public Thread
{
    public:
        Save() :    Thread ("save", 0)
        {
        }

        ~Save()
        {
            stopThread (2000);
        }
        
        void run()
        {
            while (!threadShouldExit())
            {
                const MessageManagerLock mmLock;

                f.deleteFile();
                FileOutputStream fOS (f.withFileExtension (".isf"));
                vtToSave.writeToStream (fOS); 
                fOS.flush();
                end();
            };
        }
        
        void save (ValueTree vt, const String sd)
        {
            vtToSave = vt;
            FileChooser fC ("Choose a file to save...", File (sd), "*", true);
            
            if (fC.browseForFileToSave (true)) 
            {
                f = fC.getResult();
                startThread();
            };
        }
        
        void end()
        {
            signalThreadShouldExit();
        }
            
    private:
        ValueTree vtToSave;
        File f;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Save);
};