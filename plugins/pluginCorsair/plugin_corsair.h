//! \file    plugin_corsaire.h
//! \brief   Plugin de périphériques corsaire. Reconnait une clé usb portant le nom de volume CORSAIRE.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_CORSAIR_H__
#define __PLUGIN_CORSAIR_H__
#include<QtGui>


#include "../../interface/pluginAbstract.h"
#include "../../interface/pluginAbstractObject.h"


//! \class CPluginCorsair
//! \brief Cette classe est similaire au plugin d-note de la tablette tactile. Il faudrait faire un plugin plus générique avec libusb.
class CPluginCorsair :  public CPluginAbstractObject , public CPluginAbstract
{
Q_OBJECT
Q_INTERFACES(CPluginAbstract)

public :

    CPluginCorsair();

    ~CPluginCorsair();

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

    void parseDirectory();

signals :

    void signalDisconnect   (CPluginAbstract*);

    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    QString        m_device_type;
    QTimer         m_timer;
};



#endif
