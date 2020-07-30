#include "Sequences.h"
//#include "LinkWrapper.h"

Sequences::Sequences()
{
}

Sequences::~Sequences()
{
}

void Sequences::updateValueTree()
{
    ValueTree x = mainVT->getChildWithName ("sequenceVT");
    
    if (x.isValid()) 
    {
        thisVT = x;
        updateVTProperties();
    }
    
    else  
    {
        thisVT = ValueTree ("sequenceVT");
        mainVT->addChild (thisVT, -1, nullptr);
    };   
}

    //-----SETTERS-----\\
    
void Sequences::setNewSequenceUserId (const String& a)
{
    newSequenceUserId = a;
}

void Sequences::setNewSequenceNumNotes (const int a)
{
    newSequenceNumNotes = a;
}

void Sequences::setNewSequenceLengthBeats (const int a)
{
    newSequenceLengthBeats = a;
}

void Sequences::setNewSequenceLengthDivisions (const int a)
{
    newSequenceLengthDivisions = a;
}

//void Sequences::updateSequenceEditGUIPtr()
//{
//    sequenceEditGUIPtr.release();
//    sequenceEditGUIPtr = sequenceEditWindowPtr->getSequenceEditGUIPtr();
//    if (sequenceEditGUIPtr != nullptr) sequenceEditGUIPtr->updateGUI();
//}
//
//    //-----VALUETREE-----\\

void Sequences::postUpdateValueTree()
{
    mainVT->addListener (this);
}

void Sequences::valueTreeChildAdded (ValueTree& parentVT, ValueTree& addedVT)
{
    DBG ("Sequences::valueTreeChildAdded");
    
    if (parentVT.getType().toString() == "sequenceVT")
    {
        DBG ("Sequences::valueTreeChildAdded2");
        if (isNewTransaction == false) addSequenceRedo (addedVT);
    };
    
    isNewTransaction = false;
}

void Sequences::valueTreeChildRemoved (ValueTree& parentVT, ValueTree& removedVT, int)
{
    DBG ("Sequences::valueTreeChildRemoved");
    
    if (parentVT.getType().toString() == "sequenceVT")
    {
        if (isNewTransaction == false) 
        {
            deleteSequence (removedVT.getProperty ("sequenceId"));
            DBG ("Sequences::valueTreeChildRemoved2");
        };
    };
    
    isNewTransaction = false;
}

//void Sequences::setValueTree (ValueTree& a)
//{  
//    globalVT = a.getChildWithName ("globalVT");
//    globalVT.addListener (dynamic_cast <ValueTreeListener*> (this));
//    sequenceVT = a.getChildWithName ("sequenceVT");
//    sequenceVT.addListener (dynamic_cast <ValueTreeListener*> (this));
//}
//
//void Sequences::valueTreeChildAdded (ValueTree& a, ValueTree& b)
//{
//    String pvtId = a.getType().toString();
//    String vtId = b.getType().toString(); 
//    
//    if (pvtId == "sequenceVT") 
//    {
//        if (newAddSequenceTransaction == false) addSequenceRedo (b);
//        newAddSequenceTransaction = false;     
//    };
//}
//
//void Sequences::valueTreeChildRemoved (ValueTree& a, ValueTree& b , int c)
//{
//    String pvtId = a.getType().toString();
//    String vtId = b.getType().toString(); 
//    
//    if (pvtId == "sequenceVT") 
//    {
//        if (newDeleteSequenceTransaction == false) deleteSequenceRedo (b);
//        newDeleteSequenceTransaction = false;  
//    };
//}
//
//void Sequences::valueTreePropertyChanged (ValueTree& a, const Identifier& b)
//{
//    String pvtId = a.getParent().getType().toString();
//    String vtId = a.getType().toString();
//    String id = b.toString(); 
//    
//    if      (vtId == "globalVT" && id == "globalKey")
//    {
//        globalKey.setValue (globalVT.getProperty ("globalKey"));
//    }
//    
//    else if (vtId == "globalVT" && id == "globalScale")
//    {
//        globalScale.setValue (globalVT.getProperty ("globalScale"));        
//    }
//    
//    else if (vtId == "globalVT" && id == "masterBPM") 
//    {
//        masterBPM.setValue (globalVT.getProperty ("masterBPM")); //Delete master? removed from Sequence as not needed
//    }
//    
//    else if (pvtId == "sequenceVT")
//    {
//        if (newChangeSequenceTransaction == false) 
//        {
//            changeSequenceRedo (id, a, a.getProperty ("sequenceId"));
//        };
//        
//        newChangeSequenceTransaction = false;
//    };
//    
//    updateSequenceEditGUIPtr();
//}

    //-----ADD/DELETE/CHANGE NOTESEQUENCE-----\\

void Sequences::addSequenceNew()
{
    bool sequenceExists = checkIfSequenceUserIdExists();
    const String newSequenceId = getNewSequenceId();
    if (sequenceExists == true) newSequenceUserId = newSequenceId;
    isNewTransaction = true;
    sequenceArray.add   (new Sequence   (   newSequenceId,
                                            newSequenceUserId,
                                            newSequenceNumNotes,
                                            newSequenceLengthBeats,
                                            newSequenceLengthDivisions
                                        )
                        ); 

    undoManager->beginNewTransaction();
    mainVT->getChildWithName ("sequenceVT").addChild (sequenceArray.getLast()->getSequenceVT(), -1, undoManager);
    //isNewTransaction = false;
}

void Sequences::addSequenceRedo (ValueTree vt)
{
    sequenceArray.add (new Sequence (vt));
}

void Sequences::deleteSequence (const String& a)
{
    for (auto& o : sequenceArray) 
    {
        if (o->getSequenceUserId() == a) 
        {
            isNewTransaction = true;
            DBG ("Delete Sequence");
            undoManager->beginNewTransaction();
            mainVT->getChildWithName ("sequenceVT").removeChild (o->getSequenceVT(), undoManager);
            sequenceArray.removeObject (o, true);
            return;
        };
    };
    
    //isNewTransaction = false;
}

const bool Sequences::checkIfSequenceUserIdExists()
{
    for (auto& o : sequenceArray) 
    {
        if (o->getSequenceUserId() == newSequenceUserId) return true;
    }
    
    return false;
}

const String Sequences::getNewSequenceId()
{
    return "sequence" + IsomerObject::genAN (8);
}

//void Sequences::addSequenceVT (ValueTree a)
//{
//    undoManagerPtr->beginNewTransaction();
//    sequenceVT.addChild (a, -1, undoManagerPtr); 
//}
//
//void Sequences::addSequenceRedo (ValueTree a)
//{
//    ScopedPointer <Sequence> newNSPtr = sequenceArray.add (new Sequence (   a, 
//                                                                                        globalKey,
//                                                                                        globalScale,
//                                                                                        midiOutPtr.get(),
//                                                                                        resourcesPtr.get(),
//                                                                                        this
//                                                                                    ));
//   resourcesPtr->registerLinkParent (newNSPtr->getSequenceId(), newNSPtr->getSequenceUserId()); 
//   sendUserIdsToGUI();
//   newNSPtr.release();
//}
//
//void Sequences::addSequencesFromVT()
//{
//    sequenceArray.clear();
//    
//    for (auto o : sequenceVT) 
//    {
//        //MyFunctions::printAllProperties (o);
//        addSequenceRedo (o);
//    };
//}
//
//void Sequences::deleteSequenceNew (const String a)
//{
//    if (a != "")
//    {
//        resourcesPtr->deRegisterLinkParent (getIdFromUserId (a));
//        newDeleteSequenceTransaction = true; 
//        deleteSequenceVT (getIdFromUserId (a));
//        sequenceArray.removeObject (getSequenceFromUserId (a));
//        sendUserIdsToGUI();
//    };
//}
//
//void Sequences::deleteSequenceVT (const String a)
//{
//    undoManagerPtr->beginNewTransaction();
//    sequenceVT.removeChild (sequenceVT.getChildWithName (a), undoManagerPtr);
//}
//        
//void Sequences::deleteSequenceRedo (ValueTree a)
//{
//    resourcesPtr->deRegisterLinkParent (a.getProperty ("sequenceId").toString());
//    sequenceArray.removeObject (getSequence (a.getProperty ("sequenceId")));
//    sendUserIdsToGUI();
//}
//
//void Sequences::copySequence (const String a, const String b)
//{
//    ScopedPointer <Sequence> newNSPtr = sequenceArray.add (new Sequence (*getSequenceFromUserId (a)));
//    newNSPtr->setSequenceId (createNewSequenceId());
//    newNSPtr->setSequenceUserId (checkNewSequenceUserId (newSequenceUserId));
//    
//    resourcesPtr->registerLinkParent (newNSPtr->getSequenceId(), newNSPtr->getSequenceUserId());
//    ++numSequencesCreated; 
//    sendUserIdsToGUI();
//    
//    newAddSequenceTransaction = true;
//    addSequenceVT (newNSPtr->getSequenceVT());
//    newNSPtr.release();
//}
//
//void Sequences::changeSequenceNew (Sequence* a, const String b)
//{
//    newChangeSequenceTransaction = true;
//    undoManagerPtr->beginNewTransaction();
//    ValueTree nsvt = getSequenceVT (a->getSequenceId()); 
//    
//    if      (b == "sequenceUserId") 
//    {
//        nsvt.setProperty ("sequenceUserId", a->getSequenceUserId(), undoManagerPtr);
//        resourcesPtr->editLinkParent (a->getSequenceId(), a->getSequenceUserId());
//    }
//    else if (b == "numberOfNotes")      nsvt.setProperty ("numberOfNotes", a->getNumberOfNotes(), undoManagerPtr);
//    else if (b == "root")               nsvt.setProperty ("root", a->getRoot(), undoManagerPtr);
//    else if (b == "key")                nsvt.setProperty ("key", a->getKey(), undoManagerPtr);
//    else if (b == "octave")             nsvt.setProperty ("octave", a->getOctave(), undoManagerPtr);
//    else if (b == "keyLock")            nsvt.setProperty ("keyLock", a->getKeyLock(), undoManagerPtr);
//    else if (b == "scale")              nsvt.setProperty ("scale", a->getScale(), undoManagerPtr);
//    else if (b == "scaleLock")          nsvt.setProperty ("scaleLock", a->getScaleLock(), undoManagerPtr);
//    else if (b == "lengthTicks")        nsvt.setProperty ("lengthTicks", a->getLengthTicks(), undoManagerPtr);
//    else if (b == "isSequenceLooping")  nsvt.setProperty ("isSequenceLooping", a->getIsSequenceLooping(), undoManagerPtr);
//    else if (b == "pitchArray")         nsvt.setProperty ("pitchArray", a->getPitchArrayVar(), undoManagerPtr);
//    else if (b == "velocityArray")      nsvt.setProperty ("velocityArray", a->getVelocityArrayVar(), undoManagerPtr);
//    else if (b == "noteTimesArray")     nsvt.setProperty ("noteTimesArray", a->getNoteTimesArrayVar(), undoManagerPtr);
//    else if (b == "noteLengthArray")    nsvt.setProperty ("noteLengthArray", a->getNoteLengthArrayVar(), undoManagerPtr);
//    else if (b == "midiChannelArray")   nsvt.setProperty ("midiChannelArray", a->getMidiChannelArrayVar(), undoManagerPtr);
//    else if (b == "allArrays")
//    {
//        nsvt.setProperty ("pitchArray", a->getPitchArrayVar(), undoManagerPtr);
//        nsvt.setProperty ("velocityArray", a->getVelocityArrayVar(), undoManagerPtr);
//        nsvt.setProperty ("noteTimesArray", a->getNoteTimesArrayVar(), undoManagerPtr);
//        nsvt.setProperty ("noteLengthArray", a->getNoteLengthArrayVar(), undoManagerPtr);
//        nsvt.setProperty ("midiChannelArray", a->getMidiChannelArrayVar(), undoManagerPtr);
//        nsvt.setProperty ("root", a->getRoot(), undoManagerPtr);
//        nsvt.setProperty ("numberOfNotes", a->getNumberOfNotes(), undoManagerPtr);
//    };
//    
//    //updateSequenceEditGUIPtr(); // May be inefficient due to calls from sequenceEditGUIPtr updating sequenceEditGUIPtr twice. However, useful for updating the gui view from anywhere else but itself
//}
//
//void Sequences::changeSequenceRedo (const String a, ValueTree b, const String c) // Same for mni & links?????
//{
//    if      (a == "sequenceUserId") getSequence (c)->setSequenceUserId (b.getProperty ("sequenceUserId").toString());
//    else if (a == "root")               getSequence (c)->setRoot (b.getProperty ("root").operator int());
//    else if (a == "numberOfNotes")      getSequence (c)->setNumberOfNotes (b.getProperty ("numberOfNotes").operator int());
//    else if (a == "key")                getSequence (c)->setKey (b.getProperty ("key"));
//    else if (a == "octave")             getSequence (c)->setOctave (b.getProperty ("octave"));
//    else if (a == "keyLock")            getSequence (c)->setKeyLock (b.getProperty ("keyLock").operator bool());
//    else if (a == "scale")              getSequence (c)->setScale (b.getProperty ("scale").toString());
//    else if (a == "scaleLock")          getSequence (c)->setScaleLock (b.getProperty ("scaleLock").operator bool());
//    else if (a == "lengthTicks")        getSequence (c)->setLengthTicks (b.getProperty ("lengthTicks").operator int());
//    else if (a == "isSequenceLooping")  getSequence (c)->setIsSequenceLooping (b.getProperty ("isSequenceLooping"));
//    else if (a == "pitchArray")         getSequence (c)->setPitchArray (b.getProperty ("pitchArray"));
//    else if (a == "velocityArray")      getSequence (c)->setVelocityArray (b.getProperty ("velocityArray"));
//    else if (a == "noteTimesArray")     getSequence (c)->setNoteTimesArray (b.getProperty ("noteTimesArray"));
//    else if (a == "noteLengthArray")    getSequence (c)->setNoteLengthArray (b.getProperty ("noteLengthArray"));
//    else if (a == "midiChannelArray")   getSequence (c)->setMidiChannelArray (b.getProperty ("midiChannelArray"));
//}
//
//    //-----NOTE CREATION-----\\
//    
//
//void Sequences::calcSequenceLengthTicks()
//{
//    newSequenceLengthTicks = (newSequenceLengthBeats * 960) + (newSequenceLengthDivisions * 60);
//}
//
//const String Sequences::createNewSequenceId()
//{
//    return "Sequence " + String (numSequencesCreated);
//}
//
//const String Sequences::checkNewSequenceUserId (const String a)
//{
//    for (auto o : sequenceArray)
//    {
//        if (o->getSequenceUserId() == a) return MyFunctions::sGen ("Sequence", 8);
//    };
//    
//    return a;
//}
//
//void Sequences::createAllArrays()
//{
//    createPitchArray();
//    createVelocityArray(); 
//    createNoteStartArray();          
//    createNoteLengthArray();
//    createMidiChannelArray();
//}
//
//    //-----GET FUNCTIONS-----\\
//  
//int Sequences::getIndSequenceNumNotes (String a)
//{
//    for (auto o : sequenceArray) if (o->getSequenceId() == a) return o->getNumberOfNotes();
//    return 0;
//}
//
//void Sequences::sendUserIdsToGUI()
//{
//    sequenceUserIds.clear();
//    for (auto o : sequenceArray) sequenceUserIds.add (o->getSequenceUserId());
//    guiPtr->setSequenceIds (sequenceUserIds);
//    mapInterfacePtr->updateObjectComboBoxes();
//}
//
//const String Sequences::getIdFromUserId (const String a)
//{
//    for (auto o : sequenceArray) if (o->getSequenceUserId() == a) return o->getSequenceId();
//    return "";
//}
//
//Sequence* Sequences::getSequence (const String a)
//{
//    for (auto o : sequenceArray) if (o->getSequenceId() == a) return o;
//    return nullptr;
//}
//
//Sequence* Sequences::getSequenceFromUserId (const String a)
//{
//    for (auto o : sequenceArray) if (o->getSequenceUserId() == a) return o;
//    return nullptr;
//}
//
//ValueTree Sequences::getSequenceVT (const String a)
//{
//    return sequenceVT.getChildWithName (a);
//}
//
//LinkParent* Sequences::getLinkParentPtr (String a)
//{
//    for (auto o : sequenceArray) if (o->getSequenceId() == a) return dynamic_cast <LinkParent*> (o);
//    return nullptr;
//}
//
//    //-----ROUTE FUNCTIONS-----\\
//    
//void Sequences::routeAddLink (LinkWrapper* a)
//{
//    String s = a->getSendParameterType();
//    if (s == "Note Played") routeCreateNotePlayedLink (a);
//}
//
//void Sequences::routeCreateNotePlayedLink (LinkWrapper* a)
//{
//    getSequence (a->getSendObjectId())->createNotePlayedLink (resourcesPtr->getLinkParentPtr (a->getReceiveObjectId()), a);
//}
//
//    //-----MISC-----\\
//    
//void Sequences::panicButtonPressed()
//{
//    midiOutPtr->panicButtonPressed();
//}
