//! \file    service_flite.h
//! \brief   Service de voix synthétique. Utilise la librairie flite.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __SERVICE_FLITE_H__
#define __SERVICE_FLITE_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"

#include "flite/flite.h"

extern "C"
{
        cst_voice* register_cmu_us_kal();
}

//! \class CServiceFliteThread
//! \brief Thread qui lit les informations à lire à la suite.
class CServiceFliteThread : public QThread
{
   public :
    CServiceFliteThread();

    void setListDataService        (CListDataService *_list_data_service);
    void setTreeWidget                  (QTreeWidget *_tree_widget);
    void setStop (bool _stop);

   protected:

       void run();

   private :
    cst_voice *m_voice;
    CListDataService *m_list_data_service;
    QTreeWidget *m_tree_widget;
    bool      m_stop;
};

//! \class CServiceFlite
//! \brief Service de voix synthétique. La librairie utilisé est flite-1.4-release, les versions antérieur ne marche pas.
class CServiceFlite : public CServiceAbstractObject , public CServiceAbstract
{

    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceFlite();
    ~CServiceFlite();

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

signals :
    void signalSendData();

private :

    CServiceFliteThread     *m_thread;

    QWidget     *m_widget;

    QTreeWidget *m_tree_widget;
};



#endif
