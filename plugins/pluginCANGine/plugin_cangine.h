//! \file    plugin_cangine.h
//! \brief   Plugin de périphériques cangine.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_CANGINE_H__
#define __PLUGIN_CANGINE_H__

#include<QtGui>

#include "plugin_abstract_serial_port.h"

//! \class CPluginCANGine
//! \brief Classe pour gérer le cangine. Pour détecter la déconnection du périphérique il faut surveiller avec un timer. Le parsage du message est assez lourd, peut être faudrait t'il améliorer.
class CPluginCANGine:  public CPluginAbstractSerialPort
{
    Q_OBJECT
    Q_INTERFACES(CPluginAbstract)

public :

    CPluginCANGine();

    ~CPluginCANGine();

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

    virtual void slotSendData    () {}

    virtual void slotDisconnect  ();

signals :

    void signalDisconnect   (CPluginAbstract*);

    void signalUpdateServices ();

protected :

    virtual void setDataConnectionSettings ();

    virtual void setDefaultData();

private :

    void parseToMessage ();

    QRegExp m_device_type;

    QString m_data;

    QList<QString> m_list_string_validation;

    QString m_message;

    QTimer m_time_disconnect;

    int    m_cpt_iteration_data;
};



#endif
