#include "plugin_corsair.h"


CPluginCorsair::CPluginCorsair()
{

    setDataConnectionSettings ();
    setDefaultData();


    m_device_type = "/media/CORSAIR/";

    //connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)),Qt::DirectConnection);

    m_timer.setInterval(1000);
    m_timer.setSingleShot(false);
    connect (&m_timer , SIGNAL(timeout()) , this , SLOT(slotDisconnect()));
    //connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()),Qt::DirectConnection);
}

CPluginCorsair::~CPluginCorsair()
{

}

QString CPluginCorsair::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginCorsair::getObject()
{
    return this;
}

void CPluginCorsair::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginCorsair::start()
{
    bool result = false;

    if (m_device_type == m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString())
    {
        QFile file (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

        if (file.exists() == true)
        {
            //Je ne m'attend pas à recevoir des données ici, comme je suis utilisé je vais parser directement
            if (isUsed() == true)
            {
                m_timer.start();
                //Je met un timer parce que si je parse de suite des fois il à pas le temps de monter la clé et il ne voit pas les fichiers
                QTimer::singleShot(2000 , this , SLOT(parseDirectory()));
            }

            result = true;
         }
     }
    return result;
}

void CPluginCorsair::stop()
{
    m_timer.stop();
}

QWidget *CPluginCorsair::getWidget()
{
    return NULL;
}

int CPluginCorsair::getPriority()
{
    return 1;
}

bool  CPluginCorsair::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginCorsair::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginCorsair::slotReceiveData (QString &)
{

}

void CPluginCorsair::slotDisconnect ()
{
    QFile file (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    if (file.exists() == false)
    {
        setDefaultData();
        emit signalUpdateServices ();
        emit signalDisconnect(this);
    }
}

void CPluginCorsair::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN" , "Plugin CORSAIR"      ,  UNIT_NONE ,DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"        , "clé usb"             ,  UNIT_NONE ,DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"          , "cle_usb_corsaire"    ,  UNIT_NONE ,DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"        , false                 ,  UNIT_NONE ,DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"      , ""                    ,  UNIT_NONE ,DESCRIPTION_DEVICE);
}

void CPluginCorsair::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("1_FILE"   , "" ,  UNIT_NONE ,"premier fichier");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("ALL_FILE" , "" ,  UNIT_NONE ,"tout les fichiers");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("END_FILE" , "" ,  UNIT_NONE ,"dernier fichier");
}

void CPluginCorsair::parseDirectory()
{
    QDir dir = QDir("/media/CORSAIR/");

    QStringList list_absolute_path_files;
    foreach (QString fileName , dir.entryList(QDir::Files))
    {
        list_absolute_path_files.append (dir.absoluteFilePath(fileName));
    }

    if (list_absolute_path_files.count() > 0)
    {
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("1_FILE"   , list_absolute_path_files[0]);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("ALL_FILE" , list_absolute_path_files.join("\n"));
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("END_FILE" , list_absolute_path_files[list_absolute_path_files.count() - 1]);
    }

    emit signalUpdateServices ();
}

Q_EXPORT_PLUGIN2(pluginCorsair , CPluginCorsair)

