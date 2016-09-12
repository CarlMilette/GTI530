/*
 * Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "EtherAppCliMod.h"

#include "EtherApp_m.h"
#include "Ieee802Ctrl_m.h"
#include "NodeOperations.h"
#include "ModuleAccess.h"
#include <vector>
#include <algorithm>

using namespace std;

Define_Module(EtherAppCliMod);

simsignal_t EtherAppCliMod::sentPkSignal = registerSignal("sentPk");
simsignal_t EtherAppCliMod::rcvdPkSignal = registerSignal("rcvdPk");
std::vector<std::string> EtherAppCliMod::macAddrList = {};

EtherAppCliMod::EtherAppCliMod()
{
    reqLength = NULL;
    respLength = NULL;
    sendInterval = NULL;
    timerMsg = NULL;
    nodeStatus = NULL;
}

EtherAppCliMod::~EtherAppCliMod()
{
    cancelAndDelete(timerMsg);
}

void EtherAppCliMod::initialize(int stage)
{
  cSimpleModule::initialize(stage);

  if (stage == 0)
    {

      reqLength = &par("reqLength");
      respLength = &par("respLength");
      sendInterval = &par("sendInterval");

      localSAP = par("localSAP");
      remoteSAP = par("remoteSAP");

      seqNum = 0;
      WATCH(seqNum);

      // statistics
      packetsSent = packetsReceived = 0;
      WATCH(packetsSent);
      WATCH(packetsReceived);

      startTime = par("startTime");
      stopTime = par("stopTime");
      if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
	error("Invalid startTime/stopTime parameters");

    }

  else if (stage == 2)
    {
      //Firmin 04-03-2015 **********************
      // This part has been added to choose destination mac address automaticaly
      //First we poor macAddrList with all nodes' mac addresses
      //
      cModule* macMod = this->getParentModule()->getSubmodule("mac",-1);
      string myMacAddr = macMod->getAncestorPar("address").stringValue();
      macAddrList.push_back(myMacAddr);
      //**********************
    }


  else if (stage == 3)
    {
      //Firmin 04-03-2015 **********************
      // This part has been added to choose destination mac address automaticaly.
      // The destination mac address is choosen randomly in the macAddrList, excluding the node's own mac address
      //
      if(par("autoDestAddress"))//If automatic destination address is activated
	{
	  int numSta = int(getModuleByPath("etherLan")->getAncestorPar("numEtherSta").doubleValue());
	  cModule* macMod = this->getParentModule()->getSubmodule("mac",-1);
	  string myMacAddr = macMod->getAncestorPar("address").stringValue();
	  int addrIdx = rand()%numSta;
	  //If the choosen destination address is our mac address, we choose another one.
	  while( macAddrList[addrIdx] == myMacAddr )
	    {
	      addrIdx = rand()%numSta;
	    }
	  par("destAddress").setStringValue(macAddrList[addrIdx].c_str());
	}
      //**********************

      if (isGenerator())
	timerMsg = new cMessage("generateNextPacket");

      nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));

      if (isNodeUp() && isGenerator())
	scheduleNextPacket(true);
    }
}

void EtherAppCliMod::handleMessage(cMessage *msg)
{

  if (!isNodeUp())
    throw cRuntimeError("Application is not running");
  if (msg->isSelfMessage())
    {
      if (msg->getKind() == START)
	{
	  bool registerSAP = par("registerSAP");
	  if (registerSAP)
	    registerDSAP(localSAP);
	  destMACAddress = resolveDestMACAddress();
	  // if no dest address given, nothing to do
	  if (destMACAddress.isUnspecified())
	    return;
	}
      sendPacket();
      scheduleNextPacket(false);
    }
  else
    receivePacket(check_and_cast<cPacket*>(msg));
}

bool EtherAppCliMod::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{

  Enter_Method_Silent();
  if (dynamic_cast<NodeStartOperation *>(operation)) {
      if (stage == NodeStartOperation::STAGE_APPLICATION_LAYER && isGenerator())
	scheduleNextPacket(true);
  }
  else if (dynamic_cast<NodeShutdownOperation *>(operation)) {
      if (stage == NodeShutdownOperation::STAGE_APPLICATION_LAYER)
	cancelNextPacket();
  }
  else if (dynamic_cast<NodeCrashOperation *>(operation)) {
      if (stage == NodeCrashOperation::STAGE_CRASH)
	cancelNextPacket();
  }
  else throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
  return true;
}

bool EtherAppCliMod::isNodeUp()
{
    return !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
}

bool EtherAppCliMod::isGenerator()
{
    return par("destAddress").stringValue()[0];
}

void EtherAppCliMod::scheduleNextPacket(bool start)
{
  simtime_t cur = simTime();
    simtime_t next;
    if (start)
    {
        next = cur <= startTime ? startTime : cur;
        timerMsg->setKind(START);
    }
    else
    {
        next = cur + sendInterval->doubleValue();
        timerMsg->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || next < stopTime)
        scheduleAt(next, timerMsg);
}

void EtherAppCliMod::cancelNextPacket()
{
    if (timerMsg)
        cancelEvent(timerMsg);
}

MACAddress EtherAppCliMod::resolveDestMACAddress()
{

  MACAddress destMACAddress;
    const char *destAddress = par("destAddress");
    if (destAddress[0])
    {
        // try as mac address first, then as a module
        if (!destMACAddress.tryParse(destAddress))
        {
            cModule *destStation = simulation.getModuleByPath(destAddress);
            if (!destStation)
                error("cannot resolve MAC address '%s': not a 12-hex-digit MAC address or a valid module path name", destAddress);

            cModule *destMAC = destStation->getSubmodule("mac");
            if (!destMAC)
                error("module '%s' has no 'mac' submodule", destAddress);

            destMACAddress.setAddress(destMAC->par("address"));
        }
    }
    return destMACAddress;
}

void EtherAppCliMod::registerDSAP(int dsap)
{
    EV << getFullPath() << " registering DSAP " << dsap << "\n";

    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDsap(dsap);
    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
    msg->setControlInfo(etherctrl);

    send(msg, "out");
}

void EtherAppCliMod::sendPacket()
{
    seqNum++;

    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);
    EV << "Generating packet `" << msgname << "'\n";

    EtherAppReq *datapacket = new EtherAppReq(msgname, IEEE802CTRL_DATA);

    datapacket->setRequestId(seqNum);

    long len = reqLength->longValue();
    datapacket->setByteLength(len);

    long respLen = respLength->longValue();
    datapacket->setResponseBytes(respLen);

    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setSsap(localSAP);
    etherctrl->setDsap(remoteSAP);
    etherctrl->setDest(destMACAddress);
    datapacket->setControlInfo(etherctrl);

    emit(sentPkSignal, datapacket);
    send(datapacket, "out");
    packetsSent++;
}

void EtherAppCliMod::receivePacket(cPacket *msg)
{
    EV << "Received packet `" << msg->getName() << "'\n";

    packetsReceived++;
    emit(rcvdPkSignal, msg);
    delete msg;
}

void EtherAppCliMod::finish()
{
    cancelAndDelete(timerMsg);
    timerMsg = NULL;
}
