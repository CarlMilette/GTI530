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

#include "sinkLab.h"
#include "sourceLabMsg_m.h"

Define_Module(SinkLab);

// Reçoit et détruit les messages.
// Enregistre les stats sur les paquets reçus. Ici on différencie les paquets avec la valeur du champ kind
void SinkLab::initialize()
{
    // Enregistrement des signaux utilis�s pour les stats.
    queue1PktSignal = registerSignal("paquetsQueue1");
    queue2PktSignal = registerSignal("paquetsQueue2");
    queue3PktSignal = registerSignal("paquetsQueue3");
    queue4PktSignal = registerSignal("paquetsQueue4");
}

void SinkLab::handleMessage(cMessage *msg)
{

  SourceLabMsg *msgArrive = check_and_cast<SourceLabMsg *>(msg);

priorite = msgArrive->getPriorite();

switch (priorite)
  {
    case 1:
      emit(queue1PktSignal, queue1PktServed);
    break;
    case 2:
      emit(queue2PktSignal, queue2PktServed);
        break;
    case 3:
      emit(queue3PktSignal, queue3PktServed);
        break;
    case 4:
          emit(queue4PktSignal, queue4PktServed);
            break;
    default:
    break;
  }

    delete msg;
}
