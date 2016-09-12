/*
 * queueLab.h
 *
 *  Created on: 4 juin 2015
 *      Author: firmin
 */

#ifndef QUEUELAB_H
#define QUEUELAB_H

#include "INETDefs.h"
#include "PassiveQueueBase.h"
#include "IQueueAccess.h"
#include "sourceLabMsg_m.h"

/**
 * Passive FIFO Queue with unlimited buffer space.
 */
class QueueLab : public PassiveQueueBase, public IQueueAccess
{

private:
//  int actualLenght;

protected:
  // state
  cQueue queue;
  cGate *outGate;
  int byteLength;
//  int numPkInQ;
  int rcvdPkt;

  int actualLenght;

  SourceLabMsg *arrivedMsg = nullptr;

  // statistics
  static simsignal_t queueLengthSignal;

public:
  QueueLab() : outGate(NULL), byteLength(0) {}

  //Puts the first available paquet at the top of the queue
  // and make it ready to be sent
  virtual cMessage *dequeue();

  //Sends the paquet at the top of the the queue to the out gate
  virtual void sendOut(cMessage *msg);

  //Returns true if the queue is empty
  virtual bool isEmpty();

  virtual int getLength() const;

protected:
  virtual void initialize();

  virtual cMessage *enqueue(cMessage *msg);

  virtual int getByteLength() const { return byteLength; }
};

#endif /* QUEUELAB_H_ */
