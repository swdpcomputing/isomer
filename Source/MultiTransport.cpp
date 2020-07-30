#include "MultiTransport.h"

MultiTransport::MultiTransport()
{
    createTransports();
}

MultiTransport::~MultiTransport()
{
}

void MultiTransport::updateValueTree()
{
    stopTimer();
    for (auto& o : transportArray) o->updateValueTree();
}

void MultiTransport::postUpdateValueTree()
{
    startTimer (3);  // also change the multiplier in Transport::setIndBPM
}

const double MultiTransport::getTickDiv (const String a)
{
    for (auto& o : transportArray)
    {
        if (o->getTransportID() == a) return o->getTickDiv();
    };
    
    return 0.0;
}

void MultiTransport::stopAllTransports()
{
    for (auto o : transportArray) o->stopTransport();
}

void MultiTransport::setMasterBPM (const double& a)
{
    for (auto o : transportArray) o->setMasterBPM (a);
}

void MultiTransport::createTransports()
{
    for (int i = 0; i < 9; ++i)
    {
        transportArray.add (new Transport (("transport" + String (i))));
    };
}

void MultiTransport::hiResTimerCallback()
{
    for (auto o : transportArray) o->masterCountFunc();
    //midiOutPtr->masterCountFunc();
}

    //-----ROUTE-----\\

void MultiTransport::routeChangeBPMPerc (const int a, const double b)
{
    getTransportPtr (a)->setBPMPerc (b);
}

void MultiTransport::routeStartTransport (const int a)
{
    getTransportPtr (a)->startTransport();
}

void MultiTransport::routeStopTransport (const int a)
{
    getTransportPtr (a)->stopTransport();
}

//void MultiTransport::routeAddLink (LinkWrapper* a)
//{
//    String s = a->getSendParameterType();
//    if      (s == "Time") routeCreateTimePointLink (a);
//    else if (s == "Pulse") routeCreatePulseLink (a);
//}
//
//void MultiTransport::routeCreateTimePointLink (LinkWrapper* a)
//{
//    preDesignateStringGet (a);
//    transportPtr->createTimePointLink (resourcesPtr->getLinkParentPtr (a->getReceiveObjectId()), a);
//}
//
//void MultiTransport::routeCreatePulseLink (LinkWrapper* a)
//{
//    preDesignateStringGet (a);
//    transportPtr->createPulseLink (resourcesPtr->getLinkParentPtr (a->getReceiveObjectId()), a);
//}
//
//void MultiTransport::preDesignateStringGet (LinkWrapper* a)
//{
//    designateTransportPtr (a->getSendObjectId().getLastCharacters (1).getIntValue());
//}

void MultiTransport::designateTransportPtr (const int a)
{
    //transportPtr.release();
    //transportPtr = getTransportPtr (a);
}

//LinkParent* MultiTransport::getLinkParentPtr (String a)
//{
//    for (auto o : transportArray) if (o->getTransportId() == a) return dynamic_cast <LinkParent*> (o);
//    return nullptr;
//}

Transport* MultiTransport::getTransportPtr (const int a)
{
    return transportArray.getUnchecked (a);
}

//IsomerObject* MultiTransport::getTransportPtrIO (int a)
//{
//    return getTransportPtr (a)->getIsomerPtr();
//}
