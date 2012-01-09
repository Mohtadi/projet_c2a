#ifndef __DOCK_WIDGET_LIST_DATA_SERVICE_H__
#define __DOCK_WIDGET_LIST_DATA_SERVICE_H__

#include "define.h"

class CDockWidgetListDataService : public QDockWidget
{
Q_OBJECT
public :

        CDockWidgetListDataService ( CListDataService  *_list_data_service  , QWidget *_parent = 0);

        void createTreeWidgetListDataService ();

public slots :

        void slotUpdateTreeWidgetListDataService ();

protected :

private :

    QTreeWidget         *m_tree_widget_data_service;
    CListDataService    *m_list_data_service;
};

#endif
