//! \file    main_window.h
//! \brief   Fenêtre principale de l'application.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__

#include "define.h"

#include "dock_widget_device_monitor.h"
#include "dock_widget_list_data_service.h"
#include "dock_widget_plugins.h"
#include "dock_widget_services.h"
#include "dock_widget_services_stacked_widget.h"
#include "central_widget.h"


//! \class CMainWindow
//! \brief Widget principale de l'application qui contient les autres widgets.
class CMainWindow :public QMainWindow
{
Q_OBJECT
public :

    //! \fn  CMainWindow(QWidget *_parent = NULL)
    //! \brief Constructeur.
    CMainWindow( int _argc, char ** _argv , QWidget *_parent = NULL);

    //! \fn  ~CMainWindow()
    //! \brief Destructeur.
    ~CMainWindow();

    //! \fn  void createWorkingDirectory ()
    //! \brief Crée et initialise le répertoire de travail de l'application. Efface tout les fichiers au lancement du programme, et crée le répertoire si il est inexistant.
    void createWorkingDirectory ();

    //! \fn  void createActions ()
    //! \brief Création des actions.
    void createActions ();

    //! \fn  void createToolBar ()
    //! \brief Création et initialisation de la tool bar.
    void createToolBar ();

    //! \fn   void connectAll()
    //! \brief Initialisation des différentes connections entre widgets.
    void connectAll();

private slots :

    //! \fn   void slotOpen()
    //! \brief Slot pour ouvrir un fichier projet.
    void slotOpen(QString _file_name = "");

    //! \fn   void slotSave()
    //! \brief Slot pour enregistrer un fichier projet.
    void slotSave();

private:

    CDockWidgetDeviceMonitor   *m_dock_widget_device_monitor;

    CDockWidgetListDataService *m_dock_widget_list_data_service;

    CDockWidgetPlugins         *m_dock_widget_plugins;

    CDockWidgetServices        *m_dock_widget_services;

    CDockWidgetServicesStackedWidget *m_dock_widget_services_stacked_widget;

    CCentralWidget             *m_central_widget;

    QAction *m_action_open;

    QAction *m_action_save;
};
#endif
