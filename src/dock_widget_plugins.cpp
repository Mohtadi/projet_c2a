#include "dock_widget_plugins.h"

CDockWidgetPlugins::CDockWidgetPlugins(QWidget *_parent ) : QDockWidget (_parent)
{
    WRITE_ERROR_LOGGER()

    setWindowTitle("Plugins chargés");

    m_list_data_service = NULL;

    m_list_plugins      = new QList<CPluginAbstract*>;


    m_tree_widget_plugin = new QTreeWidget;
    m_tree_widget_plugin->setHeaderLabels(QStringList()<<"Plugins chargés");

    QWidget *widget = new QWidget;

        QGridLayout *grid_layout = new QGridLayout;

            grid_layout->addWidget (m_tree_widget_plugin  , 0 , 0 , 1 , 1);

            widget->setLayout (grid_layout);

    setWidget (widget);

    loadPlugins();

    displayPlugins ();
}

CDockWidgetPlugins::~CDockWidgetPlugins()
{
    WRITE_ERROR_LOGGER()
}

void CDockWidgetPlugins::loadPlugins ()
{
    WRITE_ERROR_LOGGER()

    m_list_plugins->clear();

    QDir pluginsDir = QDir(qApp->applicationDirPath()+"/../plugins");
    foreach (QString fileName , pluginsDir.entryList(QDir::Files))
    {
         QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

         QObject *plugin = loader.instance();

         if (pluginsDir.exists() == false)
         {
             qDebug("Chemin de plugin introuvable");
         }

         if (plugin)
         {
             CPluginAbstract *plugin_abstract = qobject_cast<CPluginAbstract*>(plugin);

             m_list_plugins->append (plugin_abstract);
         }
    }

    //Je conbstruit la liste de toute les listes d'informations de chaques plugins
    m_list_data_service = new CListDataService;
    for (int i=0 ;  i < m_list_plugins->count() ; i++)
    {
        m_list_data_service->append(&((*m_list_plugins)[i]->getListDataPlugin()));

        //Sert juste à afficher chaque fenetre de cutecom
        //if ((*m_list_plugins)[i]->getWidget() != NULL)
        {
          //  (*m_list_plugins)[i]->getWidget()->show();
        }
    }
}


void CDockWidgetPlugins::displayPlugins ()
{
    WRITE_ERROR_LOGGER()

    m_tree_widget_plugin->clear();

    for (int i=0 ; i < m_list_plugins->count() ; i++)
    {
        new QTreeWidgetItem(m_tree_widget_plugin , QStringList()<<(*m_list_plugins)[i]->getNamePlugin());
    }
    m_tree_widget_plugin->resizeColumnToContents(0) ;
    m_tree_widget_plugin->resizeColumnToContents(1) ;
}

QList<CPluginAbstract*> * CDockWidgetPlugins::getListPlugins ()
{
    WRITE_ERROR_LOGGER()
    return m_list_plugins;
}

CListDataService   *CDockWidgetPlugins::getListDataService()
{
    return m_list_data_service;
}

