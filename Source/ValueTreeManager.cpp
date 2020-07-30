#include "ValueTreeManager.h"

ScopedPointer <ValueTree> IsomerVTU::mainVT = new ValueTree ("mainVT");

ValueTreeManager::ValueTreeManager()
{
}

ValueTreeManager::~ValueTreeManager()
{
    mainVT.release();
}

void ValueTreeManager::addValueTrees()
{
    guiVT = ValueTree ("guiVT");
    transportVT = ValueTree ("transportVT");
    sequenceVT = ValueTree ("sequenceVT");
    
    mainVT->addChild (guiVT, -1, nullptr);
    mainVT->addChild (transportVT, -1, nullptr);
    mainVT->addChild (sequenceVT, -1, nullptr);
}

void ValueTreeManager::setVTULL (IsomerVTU& ivtu)
{
    valueTreeUserLL.add (&ivtu);
}

ValueTree ValueTreeManager::getMainValueTree()
{
    return *mainVT; // shouldn't need with ptr
}

void ValueTreeManager::save()
{
    saveObject.save (*mainVT, Directories::userSaveDirectory);
}

void ValueTreeManager::open()
{
    FileChooser fC ("Select File...", File (Directories::userSaveDirectory), "*.isf", true);
            
    if (fC.browseForFileToOpen()) openFromFile (fC.getResult());
}

void ValueTreeManager::openFromFile (const File& f)
{
    FileInputStream fIS (f);
    ValueTree newValueTree;
    
    if (! fIS.failedToOpen()) newValueTree = ValueTree::readFromStream (fIS);
                
    if (newValueTree.isValid()) 
    {
        mainVTObject = newValueTree.createCopy();
        mainVT = &mainVTObject;
        
        valueTreeUserLL.call (&IsomerVTU::updateValueTree);
        
        undoManager->clearUndoHistory();  
    }
    
    else addValueTrees();
    
    valueTreeUserLL.call (&IsomerVTU::postUpdateValueTree);
}

void ValueTreeManager::undo()
{  
    //printTree (*mainVT);
    undoManager->undo();
}

void ValueTreeManager::redo()
{
    undoManager->redo();
}