#ifndef __DOCK_WIDGET_PLUGINS_H__
#define __DOCK_WIDGET_PLUGINS_H__

#include "define.h"
class CDockWidgetPlugins : public QDockWidget
{
public :
    CDockWidgetPlugins(QWidget *_parent = 0);

    void loadPlugins ();

    void displayPlugins();

    QList<CPluginAbstract*>     *getListPlugins ();

    CListDataService            *getListDataService();

    ~CDockWidgetPlugins();

protected:
private:

    QTreeWidget *m_tree_widget_plugin;


    QList<CPluginAbstract*>     *m_list_plugins;

    CListDataService            *m_list_data_service;

};

#endif
