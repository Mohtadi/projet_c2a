#include "thread_device_monitor.h"

CThreadDeviceMonitor::CThreadDeviceMonitor (QObject *_parent) : QThread(_parent)
{
    WRITE_ERROR_LOGGER()
}


CThreadDeviceMonitor::~CThreadDeviceMonitor()
{
    WRITE_ERROR_LOGGER()
}

void CThreadDeviceMonitor::setListDeviceMonitor (QList<CDevice*> *_list_device_monitor)
{
    WRITE_ERROR_LOGGER()

    m_list_device_monitor = _list_device_monitor;
}

void CThreadDeviceMonitor::run()
{
    WRITE_ERROR_LOGGER()
    while (true)
    {
        for (int i=0 ; i < m_list_device_monitor->count() ; i++)
        {
            if ((*m_list_device_monitor)[i]->getPlugin() == NULL)
            {
                //Si je connecte tout le monde à l'initialisation, le signal sera envoyé à tout les device et ca sert à rien
                connect ( this , SIGNAL (signalSearchPlugin ()) ,  (*m_list_device_monitor)[i] ,SLOT (slotSearchPlugin()) , Qt::BlockingQueuedConnection);

                emit signalDisplaySearchPlugin   ((*m_list_device_monitor)[i]);

                msleep(100);

                //J'envoi un signal car les plugins utilisent des thread, avec une méthode les thread ne peuvent pas être crées
                emit signalSearchPlugin ();

                disconnect ( this , SIGNAL (signalSearchPlugin ()) ,  (*m_list_device_monitor)[i] ,SLOT (slotSearchPlugin()) );
             }
        }
        //Permet de ne pas forcer sur le thread et de le mettre à 100% si il y a qu'un élément
        msleep(100);
    }
}
