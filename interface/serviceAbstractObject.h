//! \file    Classe abstraite des services pour gérer les signaux et slots.
//! \brief   Classe abstraite des plugins.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __SERVICE_ABSTRACT_OBJECT_H__
#define __SERVICE_ABSTRACT_OBJECT_H__

#include "serviceAbstract.h"

//! \class CServiceAbstractObject
//! \brief Classe abstraite qui contient la déclaration des signaux et slots des services.
class CServiceAbstractObject : public QObject
{
public slots :

    //! \fn  void slotUpdate()
    //! \brief Slot appelé par l'application lorsqu'une mise à jour des données est nécessaire. Utilisé pour actualiser le widget du service.
    virtual void slotUpdate() = 0;

signals :

    //! \fn  void signalSendData()
    //! \brief Signal envoyé au plugin pour envoyer des informations au périphériques. Le gprs par exemple utilise un protocole de communication. Les données sont transmise par l'intermédiaire de la liste de données.
    virtual void signalSendData() = 0;

};

#endif
