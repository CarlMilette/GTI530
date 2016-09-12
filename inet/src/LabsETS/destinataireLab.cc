/*
 * destinataire.cc
 *
 *  Created on: 29 mai 2015
 *      Author: firmin
 */

#include "destinataireLab.h"
#include "sourceLabMsg_m.h"

Define_Module(DestinataireLab);


void DestinataireLab::initialize()
{
    // Enregistrement des signaux utilises pour les stats
    paquets3msSignal = registerSignal("envoye3ms");
    paquets5msSignal = registerSignal("envoye5ms");
    paquets10msSignal = registerSignal("envoye10ms");
}

void DestinataireLab::handleMessage(cMessage *msg)
{
    SourceLabMsg *msgArrive = check_and_cast<SourceLabMsg *>(msg);

    // On lit la valeur du champ delaiMax et on la stocke dans une variable
    double delaiMax = msgArrive->getDelaiMax();

    // On calcule la valeur du tempsEcoule et on la stocke dans une variable

    double tempsEcoule = 1000*(msgArrive->getArrivalTime() - msgArrive->getCreationTime()).dbl();

    if(par("testConstraint"))
    {
        if(msg->arrivedOn("entree3ms"))
        {
            //	  ASSERT2(tempsEcoule + 3 <= delaiMax, "Contraintes DELAI MAX NON RESPECTEES!  Revoyez votre code." );
            emit(paquets3msSignal, nbreMessages3ms);
        }

        if(msg->arrivedOn("entree5ms"))
        {
            ASSERT2(tempsEcoule + 5 <= delaiMax, "Contraintes DELAI MAX NON RESPECTEES! Revoyez votre code." );
            emit(paquets5msSignal, nbreMessages5ms);
        }

        if(msg->arrivedOn("entree10ms"))
        {
            ASSERT2(tempsEcoule + 10 <= delaiMax,"Contraintes DELAI MAX NON RESPECTEES! Revoyez votre code." );
            emit(paquets10msSignal, nbreMessages10ms);
        }
    }
    delete(msg);

}
