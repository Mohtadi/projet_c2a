#include "plugin_gprs.h"


CPluginGPRS::CPluginGPRS()
{
    setDataConnectionSettings();
    setDefaultData();

    m_list_string_validation.append("OK");


    m_device_type = QRegExp("/dev/ttyUSB[0-9]+");

    connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)),Qt::DirectConnection);
    connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()),Qt::DirectConnection);
}

CPluginGPRS::~CPluginGPRS()
{

}

QString CPluginGPRS::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginGPRS::getObject()
{
    return this;
}

void CPluginGPRS::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginGPRS::start()
{
    bool result = false;
    //Paramètrage de cutecom
    m_cute_com->m_deviceCb->addItem             (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    m_cute_com->m_deviceCb->setCurrentIndex         (m_cute_com->m_deviceCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()));
    m_cute_com->m_baudCb->setCurrentIndex           (m_cute_com->m_baudCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("BAUD_RATE").toString()));
    m_cute_com->m_dataBitsCb->setCurrentIndex       (m_cute_com->m_dataBitsCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DATA_BITS").toString()));
    m_cute_com->m_stopCb->setCurrentIndex           (m_cute_com->m_stopCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("STOP_BITS").toString()));
    m_cute_com->m_parityCb->setCurrentIndex         (m_cute_com->m_parityCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("PARITY").toString()));

    m_send_text = m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_TEXT").toString();
    m_cute_com->m_cmdLe->setText                    (m_send_text);

    m_cute_com->m_inputModeCb->setCurrentIndex      (m_cute_com->m_inputModeCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_MODE").toString()));

    m_cute_com->m_hardwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDSHAKE_SOFTWARE").toBool());
    m_cute_com->m_softwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDCHAKE_HARDWARE").toBool());
    m_cute_com->m_writeCb->setChecked           (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("READING").toBool());
    m_cute_com->m_readCb->setChecked            (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("WRITING").toBool());

    m_cute_com->m_applyCb->setChecked (true);

    m_data ="";
    if (m_device_type.exactMatch(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()))
    {
        bool data_valid = false;

        m_cute_com->connectTTY();

        if (m_cute_com->m_fd>0)
        {
            m_cute_com->execCmd();

            QTime time;
            time.start();
            while (data_valid == false && time.elapsed()<2500)
            {
                QApplication::processEvents();
                for (int i=0 ; i<m_list_string_validation.count() ; i++)
                {
                    if (m_data.contains (m_list_string_validation[i]) == true )
                    {
                        data_valid = true;
                        result = true;
                    }
                }
            }
        }
     }
    return result;
}

void CPluginGPRS::stop()
{
    m_cute_com->disconnectTTY();
}

QWidget *CPluginGPRS::getWidget()
{
    return m_cute_com;
}

int CPluginGPRS::getPriority()
{
    return 1;
}


bool  CPluginGPRS::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginGPRS::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}


void CPluginGPRS::slotReceiveData (QString &_data)
{
    m_data = _data;
    m_message += m_data;
    if (_data.contains("ERROR") == true || _data.contains("OK") == true || _data.contains("CONNECT")==true)
    {
         parseData();
         m_message = "";
    }
}

void CPluginGPRS::slotSendData  ()
{

    /*m_cute_com->m_deviceCb->addItem             (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    m_cute_com->m_deviceCb->setCurrentIndex         (m_cute_com->m_deviceCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()));
    m_cute_com->m_baudCb->setCurrentIndex           (m_cute_com->m_baudCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("BAUD_RATE").toString()));
    m_cute_com->m_dataBitsCb->setCurrentIndex       (m_cute_com->m_dataBitsCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DATA_BITS").toString()));
    m_cute_com->m_stopCb->setCurrentIndex           (m_cute_com->m_stopCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("STOP_BITS").toString()));
    m_cute_com->m_parityCb->setCurrentIndex         (m_cute_com->m_parityCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("PARITY").toString()));

    m_send_text = m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_TEXT").toString();
    m_cute_com->m_cmdLe->setText                    (m_send_text);

    m_cute_com->m_inputModeCb->setCurrentIndex      (m_cute_com->m_inputModeCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_MODE").toString()));

    m_cute_com->m_hardwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDSHAKE_SOFTWARE").toBool());
    m_cute_com->m_softwareCb->setChecked        (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDCHAKE_HARDWARE").toBool());
    m_cute_com->m_writeCb->setChecked           (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("READING").toBool());
    m_cute_com->m_readCb->setChecked            (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("WRITING").toBool());

    m_cute_com->m_applyCb->setChecked (true);*/


    if (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_TEXT").toString() != "")
    {
        m_send_text = m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_TEXT").toString();
        m_cute_com->m_cmdLe->setText (m_send_text);
        m_cute_com->execCmd();
    }
    else
    {
       m_byte_array = m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("INPUT_DATA").toByteArray();

        /*for (int i=0 ;  i <byte_array.count() ; i++)
        {
                m_cute_com->sendByte(byte_array[i], 1);

            //Attention si j'envoi une commande et que je recoi jamais rien
        }*/
        qDebug() <<m_byte_array.count();

       // for (int i=0 ; i < m_byte_array.count() ; i+=1000)
        {
            write(m_cute_com->m_fd, (m_byte_array.data()), m_byte_array.count());
        }

        qDebug() <<"fin";
    }
}

void CPluginGPRS::slotDisconnect ()
{
    setDefaultData();
    emit signalUpdateServices ();
    emit signalDisconnect(this);
}

void CPluginGPRS::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN" , "Plugin gprs"             , UNIT_NONE , DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"        , "gprs"                    , UNIT_NONE , DESCRIPTION_TYPE);
   m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"          , "gprs"    , UNIT_NONE , DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"        , false                     , UNIT_NONE , DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"      , ""                        , UNIT_NONE , DESCRIPTION_DEVICE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("BAUD_RATE"   , 115200                    ,  UNIT_NONE ,DESCRIPTION_BAUD_RATE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DATA_BITS"   , 8                         , UNIT_NONE , DESCRIPTION_DATA_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STOP_BITS"   , 1                         ,  UNIT_NONE ,DESCRIPTION_STOP_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("PARITY"      , "None"                    ,  UNIT_NONE ,DESCRIPTION_PARITY);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("INPUT_TEXT"  , "AT"                      ,  UNIT_NONE ,"INPUT_TEXT");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , ""                        , UNIT_NONE , "OUTPUT_TEXT");
m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("INPUT_DATA"  , QByteArray()                     , UNIT_NONE , "INPUT_DATA");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("INPUT_MODE"  , "CR,LF line end"          ,  UNIT_NONE ,"INPUT_MODE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDSHAKE_SOFTWARE" , false , UNIT_NONE , DESCRIPTION_HANDSHAKE_SOFTWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDCHAKE_HARDWARE" , false , UNIT_NONE , DESCRIPTION_HANDCHAKE_HARDWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("READING" , true , UNIT_NONE , DESCRIPTION_READING);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("WRITING" , true , UNIT_NONE , DESCRIPTION_WRITING);
}

void CPluginGPRS::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN" , "Plugin gprs"             , UNIT_NONE , "nom du plugin");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"        , "gprs"                    , UNIT_NONE , "type de périphérique");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"        , false                     ,  UNIT_NONE ,"périphérique utilisé");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"      , ""                        ,  UNIT_NONE ,"DEVICE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("BAUD_RATE"   , 115200                    ,  UNIT_NONE ,"BAUD_RATE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DATA_BITS"   , 8                         ,  UNIT_NONE ,"DATA_BITS");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STOP_BITS"   , 1                         ,  UNIT_NONE ,"STOP_BITS");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("PARITY"      , "None"                    ,  UNIT_NONE ,"PARITY");    //Valeures que peut prendre PARITY "None", "Odd" , "Even" , "Mark" , "Space"
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("INPUT_TEXT"  , "AT"                      , UNIT_NONE , "INPUT_TEXT");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , ""                        ,  UNIT_NONE ,"OUTPUT_TEXT");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("INPUT_MODE"  , "CR,LF line end"          , UNIT_NONE , "INPUT_MODE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDSHAKE_SOFTWARE" , false , UNIT_NONE , "HANDSHAKE_SOFTWARE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDCHAKE_HARDWARE" , false , UNIT_NONE , "HANDCHAKE_HARDWARE");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("READING" , true , UNIT_NONE , "READING");
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("WRITING" , true , UNIT_NONE , "WRITING");
}

void CPluginGPRS::parseData()
{
    qDebug() <<"["<<m_message<<"]";

    if (m_message.contains("OK"))
    {
        m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "OK");
        emit signalUpdateServices ();
    }
    else
    {
        if (m_message.contains("ERROR"))
        {
            m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "ERROR");
            emit signalUpdateServices ();
        }
        else
        {
            if (m_message.contains("IP"))
            {
                m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "IP");
                emit signalUpdateServices ();
            }
            else
            {
                if (m_message.contains("CONNECT"))
                {
                    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "CONNECT");
                    emit signalUpdateServices ();
                }
                else
                {
                    if (m_message.contains("DISCONNECT"))
                    {
                        m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "DISCONNECT");
                        emit signalUpdateServices ();
                    }
                    else
                    {
                        m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("OUTPUT_TEXT" , "UNKNOWN");
                        emit signalUpdateServices ();
                    }
                }
            }
        }
    }
}

Q_EXPORT_PLUGIN2(pluginGPRS , CPluginGPRS)

