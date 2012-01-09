//! \file    plugin_network.h
//! \brief   Plugin de périphériques pour détecter les cartes réseaux et les connections internet.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_NETWORK_H__
#define __PLUGIN_NETWORK_H__

#include<QtGui>

#include "../../interface/pluginAbstract.h"
#include "../../interface/pluginAbstractObject.h"

#include <QNetworkInterface>


//! \class CPluginNetwork
//! \brief Cette classe permet de récupérer les adresses réseaux.
class CPluginNetwork  :   public CPluginAbstractObject , public CPluginAbstract
{
    Q_OBJECT
    Q_INTERFACES(CPluginAbstract)

public :

    CPluginNetwork();

    virtual ~CPluginNetwork();

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

    void slotUpdate();

signals :


    void signalDisconnect   (CPluginAbstract*);
    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    QTimer   m_timer;
    QRegExp  m_device_type;
    QList<QNetworkInterface> m_list_network_interface;
};



#endif
