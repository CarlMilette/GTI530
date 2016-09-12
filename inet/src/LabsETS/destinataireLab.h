/*
 * destinataire.h
 *
 *  Created on: 29 mai 2015
 *      Author: firmin
 */

#ifndef DESTINATAIRELAB_H
#define DESTINATAIRELAB_H

#include <omnetpp.h>

/**
 * Fournir la description de votre module ici.
 */

class DestinataireLab : public cSimpleModule
{

public:
  //Constructeur

  //Destructeur

private:
  //Signaux permettant d'enregistrer les statistiques
    simsignal_t paquets3msSignal;
    simsignal_t paquets5msSignal;
    simsignal_t paquets10msSignal;

    int nbreMessages3ms = 0;// variable pour compter le nombre de paquets envoyes sur la sortie sortie3ms
    int nbreMessages5ms = 0;// variable pour compter le nombre de paquets envoyes sur la sortie sortie5ms
    int nbreMessages10ms = 0;// variable pour compter le nombre de paquets envoyes sur la sortie sortie10ms

protected:
  // Initialise les param�tres du module
  virtual void initialize();

  //Methode appel� � l'arriv�e d'un message dans le module
  virtual void handleMessage(cMessage *msg);

};

#endif /* DESTINATAIRELAB_H*/
