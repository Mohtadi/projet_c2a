//! \file    dock_widget_services_stacked_widget.h
//! \brief   Ce widget contient tout les widgets de paramétrage de chaques services.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __DOCK_WIDGET_SERVICES_STACKED_WIDGET_H__
#define __DOCK_WIDGET_SERVICES_STACKED_WIDGET_H__

#include "define.h"


//! \class CDockWidgetServicesStackedWidget
//! \brief DockWidget qui contient les widgets de tout les services.
class CDockWidgetServicesStackedWidget : public QDockWidget
{
Q_OBJECT

public :

   //! \fn   CDockWidgetServicesStackedWidget (QList<CServiceAbstract*> *_list_services , QWidget *_parent = 0)
   //! \brief Constructeur.
   CDockWidgetServicesStackedWidget (QList<CServiceAbstract*> *_list_services , QWidget *_parent = 0);

    //! \fn   ~CDockWidgetServicesStackedWidget()
    //! \brief Destructeur.
   ~CDockWidgetServicesStackedWidget();

public slots :

    //! \fn   void slotUpdateStackedWidgetServices (int _index)
    //! \brief Slot de mise à jour du widget courant.
    void slotUpdateStackedWidgetServices (int _index);

private :

    //! \fn   void createStackedWidgetServices ()
    //! \brief Initialisation du stacked widget et ajout des widgets.
    void createStackedWidgetServices ();

    QStackedWidget              *m_stacked_widget_services;

    QList<CServiceAbstract*>    *m_list_services;
};

#endif
