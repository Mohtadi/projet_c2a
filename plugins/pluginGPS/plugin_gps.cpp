#include "plugin_gps.h"


/*
Exemple d'acquisition
S_TIME  "110003.000"
GPS_LATITUDE  "4914.48882N"
GPS_LONGITUDE  "00403.82836E"
GPS_TYPE_POSITIONNEMENT  "1"
GPS_NBR_SATELLITES  "08"
GPS_PRECISION_HORIZONTAL  "2.0"
GPS_ALTITUDE  "126.36M"
GPS_TIME  "110004.000"
GPS_LATITUDE  "4914.48865N"
GPS_LONGITUDE  "00403.82821E"
GPS_TYPE_POSITIONNEMENT  "1"
GPS_NBR_SATELLITES  "08"
GPS_PRECISION_HORIZONTAL  "2.0"
GPS_ALTITUDE  "126.31M"
*/

CPluginGPS::CPluginGPS()
{
    setDataConnectionSettings();
    setDefaultData();

    m_list_string_validation.append("$PSTMVER,GPSLIB_04.30.03+PAL");
    m_list_string_validation.append("$GPGGA");
    m_list_string_validation.append("$GPVTG");
    m_list_string_validation.append("$GPGSA");
    m_list_string_validation.append("$GPGLL");

    m_device_type = QRegExp("/dev/ttyUSB[0-9]+");

    connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)),Qt::DirectConnection);
    connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()),Qt::DirectConnection);
}

CPluginGPS::~CPluginGPS()
{

}

QString CPluginGPS::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginGPS::getObject()
{
    return this;
}

void CPluginGPS::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginGPS::start()
{
    bool result = false;
    //Paramètrage de cutecom
    m_cute_com->m_deviceCb->addItem             (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    m_cute_com->m_deviceCb->setItemText         (0,m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());
    m_cute_com->m_baudCb->setCurrentIndex       (m_cute_com->m_baudCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("BAUD_RATE").toString()));
    m_cute_com->m_dataBitsCb->setCurrentIndex   (m_cute_com->m_dataBitsCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DATA_BITS").toString()));
    m_cute_com->m_stopCb->setCurrentIndex       (m_cute_com->m_stopCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("STOP_BITS").toString()));
    m_cute_com->m_parityCb->setCurrentIndex     (m_cute_com->m_parityCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("PARITY").toString()));

    m_cute_com->m_hardwareCb->setChecked       (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDSHAKE_SOFTWARE").toBool());
    m_cute_com->m_softwareCb->setChecked       (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDCHAKE_HARDWARE").toBool());
    m_cute_com->m_writeCb->setChecked          (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("READING").toBool());
    m_cute_com->m_readCb->setChecked           (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("WRITING").toBool());

    m_cute_com->m_applyCb->setChecked (true);

    m_message = "";

    m_data = "";

    if (m_device_type.exactMatch(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()))
    {

        bool data_valid = false;

        m_cute_com->connectTTY();

        if (m_cute_com->m_fd>0)
        {
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

void CPluginGPS::stop()
{
    m_cute_com->disconnectTTY();
}

QWidget *CPluginGPS::getWidget()
{
    return m_cute_com;
}

int CPluginGPS::getPriority()
{
    return 1;
}


bool  CPluginGPS::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginGPS::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}


/*
$GPGGA,000110.000,0000.00000,N,00000.00000,E,0,00,99.0,082.0
0,M,18.0,M,,*5E
$GPVTG,0.0,T,,M,0.0,N,0.0,K*60
$GPGSA,A,1,,,,,,,,,,,,,99.0,99.0,99.0*00
$GPGLL,0000.000,N,00000.000,E,000110.000,V*23
*/

//Je recoit tout le message en 2 fois, je reconstruit donc tout le message en une seul chaine avant de parser
void CPluginGPS::slotReceiveData (QString &_data)
{
    m_data = _data;

    if (m_data.contains("GPGGA") == true)
    {
        m_message = m_data;

    }
    else
    {
        if (m_message.contains("GPGGA") == true)
        {
            m_message += m_data;
            parseToMessage();
            m_message = "";
        }
    }
}

void CPluginGPS::slotDisconnect ()
{
    setDefaultData();
    emit signalUpdateServices ();
    emit signalDisconnect(this);
}

void CPluginGPS::setDataConnectionSettings ()
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN"             , "Plugin gps"              , UNIT_NONE , DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"                    , "gps"                     , UNIT_NONE , DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"                      , "gps"                     , UNIT_NONE , DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"                    , false                     , UNIT_NONE , DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"                  , ""                        , UNIT_NONE , DESCRIPTION_DEVICE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("BAUD_RATE"               , 4800                      , UNIT_NONE , DESCRIPTION_BAUD_RATE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DATA_BITS"               , 8                         , UNIT_NONE , DESCRIPTION_DATA_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STOP_BITS"               , 1                         , UNIT_NONE , DESCRIPTION_STOP_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("PARITY"                  , "None"                    , UNIT_NONE , DESCRIPTION_PARITY);

    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDSHAKE_SOFTWARE"      , false                     , UNIT_NONE , DESCRIPTION_HANDSHAKE_SOFTWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDCHAKE_HARDWARE"      , false                     , UNIT_NONE , DESCRIPTION_HANDCHAKE_HARDWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("READING"                 , true                      , UNIT_NONE , DESCRIPTION_READING);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("WRITING"                 , true                      , UNIT_NONE , DESCRIPTION_WRITING);
}

void CPluginGPS::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_HEURE"             , 0 , "h"       , "heure");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_MINUTE"            , 0 , "m"       , "minute");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_SECONDE"           , 0 , "s"       , "seconde");

    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_DEGRE"         , 0 , "degré"   , "latitude en degré");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_MINUTE"        , 0 , "minute"  , "latitude en minute");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_SECONDE"       , 0 , "seconde" , "latitude en seconde");

    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_DEGRE"        , 0 , "degré"   , "longitude en degré");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_MINUTE"       , 0 , "minute"  , "longitude en minute");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_SECONDE"      , 0 , "seconde" , "longitude en seconde");

    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TYPE_POSITIONNEMENT"    , 0 , UNIT_NONE , "type de positionnement");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_NBR_SATELLITES"         , 0 , UNIT_NONE , "nombre de satellites");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_PRECISION_HORIZONTAL"   , 0 , UNIT_NONE , "précision horizontal");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_ALTITUDE"               , 0 , UNIT_NONE , "altitude");
}

//La variable m_message contient tout le paquet, je peux parser
void CPluginGPS::parseToMessage ()
{
    //Je retire tout ce qui peut être avant $GPGGA sinon la liste est mal formé et il y a des problèmes d'indice
    int taille = m_message.indexOf(QRegExp("GPGGA"));
    m_message.remove(0 , taille);

    //Je retire tout ce qui est apres le retour chariot de fin de ligne
    int index = m_message.indexOf(QRegExp("\n"));
    m_message.remove(index ,m_message.length() - index);

    QStringList list_GPGGA = m_message.split(',');

    if (10 < list_GPGGA.count())
    {
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_HEURE"             , list_GPGGA[1].mid(0,2));
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_MINUTE"            , list_GPGGA[1].mid(2,2));
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TIME_SECONDE"           , list_GPGGA[1].mid(4,2));

        int latitude_degre   =  list_GPGGA[2].mid(0,2).toInt();
        int latitude_minute  =  list_GPGGA[2].mid(2,2).toInt();
        int latitude_seconde =  list_GPGGA[2].mid(5,5).toFloat()/100.0*60.0;
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_DEGRE"         , latitude_degre);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_MINUTE"        , latitude_minute);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LATITUDE_SECONDE"       , latitude_seconde);

        int longitude_degre   =  list_GPGGA[4].mid(1,2).toInt();
        int longitude_minute  =  list_GPGGA[4].mid(3,2).toInt();
        int longitude_seconde =  list_GPGGA[4].mid(6,5).toFloat()/100.0*60.0;
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_DEGRE"        , longitude_degre);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_MINUTE"       , longitude_minute);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_LONGITUDE_SECONDE"      , longitude_seconde);

        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_TYPE_POSITIONNEMENT"    , list_GPGGA[6]);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_NBR_SATELLITES"         , list_GPGGA[7]);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_PRECISION_HORIZONTAL"   , list_GPGGA[8]);
        m_list_data_plugin[INFORMATIONS_DATA].setValueData("GPS_ALTITUDE"               , list_GPGGA[9] + list_GPGGA[10]);
    }

    emit signalUpdateServices ();
}

Q_EXPORT_PLUGIN2(pluginGPS , CPluginGPS)

