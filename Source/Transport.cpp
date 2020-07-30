#include "Transport.h"

Transport::Transport (const String a) : transportID (a),
                                        bpmPropertyID (a + "BPM")
{
    // Need to add objectType to ValueTree as not received pointer yet to query LinkParentInfo
    countValue.setValue (var (-1));
}

Transport::~Transport()
{
    //mainVT.release();
}

void Transport::updateValueTree()
{
    stopTransport();
    ValueTree x = mainVT->getChildWithName ("transportVT").getChildWithName (transportID);
    
    if (x.isValid()) 
    {
        thisVT = x;
        updateVTProperties();
    }
    
    else  
    {
        thisVT = ValueTree (transportID);
        mainVT->getChildWithName ("transportVT").addChild (thisVT, -1, nullptr);
    };  
}

void Transport::updateVTProperties()
{
    bPMPerc = thisVT.getProperty (bpmPropertyID).operator double();
    setIndBPM();
}

const String Transport::getTransportID()
{
    return transportID;
}

const double Transport::getBPM()
{
    return indBPM;
}

const bool Transport::getIsTransportRunning()
{
    return isTransportRunning;
}

const double Transport::getTickDiv()
{
    return tickDiv;
}

void Transport::setMasterBPM (const double& a)
{
    masterBPM = a;
    setIndBPM();
}

void Transport::setBPMPerc (const double a)
{
    bPMPerc = (a / 100.0);
    setIndBPM();
    thisVT.setProperty (bpmPropertyID, var (bPMPerc), undoManager);
}

void Transport::setIndBPM()
{
    indBPM = masterBPM * bPMPerc;
    dMsPerQBeat = (60.0 / indBPM) * 1000.0;
    dMsPer16thBeat = dMsPerQBeat / 16.0;
    tickDiv = (960.0 / dMsPerQBeat);
    tickDivInterval = tickDiv * 3.0; // the multiplier is the hirestimer time set in multitransport
}

void Transport::masterCountFunc()
{
    if (isTransportRunning)
    {
        masterCount += tickDivInterval;
        
        if (masterCount > 60.0)
        {
            countFunc();           
            masterCount = masterCount - 60.0;
        };
        
        //sequenceLL.call (&Sequence::masterCountFunc, tickDivInterval);
        DBG (String (masterCount) << " " << masterBPM << " " << bPMPerc);
    };
}   

void Transport::startTransport()
{
    masterCount = 0.0;
    count = 0;
    countValue.setValue (var (0));
    isTransportRunning = true; 
}

void Transport::startTransport (const int a)
{
    masterCount = 0.0;
    count = a;
    countValue.setValue (var (a));
    isTransportRunning = true; 
}

void Transport::stopTransport()
{
    isTransportRunning = false;
}

void Transport::countFunc()
{
    count++;
    countValue.setValue (var (count));
}

    //-----SEQUENCE-----\\

//void Transport::addSequence (Sequence* a)
//{
//    sequenceLL.add (a);
//}
//
//void Transport::removeSequence (Sequence* a)
//{
//    sequenceLL.remove (a);
//}

    //-----NODES-----\\
    
//void Transport::linkCall (LinkWrapper* a)
//{   
//    String s = a->getReceiveParameterType();
//    
//    if      (s == "Start")
//    {
//        startTransport ((a->getReceiveVInt() * 16) + a->getReceiveVString().getIntValue());
//    }
//    
//    else if (s == "Stop") stopTransport();
//}
//
//void Transport::createTimePointLink (LinkParent* a, LinkWrapper* b)
//{
//    linkArray.add (new LinkTransportTime (b->getLinkID(), countValue, a, b));
//}
//
//void Transport::createPulseLink (LinkParent* a, LinkWrapper* b)
//{
//    linkArray.add (new LinkPulse (b->getLinkID(), countValue, a, b));
//}