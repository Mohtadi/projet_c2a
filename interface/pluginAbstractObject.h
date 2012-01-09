//! \file    pluginAbstractObject.h
//! \brief   Classe abstraite des plugins.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_ABSTRACT_OBJECT_H__
#define __PLUGIN_ABSTRACT_OBJECT_H__

#include "pluginAbstract.h"


//! \class CPluginAbstractObject
//! \brief Classe abstraite qui contient la déclaration des méthodes génériques aux plugins pour les slots et signaux.
class CPluginAbstractObject : public QObject
{

public :

    public slots :

        //! \fn void slotReceiveData (QString&_data)
        //! \brief Slot connecté à cutecom pour les périphériques séries. Il reçoit toute les données du périphériques.
        virtual void slotReceiveData (QString &_data) = 0;

        //! \fn void slotSendData    ()
        //! \brief Le signal est émis depuis les services et apelle le slot, afin de renvoyer des actions a effectuer par le périphrique.
        //! \brief Le slot traite les actions à effectuer selon le service.
        virtual void  slotSendData    () = 0;

        //! \fn void slotDisconnect  ()
        //! \brief Méthode de déconnection, selon les cas il est nécessaire de surveiller le périphérique avec un timer. Il faut donc le connecter à un slot.
        virtual void slotDisconnect  () = 0;

    private :

    signals :

        //! \fn void signalDisconnect   (CPluginAbstract*)
        //! \brief Le signal est émis lorsque 'une déconnection est detectée.
        virtual void signalDisconnect   (CPluginAbstract*) = 0;

        //! \fn void signalUpdateServices ()
        //! \brief Lorsque des données sont reçues et rafraichit un signal est émis pour réactualiser l'application la liste des services et les services.
        virtual void signalUpdateServices () = 0;
};

#endif
