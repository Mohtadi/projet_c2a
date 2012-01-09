//! \brief   Classe de device
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "define.h"

//! \class CDevice
//! \brief Conteneur pour les périphériques. L'application utilise une liste de CDevice ou chaque CDevice représente un périphérique à surveiller. Lorsqu'un périphérique est détecté, un plugin lui est attaché.
class CDevice : public QObject
{
Q_OBJECT
public :

    //! \fn  CDevice (QString _device , QList<CPluginAbstract*> * _list_plugins = NULL , QObject *_parent = 0)
    //! \brief Constructeur
    CDevice (QString _device , QList<CPluginAbstract*> * _list_plugins = NULL , QObject *_parent = 0);

    //! \fn  CDevice (const CDevice &_device , QObject *_parent = 0)
    //! \brief Constructeur
    CDevice (const CDevice &_device , QObject *_parent = 0);

    //! \fn  ~CDevice ()
    //! \brief Destructeur
    ~CDevice ();

    //! \fn  QString getDevice()
    //! \brief Renvoi le nom du périphérique à surveiller. Par exemple /dev/ttyUSB0
    QString getDevice();

    //! \fn  CPluginAbstract *getPlugin()
    //! \brief Renvoi le plugin associé, NULL si il y a aucun plugin d'associé.
    CPluginAbstract *getPlugin();

public slots :

    //! \fn  void slotSearchPlugin   ()
    //! \brief Slot qui lance la recherche d'un plugin adapté au périphérique.
    void slotSearchPlugin   ();

    //! \fn  void slotDisconnect     (CPluginAbstract* _abstract_plugin)
    //! \brief Slot qui est apellé lorsqu'un plugin detecte une déconnection.
    void slotDisconnect     (CPluginAbstract* _abstract_plugin);

    //! \fn  void slotUpdateServices ()
    //! \brief Le périphérique reçoit des données à transmettre aux services, le slot est apellé depuis les plugins.
    void slotUpdateServices ();

signals :

    //! \fn  void signalUpdateTreeWidgetDeviceMonitor (CDevice *)
    //! \brief Signal qui apelle la mise à jour de l'interface pour actualiser les données reçuent du périphérique.
    void signalUpdateTreeWidgetDeviceMonitor (CDevice *);

private:

    QString m_device;

    CPluginAbstract *m_plugin;

    QList<CPluginAbstract*> *m_list_plugins;

    QList<CPluginAbstract*>  m_list_plugins_valid;
};

#endif
