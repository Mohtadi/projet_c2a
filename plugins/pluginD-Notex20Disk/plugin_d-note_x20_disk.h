//! \file    plugin_d-note_x20_disk.h
//! \brief   Plugin de périphériques de la tablette tactile plugin_d-note
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_DNOTE_X20_DISK_H__
#define __PLUGIN_DNOTE_X20_DISK_H__

#include<QtGui>


#include "../../interface/pluginAbstract.h"
#include "../../interface/pluginAbstractObject.h"

//! \class CPluginDNoteX20Disk
//! \brief Cette classe est similaire au plugin corsaire. Il faudrait faire un plugin plus générique avec libusb.
class CPluginDNoteX20Disk :  public CPluginAbstractObject , public CPluginAbstract
{

    Q_OBJECT
    Q_INTERFACES(CPluginAbstract)

public :

    CPluginDNoteX20Disk();

    ~CPluginDNoteX20Disk();

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
