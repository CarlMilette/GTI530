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

#ifndef SOURCELAB_H
#define SOURCELAB_H

#include <omnetpp.h>
#include "sourceLabMsg_m.h"
#include <vector>

/**
 *Générateur de messages. les messages ont des champs indiqués dans le fichier sourceLabMsg.msg
 */
class SourceLab : public cSimpleModule
{
public:
  SourceLab();
  virtual ~SourceLab();

 virtual void reduireTauxMessage();
 virtual void augmenterTauxMessage();

private:
  SourceLabMsg* srcMsg = nullptr;
  cMessage* event = nullptr; // pointer to the cMessage object. Will be used for timing
  double interArrivalTime = 0;
  std::vector<int> gouvAffDom = {0,0,0,0,0};


protected:
  virtual void initialize();
  virtual void handleMessage(cMessage* msg);
};

#endif
