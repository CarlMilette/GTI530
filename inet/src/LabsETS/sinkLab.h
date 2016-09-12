//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SINKLAB_H
#define SINKLAB_H

#include <omnetpp.h>
#include "INETDefs.h"


/**
 * A module that just deletes every packet it receives, and collects
 * basic statistics (packet count, bit count, packet rate, bit rate).
 */
class SinkLab : public cSimpleModule
{
private:
    // Pour les stats
    simsignal_t queue1PktSignal;
    simsignal_t queue2PktSignal;
    simsignal_t queue3PktSignal;
    simsignal_t queue4PktSignal;
    int queue1PktServed = 0;// variable pour compter le nombre de paquets de queue1 traites.
    int queue2PktServed = 0;// variable pour compter le nombre de paquets de queue2 traites.
    int queue3PktServed = 0;// variable pour compter le nombre de paquets de queue3 traites.
    int queue4PktServed = 0;// variable pour compter le nombre de paquets de queue4 traites.
    int priorite = 0; // variable pour stocker la valeur du champ priorite

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
