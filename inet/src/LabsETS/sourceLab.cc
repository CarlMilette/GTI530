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

#include "sourceLab.h"

Define_Module(SourceLab);

SourceLab::SourceLab()
{
}

SourceLab::~SourceLab()
{
}

void SourceLab::initialize()
{
    event= new cMessage("tempoMsg");
    scheduleAt(simTime(), event);
}

void SourceLab::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage())
    {
        //Reset gouvAffDom vector to all 0.
        std::fill(gouvAffDom.begin(), gouvAffDom.end(), 0);

        srcMsg = new SourceLabMsg("sourceMsg");


        if(par("colorGouvAffDom"))
        {
            //Put 1 to a random position of the gouvAffDom vector
            gouvAffDom.at(par("gouvAffDom")) = 1;
            srcMsg->setGouv(gouvAffDom[0]);
            srcMsg->setGouvUr(gouvAffDom[1]);
            srcMsg->setAff(gouvAffDom[2]);
            srcMsg->setAffUr(gouvAffDom[3]);
            srcMsg->setDom(gouvAffDom[4]);


            if(gouvAffDom[0]==1)
            {
                srcMsg->setKind(12);// colorize gouv packet
                srcMsg->setPriorite(3);
            }
            else if (gouvAffDom[1]==1)
            {
                srcMsg->setKind(9); // colorize gouvUr packet in green
                srcMsg->setPriorite(1);
            }
            else if (gouvAffDom[2]==1)
            {
                srcMsg->setKind(13); // colorize aff packet
                srcMsg->setPriorite(3);
            }
            else if (gouvAffDom[3]==1)
            {
                srcMsg->setKind(10); // colorize affUr packet in blue
                srcMsg->setPriorite(2);
            }
            else if (gouvAffDom[4]==1)
            {
                srcMsg->setKind(14); // colorize dom packet
                srcMsg->setPriorite(4);
            }
            else
                srcMsg->setKind(0);
        }
        else if(par("colorUrgent"))
        {
            if( par("doubleUrgent").doubleValue() == 0)
                srcMsg->setUrgent(false);
            if( par("doubleUrgent").doubleValue() == 1)
            {
                srcMsg->setUrgent(true);
                srcMsg->setKind(9);// colorize urgent packet in green
            }
        }
        else
        {
            // Set srcMsg field
            srcMsg->setDelaiMax(par("delaiMax"));
            //            srcMsg->setTempsEcoule(par("tempsEcoule"));
            srcMsg->setKind(par("messageKind"));
            srcMsg->setPriorite(par("priorite"));
        }

        if(par("delaiMessages"))
        {
            double delai= par("delaiEnvoi");
            sendDelayed(srcMsg,0.001*delai,"sortie");
        }
        else
            send(srcMsg,"sortie");

        delete msg;



        //Reset gouvAffDom vector to all 0.
        std::fill(gouvAffDom.begin(), gouvAffDom.end(), 0);

        event= new cMessage("tempoMsg");
        scheduleAt(simTime()+ par("interArrivalTime"), event);
    }
}



void SourceLab:: reduireTauxMessage()
{
    Enter_Method("reduireTauxMessage()");

    par("interArrivalTime").setDoubleValue(par("interArrivalTime").doubleValue()*2);
}

void SourceLab:: augmenterTauxMessage()
{
    Enter_Method("augmenterTauxMessage()");

    par("interArrivalTime").setDoubleValue(par("interArrivalTime").doubleValue()/2);
}
