//! \file    plugin_serial_port.h
//! \brief   Plugin de périphériques par défaut. Si je detecte un périphérique et que je ne sais pas ce que c'est, c'est un plugin par défaut pour les connections séries.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_SERIAL_PORT_H__
#define __PLUGIN_SERIAL_PORT_H__

#include<QtGui>

#include "plugin_abstract_serial_port.h"


//! \class CPluginSerialPort
//! \brief Cette classe se connecte en serial port si les périphériques connues ne sont pas détectés. En faite elle n'est pas très utile, sauf pour le programmeur. Attention, une seul instance de chaque plugin est utilisable, donc si deux périphérique sont reconnu, un seul s'associera avec le plugin.
class CPluginSerialPort  :  public CPluginAbstractSerialPort
{
    Q_OBJECT
    Q_INTERFACES(CPluginAbstract)

public :
    CPluginSerialPort();
    virtual ~CPluginSerialPort();

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


    virtual void    slotSendData    () {}
    virtual void slotDisconnect  ();

signals :


    void signalDisconnect   (CPluginAbstract*);
    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    QString m_data;

};



#endif
