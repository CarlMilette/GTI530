/*
 * queueLab.cc
 *
 *  Created on: 4 juin 2015
 *      Author: firmin
 */

#include "INETDefs.h"

#include "queueLab.h"


Define_Module(QueueLab);

simsignal_t QueueLab::queueLengthSignal = registerSignal("queueLength");

void QueueLab::initialize()
{
  PassiveQueueBase::initialize();
  queue.setName(par("queueName"));
  outGate = gate("out");
  rcvdPkt = 0;
  actualLenght = 0;
  WATCH(actualLenght);
  if (ev.isGUI())
          {
              char buf[40];
              sprintf(buf, "received: %d\nlength: %d",rcvdPkt, actualLenght );
              getDisplayString().setTagArg("t", 0, buf);
          }
}

cMessage *QueueLab::enqueue(cMessage *msg)
{
  SourceLabMsg *arrivedMsg = check_and_cast<SourceLabMsg *>(msg);
  queue.insert(arrivedMsg);
  emit(queueLengthSignal, queue.length());
  actualLenght = queue.length();
  rcvdPkt++;

  if (ev.isGUI())
      {
          char buf[40];
          sprintf(buf, "received: %d\nlength: %d",rcvdPkt, actualLenght );
          getDisplayString().setTagArg("t", 0, buf);
      }
  return NULL;
}

cMessage *QueueLab::dequeue()
{
  Enter_Method("dequeue()");

  if (queue.empty())
    {
      emit(queueLengthSignal, queue.length());
      actualLenght = queue.length();
    return NULL;
    }

  arrivedMsg = check_and_cast<SourceLabMsg *>(queue.pop());
  emit(queueLengthSignal, queue.length());
  actualLenght = queue.length();
  if (ev.isGUI())
          {
              char buf[40];
              sprintf(buf, "received: %d\nlength: %d",rcvdPkt, actualLenght );
              getDisplayString().setTagArg("t", 0, buf);
          }
  return arrivedMsg;
}

void QueueLab::sendOut(cMessage *msg)
{
  Enter_Method("sendOut()");
  actualLenght = queue.length();
  if (ev.isGUI())
        {
            char buf[40];
            sprintf(buf, "received: %d\nlength: %d",rcvdPkt, actualLenght);
            getDisplayString().setTagArg("t", 0, buf);
        }
  send(msg, outGate);
}


bool QueueLab::isEmpty()
{
  Enter_Method("isEmpty()");
  return queue.empty();
}

int QueueLab::getLength() const
{
  Enter_Method("getLength");
  return queue.getLength();
}

