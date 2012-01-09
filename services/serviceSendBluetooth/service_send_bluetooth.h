//! \file    service_send_bluetooth.h
//! \brief   Service d'envoi de fichiers par bluetooth.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __SERVICE_SEND_BLUETOOTH_H__
#define __SERVICE_SEND_BLUETOOTH_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"


//! \class CServiceSendBluetooth
//! \brief Les informations sont transmis au plugin bluetooth par l'intermediaire de la liste de donnée, c'est lui qui envoi les fichiers. On aurait pu le faire dans le service, mais si un autre service à besoin de cette fonctionnalité il faut la réécrire.
class CServiceSendBluetooth : public CServiceAbstractObject , public CServiceAbstract
{

    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSendBluetooth();

    ~CServiceSendBluetooth();

    virtual void init (CListDataService *_list_data_informations);

    virtual QObject *getObject();

    virtual QString getNameService();

    virtual QString getDescriptionService();

    virtual void createWidget();

    virtual void initWidget();

    void updateWidget();

    virtual QWidget * getWidget();

    void start ();

    void stop();

    void save (QDomDocument &_dom_document , QDomElement &_dom_element);

    void load (QDomDocument &_dom_document , QDomElement &_dom_element);

public slots :

    virtual void slotUpdate();

    void slotSendFile ();

signals :

    void signalSendData();

private :

    QWidget     *m_widget;

    QLineEdit   *m_line_edit_addresse_mac;
    QLineEdit   *m_line_edit_dir;


    QLabel      *m_label_error;

    QSpinBox    *m_spin_box_interval;
    QFile m_file;

    QTimer m_timer;


};



#endif
