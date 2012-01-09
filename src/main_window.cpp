#include "main_window.h"


CMainWindow::CMainWindow ( int _argc , char ** _argv , QWidget *_parent) : QMainWindow(_parent)
{
    WRITE_ERROR_LOGGER()

    createActions ();

    createToolBar();

    createWorkingDirectory();

    m_dock_widget_plugins           = new CDockWidgetPlugins;

    m_dock_widget_device_monitor    = new CDockWidgetDeviceMonitor  (m_dock_widget_plugins->getListPlugins() );

    m_dock_widget_list_data_service = new CDockWidgetListDataService(m_dock_widget_plugins->getListDataService());

    m_dock_widget_services          = new CDockWidgetServices       (m_dock_widget_plugins->getListPlugins() , m_dock_widget_plugins->getListDataService() , m_dock_widget_device_monitor->getListDevice());

    m_dock_widget_services_stacked_widget = new CDockWidgetServicesStackedWidget (m_dock_widget_services->getListServices());

    addDockWidget(Qt::RightDockWidgetArea    , m_dock_widget_plugins);

    addDockWidget(Qt::RightDockWidgetArea    , m_dock_widget_device_monitor);

    addDockWidget(Qt::RightDockWidgetArea    , m_dock_widget_list_data_service);

    addDockWidget(Qt::LeftDockWidgetArea , m_dock_widget_services);

    addDockWidget(Qt::LeftDockWidgetArea , m_dock_widget_services_stacked_widget);

    tabifyDockWidget (m_dock_widget_plugins         , m_dock_widget_device_monitor);
    tabifyDockWidget (m_dock_widget_device_monitor  , m_dock_widget_list_data_service);

    setWindowState (Qt::WindowMaximized);

    connectAll();

    //Affiche les interfaces de cutecom, utilisé pour déboguer mais prend beaucoup de temps
    /*m_central_widget = new CCentralWidget (m_dock_widget_device_monitor->getListDevice());
    connect (m_dock_widget_device_monitor , SIGNAL (signalUpdateInformationsData()) , m_central_widget , SLOT (slotUpdateTabWidget()));
    setCentralWidget (m_central_widget);*/

    //Chargement d'un projet depuis la ligne de commande
    if (_argc > 1)
    {
        slotOpen (_argv[1]);
    }
}

void CMainWindow::createWorkingDirectory ()
{
    WRITE_ERROR_LOGGER()
    //Création du répertoire de données
    QDir dir (WORKING_DIRECTORY);
    if (dir.exists() == true)
    {
        //Suppression de tout les fichiers dans le répertoire
        QDir dir = QDir(WORKING_DIRECTORY);
        foreach (QString fileName , dir.entryList(QDir::Files))
        {
            QFile file(dir.absolutePath() + "/" + fileName);
            if (file.remove() == false)
            {
                qDebug() <<"Fichier "+fileName + " " + "non supprimé";
            }
        }
    }
    else
    {
        if (dir.mkdir (WORKING_DIRECTORY) == false)
        {
            qDebug() <<"Répertoire data non crée";
        }
    }
}


void CMainWindow::createActions ()
{
    WRITE_ERROR_LOGGER()

    m_action_open  = new QAction (QIcon(":open.png") , "Ouvrir"        , this);

    m_action_save  = new QAction (QIcon(":save.png") , "Enregistrer"   , this);
}

void CMainWindow::createToolBar ()
{
    WRITE_ERROR_LOGGER()

    QToolBar *tool_bar = new QToolBar ("Barre d'outils");

        tool_bar->addAction (m_action_open);

        tool_bar->addAction (m_action_save);

   addToolBar (tool_bar);

}

void CMainWindow::connectAll()
{
    WRITE_ERROR_LOGGER()

    connect (m_dock_widget_device_monitor , SIGNAL (signalUpdateInformationsData()) , m_dock_widget_list_data_service , SLOT (slotUpdateTreeWidgetListDataService()));

    connect (m_dock_widget_device_monitor , SIGNAL (signalUpdateInformationsData()) , m_dock_widget_services , SLOT (slotUpdateInformationsData()));

    connect (m_dock_widget_services , SIGNAL (signalUpdateStackedWidgetServices(int)) , m_dock_widget_services_stacked_widget , SLOT (slotUpdateStackedWidgetServices(int)));

    connect (m_action_open , SIGNAL (triggered ()) , this , SLOT (slotOpen()));

    connect (m_action_save , SIGNAL (triggered ()) , this , SLOT (slotSave()));
}

void CMainWindow::slotOpen(QString _file_name)
{
    WRITE_ERROR_LOGGER()

    QString file_name = "";
    if (_file_name == "")
    {
        file_name = QFileDialog::getOpenFileName (this , "Ouvrir" , "/home" , "*.c2a");
    }
    else
    {
        file_name = _file_name;
    }

    if (file_name != "")
    {
        QFile file (file_name);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QDomDocument dom_document;

           if(dom_document.setContent(&file))
           {
                QDomElement dom_element = dom_document.documentElement();

                if (dom_element.tagName() == "Project")
                {
                    m_dock_widget_services->load (dom_document ,dom_element);
                }
           }
        }
    }
}

void CMainWindow::slotSave()
{
    WRITE_ERROR_LOGGER()

    QString file_name = QFileDialog::getSaveFileName (this , "Enregistrer" , "/home" , "*.c2a");

    QFileInfo file_info (file_name);
    if (file_info.completeSuffix() == "")
    {
        file_name += ".c2a";
    }

    if (file_name != "")
    {
        //Construction du fichier xml
        QDomDocument dom_document ("c2a");

        QDomElement  dom_element = dom_document.createElement ("Project");

        dom_document.appendChild (dom_element);

        //Appelle des méthodes de sauvegarde des différents widget
        m_dock_widget_services->save (dom_document ,dom_element);


        //Ecriture du fichier XML
        QFile file (file_name);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream text_stream(&file);

            //Je dois géré les accents dans mon fichier xml, je suis obligé de mettre iso-8856-1 sinon par défaut je suis en US-Ascii et j'ai pas d'accents.
            text_stream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"<<dom_document.toString();

            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Enregistrement" , "Impossible d'enregistrer.");
        }
    }
}

CMainWindow::~CMainWindow()
{
    WRITE_ERROR_LOGGER()
}

