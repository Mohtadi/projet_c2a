#include "dock_widget_list_data_service.h"

CDockWidgetListDataService::CDockWidgetListDataService(CListDataService  *_list_data_service , QWidget *_parent) : QDockWidget(_parent) , m_list_data_service (_list_data_service)
{
    setWindowTitle("Tunnel c2a");

    m_tree_widget_data_service = new QTreeWidget;

    QWidget *widget = new QWidget;

        QGridLayout *grid_layout = new QGridLayout;

            grid_layout->addWidget(m_tree_widget_data_service , 0 , 0 , 1 , 1 );

        widget->setLayout(grid_layout);

    setWidget(widget);

    createTreeWidgetListDataService ();
}

void CDockWidgetListDataService::createTreeWidgetListDataService ()
{
    WRITE_ERROR_LOGGER()

    m_tree_widget_data_service->setHeaderLabels(CData::getStringListTitle());

    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = new QTreeWidgetItem(QStringList()<<m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("NAME_PLUGIN").toString());
        item_parent->setFont (0, QFont("", 10, QFont::Bold) );

        m_tree_widget_data_service->addTopLevelItem(item_parent);

        for (int j=0 ;  j < m_list_data_service->index(i)->count() ; j++)
        {
            //Je parcourt les informations de connections
            QTreeWidgetItem *item_informations = new QTreeWidgetItem(QStringList());
            item_parent->addChild (item_informations);

            item_informations->setText (0 ,  m_list_data_service->index(i)->getTitle(j));
            item_informations->setFont (0, QFont("", 10 , QFont::Normal) );

            for (int k = 0 ; k < m_list_data_service->index(i,j).count() ;k++)
            {
                CData data = m_list_data_service->index(i,j,k);

                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<data.getTypeData()<<data.getValueData().toString()<<data.getUnitData()<<data.getDescription());
                item->setFont (0, QFont("", 8 , QFont::Normal) );
                item->setFont (1, QFont("", 8 , QFont::Normal) );
                item->setFont (2, QFont("", 8 , QFont::Normal) );
                item->setFont (3, QFont("", 8 , QFont::Normal) );
                item_informations->addChild(item);
            }
        }
    }

    m_tree_widget_data_service->expandAll ();
    for (int i=0 ; i < m_tree_widget_data_service->columnCount() ; i++)
    {
        m_tree_widget_data_service->resizeColumnToContents(i) ;
    }

    m_tree_widget_data_service->header()->resizeSections (QHeaderView::ResizeToContents);
}

void CDockWidgetListDataService::slotUpdateTreeWidgetListDataService()
{
    WRITE_ERROR_LOGGER()

    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = m_tree_widget_data_service->topLevelItem(i);

        for (int j=0 ;  j < m_list_data_service->index(i)->count() ; j++)
        {
            //Je parcourt les informations
            QTreeWidgetItem *item_informations = item_parent->child(j);

            for (int k = 0 ; k < m_list_data_service->index(i,j).count() ; k++)
            {
                CData data = m_list_data_service->index(i,j,k);

                QTreeWidgetItem *item = item_informations->child(k);

                item->setText (0 , data.getTypeData());
                item->setText (1 , data.getValueData().toString());
                item->setText (2 , data.getUnitData());
                item->setText (3 , data.getDescription());
            }
        }
    }
}
