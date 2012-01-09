#include "plugin_bluetooth.h"

CPluginBluetoothThread::CPluginBluetoothThread()
{

}

CPluginBluetoothThread::~CPluginBluetoothThread()
{

}

void CPluginBluetoothThread::setDeviceId (int _device_id)
{
    m_device_id = _device_id;
}

void CPluginBluetoothThread::setSocketId (int _socket_id)
{
    m_socket_id = _socket_id;
}

void CPluginBluetoothThread::setListDataPlugin (CListDataPlugin *_data_informations)
{
    m_list_data_plugin =  _data_informations;
}


/*
Pour détecter les périphériques avec obexftp : mais je ne récupère pas les nom des périphériques

char ** tableau = NULL;

tableau  = obexftp_discover_bt_src (NULL);

int i=0;
if (tableau != NULL)
{
    while (tableau[i]!='\0')
    {
        qDebug()<<tableau[i];
        i++;
    }
}

Je reste avec blueZ
*/

void CPluginBluetoothThread::run()
{
    m_stop = false;

    while (m_stop == false)
    {
        m_list_peripherique.clear();

        int max_rsp    = 255;
        int len        = 8;
        int flags      = IREQ_CACHE_FLUSH;
        char addr[19]  = { 0 };
        char name[248] = { 0 };

        inquiry_info *ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
        int num_rsp = hci_inquiry(m_device_id, len, max_rsp, NULL, &ii, flags);

        if( num_rsp > 0 )
        {
            for (int i = 0; i < num_rsp; i++)
            {
                ba2str(&(ii+i)->bdaddr, addr);
                memset(name, 0, sizeof(name));

                if (hci_read_remote_name(m_socket_id, &(ii+i)->bdaddr, sizeof(name),name, 0) < 0)
                {
                    strcpy(name, "unknown");
                }
                m_list_peripherique.append (QStringList()<<"["+QString(addr)+"]["+QString(name)+"]");
            }

            (*m_list_data_plugin)[INFORMATIONS_DATA].setValueData("DEVICES_CONNECTED" , m_list_peripherique.join("\n"));
            emit signalThread();
        }

        free( ii );

        msleep(10000);
    }
}


CPluginBluetoothThreadSendFile::CPluginBluetoothThreadSendFile()
{

}

CPluginBluetoothThreadSendFile::~CPluginBluetoothThreadSendFile()
{

}

void CPluginBluetoothThreadSendFile::setDevice (QString _device)
{
    m_device = _device;
}

void CPluginBluetoothThreadSendFile::setFile   (QStringList _files)
{
    m_files = _files;
}

void CPluginBluetoothThreadSendFile::setListDataPlugin (CListDataPlugin *_data_informations)
{
    m_list_data_plugin = _data_informations;
}

void CPluginBluetoothThreadSendFile::run()
{
    for (int i=0 ; i < m_files.count() ; i++)
    {
        int   channel  = -1;

        char *filename = NULL;
        obexftp_client_t *cli = NULL;
        int ret;

        QString filepath = QFile (m_files[i]).fileName();

        channel = obexftp_browse_bt_push(m_device.toUtf8().data());

        /* Open connection */
        (*m_list_data_plugin)[INFORMATIONS_DATA].setValueData ("FILES"  , m_files[i]);
        (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Open connection");
        emit signalThread();

        cli = obexftp_open(OBEX_TRANS_BLUETOOTH, NULL, NULL, NULL);
        if (cli == NULL)
        {
           (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Error opening obexftp client");
           emit signalThread();
        }
        else
        {
            /* Connect to device */
            (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Connect to device");
            emit signalThread();

            ret = obexftp_connect_push(cli, m_device.toUtf8().data(), channel);
            if (ret < 0)
            {
                /*obexftp_close(cli);
                cli = NULL;*/
                (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Error connecting to obexftp device");
                emit signalThread();
            }
            else
            {
                /* Push file */
                (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Push file");
                emit signalThread();

                ret = obexftp_put_file(cli, filepath.toUtf8().data(), filename);
                if (ret < 0)
                {
                     (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Error putting file");
                     emit signalThread();
                }
                else
                {
                    /* Disconnect */
                    (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Disconnect");
                    emit signalThread();

                    ret = obexftp_disconnect(cli);
                    if (ret < 0)
                    {
                         (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "Error disconnecting the client");
                         emit signalThread();
                    }
                    else
                    {
                         (*m_list_data_plugin)[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION" , "File transfert ok");
                         emit signalThread();
                    }
                }
            }
        }

        /* Close */
        obexftp_close(cli);
        cli = NULL;
        msleep(5000);
    }

}

CPluginBluetooth::CPluginBluetooth()
{
    setDataConnectionSettings();
    setDefaultData();

    m_device_type = QRegExp("bluetooth");

    connect (&m_thread , SIGNAL (signalThread()) , this , SLOT(slotThread()));
    connect (&m_thread_send_file , SIGNAL (signalThread()) , this , SLOT(slotThread()));

    m_timer.setSingleShot(false);
    m_timer.setInterval(2000);
    connect (&m_timer , SIGNAL (timeout()) , this , SLOT(slotDisconnect()));
}

CPluginBluetooth::~CPluginBluetooth()
{

}

QString CPluginBluetooth::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginBluetooth::getObject()
{
    return this;
}

void CPluginBluetooth::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}


/* Je ne sais pas si le périphérique est connecté ou pas avec obexftp, je reste avec blueZ */
bool CPluginBluetooth::start()
{
    bool result = false;

    if (m_device_type.exactMatch(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()))
    {
        //Détection d'un périphérique bluetooth;
        m_device_id = hci_get_route(NULL);
        if (m_device_id > -1)
        {
            m_socket_id = hci_open_dev(m_device_id);

            if (m_socket_id > - 1)
            {
                m_thread.setListDataPlugin(&m_list_data_plugin);
                m_thread.setDeviceId(m_device_id);
                m_thread.setSocketId(m_socket_id);
                m_thread.start();
                m_timer.start();
                result = true;
                //close (m_socket_id);
            }


        }

    }
    return result;
}

void  CPluginBluetooth::stop()
{
    m_timer.stop();
    close( m_socket_id );
}

QWidget* CPluginBluetooth::getWidget()
{
    return NULL;
}

int CPluginBluetooth::getPriority()
{
    return 0;
}

bool  CPluginBluetooth::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginBluetooth::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginBluetooth::slotReceiveData (QString & _data)
{
    m_data = _data;
}

void CPluginBluetooth::slotSendData    ()
{
    if (m_list_data_plugin[INFORMATIONS_DATA].getValueData ("ACTION") == "COPY_FILE")
    {
        m_thread_send_file.setDevice(m_list_data_plugin[INFORMATIONS_DATA].getValueData ("DEVICE_USED").toString());
        m_thread_send_file.setFile  (m_list_data_plugin[INFORMATIONS_DATA].getValueData ("FILES").toStringList());
        m_thread_send_file.setListDataPlugin (&m_list_data_plugin);
        m_thread_send_file.start();
    }
}

void CPluginBluetooth::slotDisconnect  ()
{
    //Détection d'un périphérique bluetooth;
    m_device_id = hci_get_route(NULL);
    m_socket_id = hci_open_dev(m_device_id);

    if (m_device_id < 0 || m_socket_id < 0)
    {
        setDefaultData();
        emit signalUpdateServices ();
        emit signalDisconnect(this);
    }
}

void CPluginBluetooth::slotThread()
{
    emit signalUpdateServices ();
}

void CPluginBluetooth::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN"             , "Plugin bluetooth"  , UNIT_NONE , DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"                    , "bluetooth"         , UNIT_NONE , DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"                      , "bluetooth"         , UNIT_NONE , DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"                    , false               , UNIT_NONE , DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"                  , ""                  , UNIT_NONE , DESCRIPTION_DEVICE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STATE_CONNECTION"        , ""                  , UNIT_NONE , "état de la connection");
}

void CPluginBluetooth::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("DEVICES_CONNECTED"  , "" , UNIT_NONE , "liste des périphériques connectés");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("DEVICE_USED"        , "" , UNIT_NONE , "périphérique utilisé");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("ACTION"             , "" , UNIT_NONE , "action à effectué par le périphérique");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData ("FILES"              , "" , UNIT_NONE , "fichier en cours");
}




Q_EXPORT_PLUGIN2(pluginBluetooth , CPluginBluetooth)

