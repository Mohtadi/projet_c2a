#include "dock_widget_services.h"


CDockWidgetServices::CDockWidgetServices(QList<CPluginAbstract*> *_list_plugins ,   CListDataService   *_list_data_service , QList<CDevice*> *_list_device ,  QWidget *_parent) : QDockWidget (_parent) , m_list_plugins (_list_plugins) , m_list_data_service (_list_data_service) ,  m_list_device (_list_device)
{
    WRITE_ERROR_LOGGER()

    setWindowTitle("Services chargés");

    m_list_services     = new QList<CServiceAbstract*>;
    m_tree_widget_services = new QTreeWidget;
    m_tree_widget_services->setHeaderLabels(QStringList()<<"Services chargés"<<"Type");

    connect (m_tree_widget_services             , SIGNAL(itemClicked(QTreeWidgetItem*,int)) , this , SLOT(slotUpdateTreeWidgetDataInformations              (QTreeWidgetItem*,int)) );
    connect (m_tree_widget_services             , SIGNAL(itemSelectionChanged()) , this , SLOT(slotUpdateTreeWidgetDataInformations              ()) );

    QWidget *widget = new QWidget;

        QGridLayout * grid_layout = new QGridLayout;

            grid_layout->addWidget (m_tree_widget_services , 0 , 0 , 1 , 1);

        widget->setLayout (grid_layout);

    setWidget (widget);

    loadServices();
    initServices ();

    displayServices ();
}

CDockWidgetServices::~CDockWidgetServices()
{
    WRITE_ERROR_LOGGER()
}

QList<CServiceAbstract*> *CDockWidgetServices::getListServices()
{
    WRITE_ERROR_LOGGER()
    return m_list_services;
}

void CDockWidgetServices::save (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    WRITE_ERROR_LOGGER()

    for (int i=0 ; i < m_list_services->count() ; i++)
    {
        (*m_list_services)[i]->save (_dom_document , _dom_element);
    }
}

void CDockWidgetServices::load (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    WRITE_ERROR_LOGGER()

    //Je désactive tout les services
    for (int i=0 ; i < m_tree_widget_services->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item = m_tree_widget_services->topLevelItem(i);

        item->setCheckState(0 , Qt::Unchecked);
        (*m_list_services)[i]->stop();
        (*m_list_services)[i]->getWidget()->setEnabled(true);

        //Je déconnecte les plugins des services désactivés
        disconnect (this , SIGNAL (signalUpdate()) , (*m_list_services)[i]->getObject() , SLOT (slotUpdate()));
    }

    for (int i=0 ; i < m_list_services->count() ; i++)
    {
        (*m_list_services)[i]->load (_dom_document , _dom_element);
    }

    //J'active les services ou start = true
    for (int i=0 ; i < m_tree_widget_services->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item = m_tree_widget_services->topLevelItem(i);
        if ((*m_list_services)[i]->isStart() == true)
        {
            item->setCheckState(0 , Qt::Checked);
            (*m_list_services)[i]->getWidget()->setEnabled(false);
            (*m_list_services)[i]->start();

            //Je connecte les plugins au services activés
            connect (this , SIGNAL (signalUpdate()) ,  (*m_list_services)[i]->getObject() , SLOT (slotUpdate()));
        }
    }
}

void CDockWidgetServices::loadServices()
{
    WRITE_ERROR_LOGGER()
    m_list_services->clear();

    QDir pluginsDir = QDir(qApp->applicationDirPath()+"/../services");
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
             CServiceAbstract *service_abstract = qobject_cast<CServiceAbstract*>(plugin);

             m_list_services->append (service_abstract);
         }
    }
}

void CDockWidgetServices::initServices ()
{
    WRITE_ERROR_LOGGER()

    //J'initialise les services avec la liste de tout les plugins, par référence
    for (int i=0 ; i < m_list_services->count() ; i++)
    {
        (*m_list_services)[i]->init (m_list_data_service);

        //Je connecte les services à this
        connect ((*m_list_services)[i]->getObject() , SIGNAL (signalSendData()) , this , SLOT (slotSendData()));
    }

    for (int i=0 ; i < m_list_plugins->count() ; i++)
    {
        //Et je connecte this aux plugins
        connect (this , SIGNAL (signalSendData()) , (*m_list_plugins)[i]->getObject() , SLOT (slotSendData()));
    }
}

void CDockWidgetServices::displayServices()
{
    WRITE_ERROR_LOGGER()

    m_tree_widget_services->clear();

    for (int i=0 ; i < m_list_services->count() ; i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<(*m_list_services)[i]->getNameService()<<(*m_list_services)[i]->getDescriptionService());
        m_tree_widget_services->addTopLevelItem (item);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState (0 , Qt::Unchecked);
    }

    //Par défaut je séléctionne le premier service de la liste
    if (1 < m_list_services->count())
    {
        m_tree_widget_services->setCurrentItem(m_tree_widget_services->topLevelItem(0));
    }

    m_tree_widget_services->resizeColumnToContents(0) ;
    m_tree_widget_services->resizeColumnToContents(1) ;
    m_tree_widget_services->header()->resizeSections (QHeaderView::ResizeToContents);
}




void CDockWidgetServices::slotUpdateTreeWidgetDataInformations (QTreeWidgetItem * ,int )
{
    WRITE_ERROR_LOGGER()

    //Index de l'item courant du service
    int index = m_tree_widget_services->indexOfTopLevelItem(m_tree_widget_services->currentItem());

    emit signalUpdateStackedWidgetServices (index);

    for (int i=0 ; i < m_tree_widget_services->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item = m_tree_widget_services->topLevelItem(i);
        if (item->checkState(0) == Qt::Checked &&  (*m_list_services)[i]->isStart() == false)
        {
          (*m_list_services)[i]->getWidget()->setEnabled(false);
          (*m_list_services)[i]->start();

          //Je connecte les plugins au services activés
          connect (this , SIGNAL (signalUpdate()) ,  (*m_list_services)[i]->getObject() , SLOT (slotUpdate()));
        }
        else
        {
            if (item->checkState(0) == Qt::Unchecked &&  (*m_list_services)[i]->isStart() == true)
            {
              (*m_list_services)[i]->stop();
              (*m_list_services)[i]->getWidget()->setEnabled(true);

              //Je déconnecte les plugins des services désactivés
              disconnect (this , SIGNAL (signalUpdate()) , (*m_list_services)[i]->getObject() , SLOT (slotUpdate()));
            }
        }
    }
}



void CDockWidgetServices::slotUpdateInformationsData ()
{
    WRITE_ERROR_LOGGER();

    emit signalUpdate();
}

void CDockWidgetServices::slotSendData()
{
    WRITE_ERROR_LOGGER();

    emit signalSendData();

}
