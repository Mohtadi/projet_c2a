//! \file    plugin_gps.h
//! \brief   Plugin de périphériques du gps
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_GPS_H__
#define __PLUGIN_GPS_H__

#include<QtGui>

#include "plugin_abstract_serial_port.h"
#include "../../interface/pluginAbstract.h"


//! \class CPluginGPS
//! \brief Cette classe gère le gps.
class CPluginGPS :  public CPluginAbstractSerialPort
{

    Q_OBJECT
    Q_INTERFACES(CPluginAbstract)

public :

    CPluginGPS();
    ~CPluginGPS();

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

    virtual void slotDisconnect ();

signals :

    void signalDisconnect   (CPluginAbstract*);
    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    void parseToMessage ();

    QRegExp        m_device_type;
    QString        m_data;
    QString        m_message;
    QList<QString> m_list_string_validation;

};



#endif
