//! \file    thread_device_monitor.h
//! \brief   Thread de détéction de connections ou déconnections des périphériques.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __THREAD_DEVICE_MONITOR_H__
#define __THREAD_DEVICE_MONITOR_H__

#include "define.h"
#include "device.h"

//! \class CThreadDeviceMonitor
//! \brief Cette classe gère le thread qui surveille la connection des périphériques ou la déconnection.
class CThreadDeviceMonitor : public QThread
{
Q_OBJECT

public :

    //! \fn  CThreadDeviceMonitor (QObject *_parent = 0)
    //! \brief Constructeur.
    CThreadDeviceMonitor (QObject *_parent = 0);

    //! \fn  ~CThreadDeviceMonitor ()
    //! \brief Destructeur.
    ~CThreadDeviceMonitor ();

    //! \fn  void setListDeviceMonitor (QList<CDevice*> *_list_device_monitor)
    //! \brief Initialise la list de périphérique à surveiller.
    void setListDeviceMonitor (QList<CDevice*> *_list_device_monitor);

    //! \fn  void run()
    //! \brief Méthode du thread qui tourne en arrière plan.
    void run();

signals :

    //! \fn  void signalSearchPlugin ()
    //! \brief Signal qui emet à un CDevice de chercher un plugin valide pour le périphérique.
    void signalSearchPlugin ();

    //! \fn  void signalDisplaySearchPlugin   (CDevice *_device)
    //! \brief Signal qui permet de rafraichir l'interface.
    void signalDisplaySearchPlugin   (CDevice *_device);

private :

    QList<CDevice*>         *m_list_device_monitor;

};

#endif
