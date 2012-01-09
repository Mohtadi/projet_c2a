#include "dock_widget_device_monitor.h"

CDockWidgetDeviceMonitor::CDockWidgetDeviceMonitor(QList<CPluginAbstract*> *_list_plugins , QWidget *_parent) : QDockWidget (_parent) ,  m_list_plugins (_list_plugins)
{
    WRITE_ERROR_LOGGER()

    setWindowTitle("Détection des périphériques");

    m_list_device = new QList<CDevice*>;
    m_thread_device_monitor = new CThreadDeviceMonitor;

    m_tree_widget_device_monitor = new QTreeWidget;
    m_tree_widget_device_monitor->setHeaderLabels(QStringList()<<"Péripherique"<<"Plugin de connection");

    QWidget *widget = new QWidget;

        QGridLayout *grid_layout = new QGridLayout;

            grid_layout->addWidget(m_tree_widget_device_monitor , 0 , 0 , 1 , 1 );

        widget->setLayout(grid_layout);

    setWidget(widget);

    initListDeviceMonitor();

    connect (m_thread_device_monitor , SIGNAL(signalDisplaySearchPlugin(CDevice *)) , this , SLOT (slotDisplaySearchPlugin(CDevice *)));
    m_thread_device_monitor->setListDeviceMonitor  (m_list_device);

    m_thread_device_monitor->start();
}

CDockWidgetDeviceMonitor::~CDockWidgetDeviceMonitor()
{
    WRITE_ERROR_LOGGER()
}

QList<CDevice*> *CDockWidgetDeviceMonitor::getListDevice()
{
    return m_list_device;
}

void CDockWidgetDeviceMonitor::slotUpdateTreeWidgetDeviceMonitor(CDevice *)
{
    WRITE_ERROR_LOGGER()

    for (int i=0 ; i < m_list_device->count() ; i++)
    {
        if ((*m_list_device)[i]->getPlugin() != NULL)
        {
            m_tree_widget_device_monitor->topLevelItem(i)->setText(1,(*m_list_device)[i]->getPlugin()->getNamePlugin());
        }
        else
        {
            m_tree_widget_device_monitor->topLevelItem(i)->setText(1,"Non connecte");
        }
    }

    emit signalUpdateInformationsData ();
}

void CDockWidgetDeviceMonitor::slotDisplaySearchPlugin(CDevice *_device)
{
    WRITE_ERROR_LOGGER()

    for (int i=0 ; i < m_list_device->count() ; i++)
    {
        if ((*m_list_device)[i] == _device)
        {
            m_tree_widget_device_monitor->topLevelItem(i)->setSelected(true);
        }
        else
        {
            m_tree_widget_device_monitor->topLevelItem(i)->setSelected(false);
        }
    }
}



void CDockWidgetDeviceMonitor::initListDeviceMonitor()
{
    WRITE_ERROR_LOGGER()
   //Liste des périphérique à surveiller

    m_list_device->append(new CDevice("bluetooth" , m_list_plugins));
    m_list_device->append(new CDevice("network"   , m_list_plugins));

   /* m_list_device->append(new CDevice("/dev/ttyS0"        , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyS1"        , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon0"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon1"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon2"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon3"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon4"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon5"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon6"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/usbmon7"      , m_list_plugins));*/
    m_list_device->append(new CDevice("/dev/ttyUSB0"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB1"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB2"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB3"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB4"      , m_list_plugins));

   /* m_list_device->append(new CDevice("/dev/ttyUSB5"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB6"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/ttyUSB7"      , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event0" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event1" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event2" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event3" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event4" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event5" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event6" , m_list_plugins));
    m_list_device->append(new CDevice("/dev/input/event7" , m_list_plugins));*/

    m_list_device->append(new CDevice("/media/D-NOTE DISK/" , m_list_plugins));
    m_list_device->append(new CDevice("/media/CORSAIR/"     , m_list_plugins));

    //Detecte les disk branché mais il faut connaitre le nom du disque, ou bien brancher le disk avant de lancer le programme
    //Sinon faire un thread en arriere plan  ...
    /*QDir dir = QDir("/dev/disk/by-label/");
    foreach (QString fileName , dir.entryList(QDir::Files))
    {
        m_list_device->append(CDevice(dir.absoluteFilePath(fileName)));
    }*/

    m_tree_widget_device_monitor->clear();

    for (int i=0 ; i < m_list_device->count() ; i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<(*m_list_device)[i]->getDevice()<<"Non connecte");
        m_tree_widget_device_monitor->addTopLevelItem(item);
    }
    m_tree_widget_device_monitor->header()->resizeSections (QHeaderView::ResizeToContents);
    for (int i=0 ; i<m_list_device->count() ; i++)
    {
        connect ((*m_list_device)[i] , SIGNAL (signalUpdateTreeWidgetDeviceMonitor(CDevice *)) , this , SLOT (slotUpdateTreeWidgetDeviceMonitor(CDevice *)) , Qt::DirectConnection );
    }
    m_tree_widget_device_monitor->resizeColumnToContents(0) ;
    m_tree_widget_device_monitor->resizeColumnToContents(1) ;
}
