#ifndef __DOCK_WIDGET_DEVICE_MONITOR_H__
#define __DOCK_WIDGET_DEVICE_MONITOR_H__

#include "define.h"
#include "thread_device_monitor.h"
#include "device.h"

class CDockWidgetDeviceMonitor : public QDockWidget
{
    Q_OBJECT

public :

    CDockWidgetDeviceMonitor( QList<CPluginAbstract*> *_list_plugins , QWidget *_parent = 0 );

    void initListDeviceMonitor();

    ~CDockWidgetDeviceMonitor();

    QList<CDevice*> *getListDevice();


public slots :

    void slotUpdateTreeWidgetDeviceMonitor(CDevice *_device);

    void slotDisplaySearchPlugin          (CDevice *_device);



signals :

    void signalUpdateInformationsData ();

protected :

private :

    QTreeWidget          *m_tree_widget_device_monitor;

    QList<CDevice*>       *m_list_device;

    CThreadDeviceMonitor *m_thread_device_monitor;

    QList<CPluginAbstract*>    *m_list_plugins;
};

#endif // DOCK_WIDGET_DEVICE_MONITOR_H
