#include "plugin_network.h"



CPluginNetwork::CPluginNetwork()
{
    setDataConnectionSettings();
    setDefaultData();

    m_device_type = QRegExp("network");
    m_timer.setSingleShot(false);
    m_timer.setInterval  (5000);
    connect(&m_timer , SIGNAL (timeout()) , this , SLOT (slotUpdate()));
}

CPluginNetwork::~CPluginNetwork()
{

}

QString CPluginNetwork::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginNetwork::getObject()
{
    return this;
}

void CPluginNetwork::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}


/* Je ne sais pas si le périphérique est connecté ou pas avec obexftp, je reste avec blueZ */
bool CPluginNetwork::start()
{
    bool result = false;

    if (m_device_type.exactMatch(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()))
    {
        m_list_network_interface = QNetworkInterface::allInterfaces();

        if (m_list_network_interface.count() > 0)
        {
            result = true;
            m_timer.start();
        }
    }
    return result;
}

void  CPluginNetwork::stop()
{
    m_timer.stop();
}

void CPluginNetwork::slotUpdate()
{
    m_list_network_interface = QNetworkInterface::allInterfaces();
    QStringList list_human_readable_name;
    QStringList list_hardware_address;
    QStringList list_ip_address;
    QStringList list_valid;
    QStringList list_flags;

    for (int i = 0 ; i < m_list_network_interface.count(); i++)
    {
        list_human_readable_name.append (m_list_network_interface[i].humanReadableName ());
        list_hardware_address.append    (m_list_network_interface[i].hardwareAddress());

        QString ip_address = "";
        for (int j=0 ; j<m_list_network_interface[i].addressEntries().count() ; j++)
        {
            ip_address += "[" + m_list_network_interface[i].addressEntries()[j].ip().toString()+"]";
        }
        list_ip_address.append (ip_address);


        if (m_list_network_interface[i].isValid ())
        {
            list_valid.append ("valide");
        }
        else
        {
            list_valid.append ("non valide");
        }

        QString flags = "";
        if ((QNetworkInterface::IsUp & m_list_network_interface[i].flags()) == QNetworkInterface::IsUp)
        {
            flags +="[the network interface is active]";
        }

        if ((QNetworkInterface::IsRunning & m_list_network_interface[i].flags()) == QNetworkInterface::IsRunning)
        {
            flags +="[the network interface has resources allocated]";
        }

        if ((QNetworkInterface::CanBroadcast & m_list_network_interface[i].flags()) == QNetworkInterface::CanBroadcast)
        {
            flags +="[the network interface works in broadcast mode]";
        }

        if ((QNetworkInterface::IsLoopBack & m_list_network_interface[i].flags()) == QNetworkInterface::IsLoopBack)
        {
            flags +="[the network interface is a loopback interface: that is, it's a virtual interface whose destination is the host computer itself]";
        }

        if ((QNetworkInterface::IsPointToPoint & m_list_network_interface[i].flags()) == QNetworkInterface::IsPointToPoint)
        {
            flags +="[the network interface is a point-to-point interface: that is, there is one, single other address that can be directly reached by it.]";
        }

        if ((QNetworkInterface::CanMulticast & m_list_network_interface[i].flags()) == QNetworkInterface::CanMulticast)
        {
            flags +="[the network interface supports multicasting]";
        }
        list_flags.append (flags);
    }


    QString string_human_readable_name = list_human_readable_name.join("\n");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("DEVICES_LIST"       , string_human_readable_name);

    QString string_hardware_address = list_hardware_address.join("\n");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("HARDWARE_LIST"       , string_hardware_address);

    QString string_ip_address = list_ip_address.join("\n");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("IP_LIST"       , string_ip_address);

    QString string_valid = list_valid.join("\n");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("VALID_LIST"          , string_valid);

    QString flags = list_flags.join("\n");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("STATE_LIST"         , flags);

    emit signalUpdateServices ();
}

QWidget* CPluginNetwork::getWidget()
{
    return NULL;
}

int CPluginNetwork::getPriority()
{
    return 0;
}

bool  CPluginNetwork::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginNetwork::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginNetwork::slotReceiveData (QString &)
{

}

void CPluginNetwork::slotSendData    ()
{

}

void CPluginNetwork::slotDisconnect  ()
{
    //Détection d'un périphérique bluetooth;

}

void CPluginNetwork::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN"             , "Plugin network"                  , UNIT_NONE , DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"                    , "network"                         , UNIT_NONE , DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"                      , "network"                         , UNIT_NONE , DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"                    , false                             , UNIT_NONE , DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"                  , ""                                , UNIT_NONE , DESCRIPTION_DEVICE);
}

void CPluginNetwork::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("DEVICES_LIST"       , "" , UNIT_NONE , "liste des périphériques détectés");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("HARDWARE_LIST"      , "" , UNIT_NONE , "liste des adresses matériels des périphériques");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("IP_LIST"            , "" , UNIT_NONE , "liste des adresses IP associées au périphériques");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("VALID_LIST"         , "" , UNIT_NONE , "liste des périphériques valides");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("STATE_LIST"         , "" , UNIT_NONE , "liste d'états des périphériques");
}




Q_EXPORT_PLUGIN2(pluginNetwork , CPluginNetwork)

