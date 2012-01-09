#include "plugin_serial_port.h"

CPluginSerialPort::CPluginSerialPort()
{
    setDataConnectionSettings();
    setDefaultData();

    connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)));
    connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()));
}

CPluginSerialPort::~CPluginSerialPort()
{

}

QString CPluginSerialPort::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginSerialPort::getObject()
{
    return this;
}

void CPluginSerialPort::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginSerialPort::start()
{
    bool result = false;
    //Paramètrage de cutecom
    m_cute_com->m_deviceCb->addItem             (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    m_cute_com->m_deviceCb->setCurrentIndex         (m_cute_com->m_deviceCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()));
    m_cute_com->m_baudCb->setCurrentIndex           (m_cute_com->m_baudCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("BAUD_RATE").toString()));
    m_cute_com->m_dataBitsCb->setCurrentIndex       (m_cute_com->m_dataBitsCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DATA_BITS").toString()));
    m_cute_com->m_stopCb->setCurrentIndex           (m_cute_com->m_stopCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("STOP_BITS").toString()));
    m_cute_com->m_parityCb->setCurrentIndex         (m_cute_com->m_parityCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("PARITY").toString()));

    m_cute_com->m_hardwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDSHAKE_SOFTWARE").toBool());
    m_cute_com->m_softwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDCHAKE_HARDWARE").toBool());
    m_cute_com->m_writeCb->setChecked           (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("READING").toBool());
    m_cute_com->m_readCb->setChecked            (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("WRITING").toBool());

    m_cute_com->m_applyCb->setChecked (true);

    m_data ="";

    bool data_valid = false;

    m_cute_com->connectTTY();

    if (m_cute_com->m_fd > 0)
    {
        QTime time;
        time.start();
        while (data_valid == false && time.elapsed()<500 )
        {
            QApplication::processEvents();
            if (m_data != "" )
            {
                data_valid = true;
                result = true;
            }
        }
    }
    return result;
}

void  CPluginSerialPort::stop()
{
    m_cute_com->disconnectTTY();
}


QWidget* CPluginSerialPort::getWidget()
{
    return m_cute_com;
}

int CPluginSerialPort::getPriority()
{
    return 0;
}

bool  CPluginSerialPort::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginSerialPort::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginSerialPort::slotReceiveData (QString & _data)
{
    m_data = _data;
}

void CPluginSerialPort::slotDisconnect  ()
{
    setDefaultData();
    emit signalUpdateServices ();
    emit signalDisconnect(this);
}

void CPluginSerialPort::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN"             , "Plugin serial port"  , UNIT_NONE , DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"                    , "inconnu"             , UNIT_NONE , DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"                      , "serial_port"         , UNIT_NONE , DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"                    , false                 , UNIT_NONE , DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"                  , ""                    , UNIT_NONE , DESCRIPTION_DEVICE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("BAUD_RATE"               , 4800                  , UNIT_NONE , DESCRIPTION_BAUD_RATE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DATA_BITS"               , 8                     , UNIT_NONE , DESCRIPTION_DATA_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STOP_BITS"               , 1                     , UNIT_NONE , DESCRIPTION_STOP_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("PARITY"                  , "None"                , UNIT_NONE , DESCRIPTION_PARITY);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDSHAKE_SOFTWARE"      , false                 , UNIT_NONE , DESCRIPTION_HANDSHAKE_SOFTWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDCHAKE_HARDWARE"      , false                 , UNIT_NONE , DESCRIPTION_HANDCHAKE_HARDWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("READING"                 , true                  , UNIT_NONE , DESCRIPTION_READING);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("WRITING"                 , true                  , UNIT_NONE , DESCRIPTION_WRITING);

}

void CPluginSerialPort::setDefaultData()
{
}


Q_EXPORT_PLUGIN2(pluginSerialPort , CPluginSerialPort)

