//! \file    plugin_bluetooth.h
//! \brief   Plugin de périphériques bluetooth. Utilise la librairie obexFtp et blueZ.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_BLUETOOTH_H__
#define __PLUGIN_BLUETOOTH_H__

#include<QtGui>

#include "../../interface/pluginAbstract.h"
#include "../../interface/pluginAbstractObject.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bluetooth/bluetooth.h"
#include "bluetooth/hci.h"
#include "bluetooth/hci_lib.h"
#include <bluetooth/rfcomm.h>


#include <string.h>

#include <obexftp/client.h>

//! \class CPluginBluetoothThread
//! \brief Ce thread surveille et détecte les périphériques bluetooth.
class CPluginBluetoothThread : public QThread
{
   Q_OBJECT

public :

    CPluginBluetoothThread();

    ~CPluginBluetoothThread();

    void setDeviceId (int _device_id);

    void setSocketId (int _socket_id);

    void setListDataPlugin (CListDataPlugin *_data_informations);

protected:

       void run();

signals :

        void signalThread();

private :

    bool m_stop;

    int m_device_id;

    int m_socket_id;

    CListDataPlugin * m_list_data_plugin;

    QStringList m_list_peripherique;
};

//! \class CPluginBluetoothThreadSendFile
//! \brief Ce thread est lancé lors de l'envoi de fichiers.
class CPluginBluetoothThreadSendFile : public QThread
{
    Q_OBJECT

public :

       CPluginBluetoothThreadSendFile();

       ~CPluginBluetoothThreadSendFile();

       void setDevice (QString _device);

       void setFile   (QStringList _files);

       void setListDataPlugin (CListDataPlugin *_data_informations);

protected :

        void run();

signals :

        void signalThread();

private :

        QString m_device;

        QStringList m_files;

        CListDataPlugin * m_list_data_plugin;
};


//! \class CPluginBluetooth
//! \brief Classe du plugin bluetooth. Permet de reconnaitre les périphériques bluetooth, et d'envoyer des fichiers sur un périphériques. L'association des appareil n'est pas géré pour l'instant.
class CPluginBluetooth  :   public CPluginAbstractObject , public CPluginAbstract
{
Q_OBJECT
Q_INTERFACES(CPluginAbstract)

public :

    CPluginBluetooth();

    virtual ~CPluginBluetooth();

    virtual QString getNamePlugin();

    virtual QObject *getObject();

    virtual void setDevice (QString _device);

    virtual bool start();

    virtual void stop();

    virtual QWidget *getWidget();

    virtual int getPriority();

    bool isUsed();

    void setUsed  (bool _used);

public slots :

    virtual void slotReceiveData (QString &_data);

    virtual void slotSendData    ();

    virtual void slotDisconnect  ();

    void slotThread();

signals :

    void signalDisconnect   (CPluginAbstract*);

    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    CPluginBluetoothThread  m_thread;

    QTimer   m_timer;
    QRegExp  m_device_type;
    QString  m_data;

    int m_device_id;
    int m_socket_id;

    CPluginBluetoothThreadSendFile m_thread_send_file;
};



#endif
