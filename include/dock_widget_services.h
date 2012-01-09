//! \file    dock_widget_services.h
//! \brief   Ce widget contient et initialise les services.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __DOCK_WIDGET_SERVICES_H__
#define __DOCK_WIDGET_SERVICES_H__

#include "define.h"
#include "device.h"


//! \class CDockWidgetServices
//! \brief Dockwidget qui contient la liste des services, initialise la liste des services, lance les services et gère les connections entre services et plugins.
class CDockWidgetServices : public QDockWidget
{
Q_OBJECT

public :

    //! \fn  CDockWidgetServices(QList<CPluginAbstract*>     *_list_plugins , CListDataService   *_list_data_service , QList<CDevice*> *_list_device , QWidget *_parent = 0)
    //! \brief Constructeur
    CDockWidgetServices(QList<CPluginAbstract*>     *_list_plugins , CListDataService   *_list_data_service , QList<CDevice*> *_list_device , QWidget *_parent = 0);

    //! \fn  ~CDockWidgetServices()
    //! \brief Destructeur.
    ~CDockWidgetServices();

    //! \fn  QList<CServiceAbstract*>    *getListServices()
    //! \brief Renvoi la liste des services chargés.
    QList<CServiceAbstract*>    *getListServices();

    //! \fn   void save (QDomDocument &_dom_document , QDomElement &_dom_element)
    //! \brief Lance la sauvegarde de projet, cette fonction apelle la fonction de sauvegarde de chaque services chargés.
    void save (QDomDocument &_dom_document , QDomElement &_dom_element);

    //! \fn   void load (QDomDocument &_dom_document , QDomElement &_dom_element)
    //! \brief Lance le chargement de projet, cette fonction apelle la fonction de chargement de chaque services chargés.
    void load (QDomDocument &_dom_document , QDomElement &_dom_element);

public slots :

    //! \fn   void slotUpdateTreeWidgetDataInformations (QTreeWidgetItem *_item = NULL ,int _i = 0)
    //! \brief Lance ou stop un service quand l'utilisateur coche le service. Gère l'interface pour actualiser le widget en fonction du service séléctionné.
    void slotUpdateTreeWidgetDataInformations (QTreeWidgetItem *_item = NULL ,int _i = 0);

    //! \fn   void slotUpdateInformationsData ()
    //! \brief Permet d'envoyer un signal pour actualiser les services. (Peut être à revoir et à mettre au clair).
    void slotUpdateInformationsData ();


    //! \fn   void slotSendData()
    //! \brief Permet aux services de renvoyer des informations aux plugins. (Peut être à revoir et à mettre au clair).
    void slotSendData();

signals :

   void signalUpdate();

   void signalSendData();

   void signalUpdateStackedWidgetServices (int);

private :

    //! \fn   void loadServices()
    //! \brief Chargement des services.
    void loadServices();

    //! \fn   void initServices ()
    //! \brief Initialisation des services.
    void initServices ();

    //! \fn   void displayServices()
    //! \brief Affichage des services dans l'interface.
    void displayServices();

private :

    QTreeWidget                 *m_tree_widget_services;

    QList<CServiceAbstract*>    *m_list_services;

    QList<CPluginAbstract*>     *m_list_plugins;

    CListDataService            *m_list_data_service;

    QList<CDevice*>             *m_list_device;
};

#endif
