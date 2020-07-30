#include "GUIReceiver.h"

GUIReceiver::~GUIReceiver()
{
    multiTransport.release();
    sequences.release();
}

void GUIReceiver::setObjectPointers (MultiTransport& mt, Sequences& ns)
{
    multiTransport = &mt;
    sequences = &ns;
}

    //-----MASTER-----\\
    
void GUIReceiver::masterScaleSelected (const String& a)
{
}

void GUIReceiver::masterKeySelected (const String& a)
{
}

void GUIReceiver::masterKeyNumSelected (const int a)
{
}

void GUIReceiver::masterBPMSelected (const double& a)
{
    multiTransport->setMasterBPM (a);
}

    //-----TRANSPORT-----\\
    
void GUIReceiver::startButtonPressed (const int a)
{
    multiTransport->routeStartTransport (a);
}

void GUIReceiver::stopButtonPressed (const int a)
{
    multiTransport->routeStopTransport (a);
}

void GUIReceiver::bpmLabelChanged (const int a, const double& b)
{
    bpmArray.set (a, b);
    multiTransport->routeChangeBPMPerc (a, b);
}

    //-----SEQUENCE-----\\
        
void GUIReceiver::newSequenceButtonPressed()
{
    sequences->addSequenceNew();
}

void GUIReceiver::openSequenceButtonPressed()
{
    DBG ("openSequenceButtonPressed");
}

void GUIReceiver::deleteSequenceButtonPressed()
{
    sequences->deleteSequence (selectedSequence);
}

void GUIReceiver::copySequenceButtonPressed()
{
    DBG ("copySequenceButtonPressed");
}

void GUIReceiver::newSequenceUserIdLabelChanged (const String& a)
{
    sequences->setNewSequenceUserId (a);
}

void GUIReceiver::numberOfNotesLabelChanged (const int a)
{
    sequences->setNewSequenceNumNotes (a);
}

void GUIReceiver::lengthBeatsLabelChanged (const int a)
{
    sequences->setNewSequenceLengthBeats (a);
}

void GUIReceiver::lengthDivisionsSelected (const int a)
{
    sequences->setNewSequenceLengthDivisions (a);
}

void GUIReceiver::sequenceSelected (const String& a)
{
    selectedSequence = a;
}

    //-----NODE SELECTION-----\\
    
void GUIReceiver::sendObjectSelected (const String& a)
{
    sendObject = a;
}

void GUIReceiver::sendParameterSelected (const String& a)
{
    sendParameter = a;
}

void GUIReceiver::sendVIntSelected (const int a)
{
    sendVInt = a;
}

void GUIReceiver::sendVStringSelected (const String& a)
{
    sendVString = a;
}

void GUIReceiver::sendVString2Selected (const String& a)
{
    sendVString2 = a;
}

void GUIReceiver::receiveObjectSelected (const String& a)
{
    receiveObject = a;
}

void GUIReceiver::receiveParameterSelected (const String& a)
{
    receiveParameter = a;
}

void GUIReceiver::receiveVIntSelected (const int a)
{
    receiveVInt = a;
}

void GUIReceiver::receiveVStringSelected (const String& a)
{
    receiveVString = a;
}

void GUIReceiver::receiveVString2Selected (const String& a)
{
    receiveVString2 = a;
}

const String& GUIReceiver::getSendObject()
{
    return sendObject;
}

const String& GUIReceiver::getSendParameter()
{
    return sendParameter;
}

const int GUIReceiver::getSendVInt()
{
    return sendVInt;
}

const String& GUIReceiver::getSendVString()
{
    return sendVString;
}

const String& GUIReceiver::getSendVString2()
{
    return sendVString2;
}

const String& GUIReceiver::getReceiveObject()
{
    return receiveObject;
}

const String& GUIReceiver::getReceiveParameter()
{
    return receiveParameter;
}

const int GUIReceiver::getReceiveVInt()
{
    return receiveVInt;
}

const String& GUIReceiver::getReceiveVString()
{
    return receiveVString;
}

const String& GUIReceiver::getReceiveVString2()
{
    return receiveVString2;
}

NodeData* GUIReceiver::createMapNodeIcon (const String& s, const int x, const int y)
{
    
    return nullptr;
}