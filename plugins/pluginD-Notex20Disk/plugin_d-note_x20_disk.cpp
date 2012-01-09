#include "plugin_d-note_x20_disk.h"


CPluginDNoteX20Disk::CPluginDNoteX20Disk()
{

    setDataConnectionSettings ();
    setDefaultData();


    m_device_type = "/media/D-NOTE DISK/";

    //connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)),Qt::DirectConnection);

    m_timer.setInterval(1000);
    m_timer.setSingleShot(false);
    connect (&m_timer , SIGNAL(timeout()) , this , SLOT(slotDisconnect()));
    //connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()),Qt::DirectConnection);
}

CPluginDNoteX20Disk::~CPluginDNoteX20Disk()
{

}

QString CPluginDNoteX20Disk::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginDNoteX20Disk::getObject()
{
    return this;
}

void CPluginDNoteX20Disk::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginDNoteX20Disk::start()
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

void CPluginDNoteX20Disk::stop()
{
    m_timer.stop();
}

QWidget *CPluginDNoteX20Disk::getWidget()
{
    return NULL;
}

int CPluginDNoteX20Disk::getPriority()
{
    return 1;
}

bool  CPluginDNoteX20Disk::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginDNoteX20Disk::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginDNoteX20Disk::slotReceiveData (QString &)
{

}

void CPluginDNoteX20Disk::slotDisconnect ()
{
    QFile file (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    if (file.exists() == false)
    {
        setDefaultData();
        emit signalUpdateServices ();
        emit signalDisconnect(this);
    }
}

void CPluginDNoteX20Disk::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN" , "Plugin D-Note Disk"  ,  UNIT_NONE ,DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"        , "tablette tactile"    ,  UNIT_NONE ,DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"          , "tablette_tactile"    ,  UNIT_NONE ,DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"        , false                 ,  UNIT_NONE ,DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"      , ""                    ,  UNIT_NONE ,DESCRIPTION_DEVICE);
}

void CPluginDNoteX20Disk::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("1_FILE"   , "" ,  UNIT_NONE ,"premier fichier");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("ALL_FILE" , "" ,  UNIT_NONE ,"tout les fichiers");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("END_FILE" , "" ,  UNIT_NONE ,"dernier fichier");
}

void CPluginDNoteX20Disk::parseDirectory()
{
    QDir dir = QDir("/media/D-NOTE DISK/");

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

Q_EXPORT_PLUGIN2(pluginDNoteX20Disk , CPluginDNoteX20Disk)

