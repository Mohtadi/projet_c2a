#include "device.h"

CDevice::CDevice (QString _device , QList<CPluginAbstract*> * _list_plugins , QObject *_parent) : QObject(_parent),
        m_device(_device),
        m_plugin(NULL),
        m_list_plugins(_list_plugins)
{
    WRITE_ERROR_LOGGER()
}

CDevice::CDevice (const CDevice &_device , QObject *_parent) : QObject(_parent)
{
    m_device                     = _device.m_device;
    m_plugin                     = _device.m_plugin;
    m_list_plugins               = _device.m_list_plugins;
    m_list_plugins_valid         = _device.m_list_plugins_valid;
}

CDevice::~CDevice ()
{
    WRITE_ERROR_LOGGER()
}

QString CDevice::getDevice()
{
    return m_device;
}


CPluginAbstract *CDevice::getPlugin()
{
    return m_plugin;
}

void CDevice::slotSearchPlugin()
{
    WRITE_ERROR_LOGGER()

    m_list_plugins_valid.clear();

    //Je test tout les plugins l'un après l'autre
    for (int i=0 ; i < m_list_plugins->count() ; i++)
    {
        //Si le plugin n'est pas utilisé par un périphérique
        if ((*m_list_plugins)[i]->isUsed() == false)
        {
            connect ((*m_list_plugins)[i]->getObject() , SIGNAL(signalDisconnect(CPluginAbstract*)) , this , SLOT(slotDisconnect   (CPluginAbstract*)) , Qt::DirectConnection);

            (*m_list_plugins)[i]->setDevice(m_device);

            //Si le plugin est valide je le met dans une liste
            if ((*m_list_plugins)[i]->start() == true)
            {
                m_list_plugins_valid.append((*m_list_plugins)[i]);
            }

            disconnect ((*m_list_plugins)[i]->getObject() , SIGNAL(signalDisconnect(CPluginAbstract*)) , this , SLOT(slotDisconnect   (CPluginAbstract*)));

            (*m_list_plugins)[i]->stop();
        }
   }

    //Je récupère le plugin de plus haute priorité ex :serial port et gps => gps qui gagne pour un gps
    int priority = -1;
    CPluginAbstract *plugin = NULL;

    for (int i = 0 ; i < m_list_plugins_valid.count() ; i++)
    {
        if (m_list_plugins_valid[i]->getPriority() > priority)
        {
            priority = m_list_plugins_valid[i]->getPriority();
            plugin   = m_list_plugins_valid[i];
        }
    }

    if (plugin != NULL)
    {
        m_plugin = plugin;
        m_plugin->setUsed (true);
        m_plugin->setDevice(m_device);

        connect (m_plugin->getObject() , SIGNAL(signalDisconnect(CPluginAbstract*))         , this , SLOT(slotDisconnect   (CPluginAbstract*)));
        connect (m_plugin->getObject() , SIGNAL(signalUpdateServices ())         , this , SLOT(slotUpdateServices ())) ;

        m_plugin->start();

        emit signalUpdateTreeWidgetDeviceMonitor(this);
    }
}


//Périphérique déconnecté
void CDevice::slotDisconnect              (CPluginAbstract* _abstract_plugin)
{
    WRITE_ERROR_LOGGER()

    if (m_plugin == _abstract_plugin)
    {
        disconnect (m_plugin->getObject() , SIGNAL(signalDisconnect(CPluginAbstract*))          , this , SLOT(slotDisconnect   (CPluginAbstract*)));
        disconnect (m_plugin->getObject() , SIGNAL(signalUpdateServices ())         , this , SLOT(slotUpdateServices ())) ;
        m_plugin->setUsed (false);
        m_plugin->stop();

        m_plugin = NULL;

        emit signalUpdateTreeWidgetDeviceMonitor(this);
     }
}

//Rafraichissement des paramètres recu du périphérique
void CDevice::slotUpdateServices ()
{
    WRITE_ERROR_LOGGER()
    emit signalUpdateTreeWidgetDeviceMonitor(this);
}



