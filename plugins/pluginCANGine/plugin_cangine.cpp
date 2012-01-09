#include "plugin_cangine.h"

/*
C2ACamion
0-00:11:55.040
EngSpeed 3217,375 rpm
Accel    0
,0 %
TCO      72,36 km/h MD:0  OS:0  DI:0  TP:0  HI:0  EV:0  D1:0/0/0 D2:0/0/0
Speed    72,36 km/h CC:0 BR:0 CS:0 PB:0
Distance 0,000 km
EngHours 0,00 h
FuelC    0,0 L
EngTemp  +57 degr
FuelLev  46,8 %
VehID
FMS      02.51 Diag:0 Requ:0
Gear     S:* C:*
DoorCtr1 P:* R:* S:*
DC2 loe  1:* 2:* 3:* 4:* 5:* 6:* 7:* 8:* 9:* 10:*
BellowPr FAL:* kPa FAR:* kPa RAL:* kPa RAR:* kPa
BrakePr  1:* kPa 2:* kPa
Alternat 1:* 2:* 3:* 4:*
DateTime *
AmbTemp  * degr
*/

CPluginCANGine::CPluginCANGine()
{
    setDataConnectionSettings ();
    setDefaultData ();

    m_list_string_validation.append("C2ACamion");
    m_list_string_validation.append("EngSpeed");
    m_list_string_validation.append("Accel");
    m_list_string_validation.append("TCO");
    m_list_string_validation.append("Speed");
    m_list_string_validation.append("Distance");
    m_list_string_validation.append("EngHours");
    m_list_string_validation.append("FuelC");
    m_list_string_validation.append("EngTemp");
    m_list_string_validation.append("FuelLev");
    m_list_string_validation.append("VehID");
    m_list_string_validation.append("FMS");
    m_list_string_validation.append("Gear");
    m_list_string_validation.append("DoorCtr1");
    m_list_string_validation.append("DC2 loe");
    m_list_string_validation.append("BellowPr");
    m_list_string_validation.append("BrakePr");
    m_list_string_validation.append("Alternat");
    m_list_string_validation.append("DateTime");
    m_list_string_validation.append("AmbTemp");

    m_device_type = QRegExp("/dev/ttyS[0-9]+|/dev/USB[0-9]+");

    connect (m_cute_com , SIGNAL (signalReceiveData(QString&)) , this , SLOT(slotReceiveData(QString&)));
    connect (m_cute_com , SIGNAL (signalDisconnect()) , this , SLOT(slotDisconnect()));
    connect (&m_time_disconnect , SIGNAL(timeout()) , this , SLOT(slotDisconnect()));
}

CPluginCANGine::~CPluginCANGine()
{

}

QString CPluginCANGine::getNamePlugin()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString();
}

QObject *CPluginCANGine::getObject()
{
    return this;
}

void CPluginCANGine::setDevice (QString _device)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE" , _device);
}

bool CPluginCANGine::start()
{
    bool result = false;
    //Paramètrage de cutecom
    m_cute_com->m_deviceCb->addItem             (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString());

    m_cute_com->m_deviceCb->setCurrentIndex         (m_cute_com->m_deviceCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()));
    m_cute_com->m_baudCb->setCurrentIndex           (m_cute_com->m_baudCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("BAUD_RATE").toString()));
    m_cute_com->m_dataBitsCb->setCurrentIndex       (m_cute_com->m_dataBitsCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DATA_BITS").toString()));
    m_cute_com->m_stopCb->setCurrentIndex           (m_cute_com->m_stopCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("STOP_BITS").toString()));
    m_cute_com->m_parityCb->setCurrentIndex         (m_cute_com->m_parityCb->findText(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("PARITY").toString()));

    m_cute_com->m_hardwareCb->setChecked       (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDSHAKE_SOFTWARE").toBool());
    m_cute_com->m_softwareCb->setChecked       (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("HANDCHAKE_HARDWARE").toBool());
    m_cute_com->m_writeCb->setChecked          (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("READING").toBool());
    m_cute_com->m_readCb->setChecked           (m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("WRITING").toBool());

    m_cute_com->m_applyCb->setChecked (true);

    m_data ="";

    //Si je suis sur une connection rs232
    if (m_device_type.exactMatch(m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("DEVICE").toString()))
    {
        m_cute_com->connectTTY();
        if (m_cute_com->m_fd >0 )
        {
            bool data_valid = false;
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
                        m_time_disconnect.setSingleShot (false);
                        m_time_disconnect.start(1000);
                        result = true;
                    }
                }
             }
        }
     }
    return result;
}

void CPluginCANGine::stop()
{
    m_cute_com->disconnectTTY();
}


QWidget *CPluginCANGine::getWidget()
{
    return m_cute_com;
}

int CPluginCANGine::getPriority()
{
    return 1;
}

bool  CPluginCANGine::isUsed()
{
    return m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("USED").toBool();
}

void  CPluginCANGine::setUsed  (bool _used)
{
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED" , _used);
}

void CPluginCANGine::slotReceiveData (QString &_data)
{
    //Je remet à 0 dès que je reçoit une donnée
    m_cpt_iteration_data = 0;

    m_data = _data;

    if (m_data.contains("C2ACamion"))
    {
        m_message = m_data;
    }
    else
    {
        if (m_message.contains("C2ACamion"))
        {
            m_message += m_data;

            parseToMessage();

            m_message = "";
        }
    }
}

void CPluginCANGine::slotDisconnect  ()
{
    //J'incrémente si c'est < 2 , et si je ne reçoit jamais de données le compteur n'est pas remis à 0 , le timer est initialié à 1 seconde
    if (m_cpt_iteration_data == 2)
    {
        //Donc si je ne recoit pas de donnée au bout de 2 secondes je me déconnecte.
        setDefaultData();
        emit signalUpdateServices ();
        emit signalDisconnect(this);
    }
    else
    {
        m_cpt_iteration_data ++;
    }
}

void CPluginCANGine::setDataConnectionSettings ()
{

    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("NAME_PLUGIN"          , "Plugin cangine" ,  UNIT_NONE ,DESCRIPTION_NAME_PLUGIN);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("TYPE"                 , "cangine"        ,  UNIT_NONE ,DESCRIPTION_TYPE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("ID"                   , "cangine"        ,  UNIT_NONE ,DESCRIPTION_ID);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("USED"                 , false            ,  UNIT_NONE ,DESCRIPTION_USED);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DEVICE"               , ""               ,  UNIT_NONE ,DESCRIPTION_DEVICE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("BAUD_RATE"            , 19200            ,  UNIT_NONE ,DESCRIPTION_BAUD_RATE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("DATA_BITS"            , 8                ,  UNIT_NONE ,DESCRIPTION_DATA_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("STOP_BITS"            , 1                ,  UNIT_NONE ,DESCRIPTION_STOP_BITS);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("PARITY"               , "None"           ,  UNIT_NONE ,DESCRIPTION_PARITY);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDSHAKE_SOFTWARE"   , false            ,  UNIT_NONE ,DESCRIPTION_HANDSHAKE_SOFTWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("HANDCHAKE_HARDWARE"   , false            ,  UNIT_NONE ,DESCRIPTION_HANDCHAKE_HARDWARE);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("READING"              , true             ,  UNIT_NONE ,DESCRIPTION_READING);
    m_list_data_plugin[INFORMATIONS_CONNECTIONS_SETTINGS].setValueData("WRITING"              , true             ,  UNIT_NONE ,DESCRIPTION_WRITING);
}

void CPluginCANGine::setDefaultData()
{
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGSPEED"  , 0 ,  "tr/min" ,"vitesse du moteur (tr/min)");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ACCEL"     , 0 ,  "%" ,"position de l'accélérateur %");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO"       , 0 ,  UNIT_NONE ,"information du tachygraphe");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_MD"    , 0 ,  UNIT_NONE ,"détection de mouvement");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_OS"    , 0 ,  UNIT_NONE ,"détection de sur vitesse"); //ATTention problème de caractère - avec la base de donnée.
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_DI"    , 0 ,  UNIT_NONE ,"direction 0 : avant , 1 : arrière");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_TP"    , 0 ,  UNIT_NONE ,"performance du tachygraphe");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_HI"    , 0 ,  UNIT_NONE ,"traitement d'information");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_EV"    , 0 ,  UNIT_NONE ,"incident du tachygraphe");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_D1"    , 0 ,  UNIT_NONE ,"conducteur 0 : absent , 1: présent");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_D2"    , 0 ,  UNIT_NONE ,"conducteur 0 : absent , 1: présent");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED"     , 0 ,  "km/h"    ,"vitesse");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_CC"  , 0 ,  UNIT_NONE ,"régulateur de vitesse");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_BR"  , 0 ,  UNIT_NONE ,"activation des freins");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_CS"  , 0 ,  UNIT_NONE ,"activation de l'embrayage");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_PB"  , 0 ,  UNIT_NONE ,"état du frein à main");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DISTANCE"  , 0 ,  UNIT_NONE ,"distance parcourue");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGHOURS"  , 0 ,  UNIT_NONE ,"durée du moteur");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FUELC"     , 0 ,  UNIT_NONE ,"consommation de carburant");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGTEMP"   , 0 ,  UNIT_NONE ,"température du liquide de refroidissement");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FUELLEV"   , 0 ,  "litre"   ,"niveau de carburant");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_VEHID"     , 0 ,  UNIT_NONE ,"identification du véhicule");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS"       , 0 ,  UNIT_NONE ,"version du logiciel");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS_DIAG"  , 0 ,  UNIT_NONE ,"PCAN_FMS_DIAG");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS_REQU"  , 0 ,  UNIT_NONE ,"PCAN_FMS_REQU");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_GEAR_S"    , 0 ,  UNIT_NONE ,"boite de vitesse, vitesse séléctionnée. Les valeurs négatives sont marche arrière, la valeur 0 signifie neutre et 126 signifie position de parking.");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_GEAR_C"    , 0 ,  UNIT_NONE ,"boite de vitesse, vitesse en cours. Les valeurs négatives sont marche arrière, la valeur 0 signifie neutre et 126 signifie position de parking.");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_P", 0 ,  UNIT_NONE ,"position des portières 0 : au moins une portière ouverte , 1 : dernière portière fermée , 2 : toutes les portières fermées");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_R", 0 ,  UNIT_NONE ,"état de l'élévateur (pour fauteuil roulant) 0 : dans le véhicule , 1 : à l’extérieur");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_S", 0 ,  UNIT_NONE ,"état général 0 : toutes les portières désactivées , 1 : au moins une portière activée");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2"       , 0 ,  UNIT_NONE ,"Etat des portières 2  seulement prise en compte dans le protocole Bus FMS");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_1"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_2"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_3"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_4"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_5"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_6"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_7"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_8"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_9"     , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_10"    , 0 ,  UNIT_NONE ,"L (LockState) 0 : La portière peut être actionnée par le conducteur ou le passager , 1 : La portière ne peut être actionnée O (OpenState) 0 : La portière est fermée , 1 : la portière n'est pas fermée E (EnableState) 0 : La portère ne peut pas être ouverte par un passager , 1 : La portière peut être ouverte par un passager");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_FAL"  , 0 ,  UNIT_NONE ,"PCAN_BELLOWPR_FAL");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_FAR"  , 0 ,  UNIT_NONE ,"PCAN_BELLOWPR_FAR");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_RAL"  , 0 ,  UNIT_NONE ,"PCAN_BELLOWPR_RAL");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_RAR"  , 0 ,  UNIT_NONE ,"PCAN_BELLOWPR_RAR");

    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BRAKEPR_1"  , 0 ,  UNIT_NONE ,"PCAN_BRAKEPR_1");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BRAKEPR_2"  , 0 ,  UNIT_NONE ,"PCAN_BRAKEPR_2");

    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_1" , 0 ,  UNIT_NONE ,"PCAN_ALTERNAT_1");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_2" , 0 ,  UNIT_NONE ,"PCAN_ALTERNAT_2");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_3" , 0 ,  UNIT_NONE ,"PCAN_ALTERNAT_3");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_4" , 0 ,  UNIT_NONE ,"PCAN_ALTERNAT_4");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DATETIME"   , 0 ,  UNIT_NONE ,"PCAN_DATETIME");
    m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_AMBTEMP"    , 0 ,  UNIT_NONE ,"PCAN_AMBTEMP");
}

/*
  Message type
"C2ACamion"
"0-02:06:18.040"
"EngSpeed 898,500 rpm"
"Accel    0,0 %"
"TCO      114,30 km/h MD:0  OS:0  DI:0  TP:0  HI:0  EV:0  D1:0/0/0 D2:0/0/0"
"Speed    114,30 km/h CC:0 BR:0 CS:0 PB:0"
"Distance 0,000 km"
"EngHours 1,90 h"
"FuelC    0,0 L"
"EngTemp  +61 degr"
"FuelLev  36,8 %"
"VehID    azerty"
"FMS      02.51 Diag:0 Requ:0"
"Gear     S:* C:*"
"DoorCtr1 P:* R:* S:*"
"DC2 loe  1:* 2:* 3:* 4:* 5:* 6:* 7:* 8:* 9:* 10:*"
"BellowPr FAL:* kPa FAR:* kPa RAL:* kPa RAR:* kPa"
"BrakePr  1:* kPa 2:* kPa"
"Alternat 1:* 2:* 3:* 4:*"
"DateTime *"
"AmbTemp  * degr" */
void CPluginCANGine::parseToMessage ()
{
    QStringList list = m_message.split('\n');

    if (2 < list.count())
    {
        QStringList list_engspeed = list[2].split(QRegExp("\\s+"));
        if (1 < list_engspeed.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGSPEED"  , list_engspeed[1]);
        }
    }

    if (3 < list.count())
    {
        QStringList list_accel = list[3].split(QRegExp("\\s+"));
        if (1 < list_accel.count() )
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ACCEL"     , list_accel[1]);
        }
    }

    if (4 < list.count())
    {
        QStringList list_tco = list[4].split(QRegExp("\\s+"));
        if (1 < list_tco.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO"       , list_tco[1]);
        }

        if (3 < list_tco.count())
        {
            QStringList list_tco_md = list_tco[3].split(":");
            if (1 < list_tco_md.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_MD"    , list_tco_md [1]);
            }
        }

        if (4 < list_tco.count())
        {
            QStringList list_tco_os =  list_tco[4].split(":");
            if (1 < list_tco_os.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_OS"    ,list_tco_os[1]);
            }
        }

        if (5 < list_tco.count())
        {
            QStringList list_tco_di = list_tco[5].split(":");
            if (1 < list_tco_di.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_DI"    , list_tco_di[1]);
            }
        }

        if (6 < list_tco.count())
        {
            QStringList list_tco_tp = list_tco[6].split(":");
            if (1 < list_tco_tp.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_TP"    , list_tco_tp[1]);
            }
        }

        if (7 < list_tco.count())
        {
            QStringList list_tco_hi =  list_tco[7].split(":");
            if (1 < list_tco_hi.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_HI"    ,list_tco_hi[1]);
            }
        }

        if (8 < list_tco.count())
        {
            QStringList list_tco_ev =   list_tco[8].split(":");
            if (1 < list_tco_ev.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_EV"    , list_tco_ev[1]);
            }
        }

        if (9 < list_tco.count())
        {
            QStringList list_tch_d1 =  list_tco[9].split(":");
            if (1 < list_tch_d1.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_D1"    , list_tch_d1[1]);
            }
        }

        if (10 < list_tco.count())
        {
            QStringList list_tch_d2 =  list_tco[10].split(":");
            if (1 < list_tch_d2.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_TCO_D2"    , list_tch_d2[1]);
            }
        }
    }

    if (5 < list.count())
    {
        QStringList list_speed = list[5].split(QRegExp("\\s+"));
        if (1 < list_speed.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED"     , list_speed[1]);
        }

        if (3 < list_speed.count())
        {
            QStringList list_speed_cc = list_speed[3].split(":");
            if (1 < list_speed_cc.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_CC"  , list_speed_cc[1]);
            }
        }

        if (4 < list_speed.count())
        {
            QStringList list_speed_br = list_speed[4].split(":");
            if (1 < list_speed_br.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_BR"  , list_speed_br[1]);
            }
        }

        if (5 < list_speed.count())
        {
            QStringList list_speed_cs = list_speed[5].split(":");
            if (1 < list_speed_cs.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_CS"  , list_speed_cs[1]);
            }
        }

        if (6 < list_speed.count())
        {
            QStringList list_speed_pb = list_speed[6].split(":");
            if (1 < list_speed_pb.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_SPEED_PB"  , list_speed_pb[1]);
            }
        }
    }

    if (6 < list.count())
    {
        QStringList list_distance = list[6].split(QRegExp("\\s+"));
        if (1 < list_distance.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DISTANCE"  , list_distance[1]);
        }
    }

    if (7 < list.count())
    {
        QStringList list_enghours = list[7].split(QRegExp("\\s+"));
        if (1 < list_enghours.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGHOURS"  , list_enghours[1]);
        }
    }

    if (8 < list.count())
    {
        QStringList list_fuelc = list[8].split(QRegExp("\\s+"));
        if (1 < list_fuelc.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FUELC"     , list_fuelc[1]);
        }
    }

    if (9 < list.count())
    {
        QStringList list_engtemp = list[9].split(QRegExp("\\s+"));
        if (1 < list_engtemp.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ENGTEMP"   , list_engtemp[1]);
        }
    }

    if (10 < list.count())
    {
        QStringList list_fuellev = list[10].split(QRegExp("\\s+"));
        if (1 < list_fuellev.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FUELLEV"   , list_fuellev[1]);
        }
    }

    if (11 < list.count())
    {
        QStringList list_vehid =  list[11].split(QRegExp("\\s+"));
        if (1 < list_vehid.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_VEHID"     , list_vehid[1]);
        }
    }

    if (12 < list.count())
    {
        QStringList list_fms  =  list[12].split(QRegExp("\\s+"));
        if (1 < list_fms.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS"       , list_fms[1]);
        }

        if (2 < list_fms.count())
        {
            QStringList list_fms_diag = list_fms[2].split(":");
            if (1 < list_fms_diag.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS_DIAG"  , list_fms_diag[1]);
            }
        }

        if (3 < list_fms.count())
        {
            QStringList list_fms_requ = list_fms[3].split(":");
            if (1 < list_fms_requ.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_FMS_REQU"  , list_fms_requ[1]);
            }
        }
    }


    if (13 < list.count())
    {
        QStringList list_gear = list[13].split(QRegExp("\\s+"));
        if (1 < list_gear.count())
        {
            QStringList list_gear_s = list_gear[1].split(":");
            if (1 < list_gear_s.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_GEAR_S"    , list_gear_s[1]);
            }
        }

        if (2 < list_gear.count())
        {
            QStringList list_gear_c = list_gear[2].split(":");
            if (1 < list_gear_c.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_GEAR_C"    , list_gear_c[1]);
            }
        }
    }

    if (14 < list.count())
    {
        QStringList list_doorctrl = list[14].split(QRegExp("\\s+"));
        if (1 < list_doorctrl.count())
        {
            QStringList list_doorctrl_p =  list_doorctrl[1].split(":");
            if (1 < list_doorctrl_p.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_P",list_doorctrl_p[1]);
            }
        }

        if (2 < list_doorctrl.count())
        {
            QStringList list_doorctrl_r =  list_doorctrl[2].split(":");
            if (1 < list_doorctrl_r.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_R",list_doorctrl_r[1]);
            }
        }

        if (3 < list_doorctrl.count())
        {
            QStringList list_doorctrl_s =  list_doorctrl[3].split(":");
            if (1 < list_doorctrl_s.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DOORCTRL_S",list_doorctrl_s[1]);
            }
        }
    }

    if (15 < list.count())
    {
        QStringList list_dc2 = list[15].split(QRegExp("\\s+"));
        if (1 < list_dc2.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2"           , list_dc2[1]);
        }

        if (2 < list_dc2.count())
        {
            QStringList list_dc2_loe_1 = list_dc2[2].split(":");
            if (1 < list_dc2_loe_1.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_1"     , list_dc2_loe_1[1]);
            }
        }

        if (3 < list_dc2.count())
        {
            QStringList list_dc2_loe_2 = list_dc2[3].split(":");
            if (1 < list_dc2_loe_2.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_2"     , list_dc2_loe_2[1]);
            }
        }

        if (4 < list_dc2.count())
        {
            QStringList list_dc2_loe_3 = list_dc2[4].split(":");
            if (1 < list_dc2_loe_3.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_3"     , list_dc2_loe_3[1]);
            }
        }

        if (5 < list_dc2.count())
        {
            QStringList list_dc2_loe_4 = list_dc2[5].split(":");
            if (1 < list_dc2_loe_4.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_4"     , list_dc2_loe_4[1]);
            }
        }

        if (6 < list_dc2.count())
        {
            QStringList list_dc2_loe_5 =  list_dc2[6].split(":");
            if (1 < list_dc2_loe_5.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_5"     , list_dc2_loe_5[1]);
            }
        }

        if (7 < list_dc2.count())
        {
            QStringList list_dc2_loe_6 =  list_dc2[7].split(":");
            if (1 < list_dc2_loe_6.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_6"     , list_dc2_loe_6[1]);
            }
        }

        if (8 < list_dc2.count())
        {
            QStringList list_dc2_loe_7 = list_dc2[8].split(":");
            if (1 < list_dc2_loe_7.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_7"     , list_dc2_loe_7[1]);
            }
        }

        if (9 < list_dc2.count())
        {
            QStringList list_dc2_loe_8 = list_dc2[9].split(":");
            if (1 < list_dc2_loe_8.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_8"     , list_dc2_loe_8[1]);
            }
        }

        if (10 < list_dc2.count())
        {
            QStringList list_dc2_loe_9 =  list_dc2[10].split(":");
            if (1 < list_dc2_loe_9.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_9"      ,list_dc2_loe_9[1]);
            }
        }

        if (11 < list_dc2.count())
        {
            QStringList list_dc2_loe_10 = list_dc2[11].split(":");
            if (1 < list_dc2_loe_10.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DC2_LOE_10"    , list_dc2_loe_10[1]);
            }
        }
     }

    if (16 < list.count())
    {
        QStringList list_bollowpr = list[16].split(QRegExp("\\s+"));

        if (1 < list_bollowpr.count())
        {
            QStringList list_bellowpr_fal = list_bollowpr[1].split(":");
            if (1 < list_bellowpr_fal.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_FAL"  , list_bellowpr_fal[1]);
            }
        }

        if (3 < list_bollowpr.count())
        {
            QStringList list_bellowpr_far = list_bollowpr[3].split(":");
            if (1 < list_bellowpr_far.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_FAR"  , list_bellowpr_far[1]);
            }
        }

        if (5 < list_bollowpr.count())
        {
            QStringList list_bellowpr_ral = list_bollowpr[5].split(":");
            if (1 < list_bellowpr_ral.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_RAL"  , list_bellowpr_ral[1]);
            }
        }

        if (7 < list_bollowpr.count())
        {
            QStringList list_bellowpr_rar =  list_bollowpr[7].split(":");
            if (1 < list_bellowpr_rar.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BELLOWPR_RAR"  , list_bellowpr_rar[1]);
            }
        }
    }

    if (17 < list.count())
    {
        QStringList list_breakprr = list[17].split(QRegExp("\\s+"));
        if (1 < list_breakprr.count())
        {
            QStringList list_brakepr_1 =  list_breakprr[1].split(":");
            if (1 < list_brakepr_1.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BRAKEPR_1"  , list_brakepr_1[1]);
            }
        }

        if (3 < list_breakprr.count())
        {
            QStringList list_brakepr_2 =  list_breakprr[3].split(":");
            if (1 < list_brakepr_2.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_BRAKEPR_2"  , list_brakepr_2[1]);
            }
        }
    }

    if (18 < list.count())
    {
        QStringList list_alternat = list[18].split(QRegExp("\\s+"));
        if (1 < list_alternat.count())
        {
            QStringList list_alternat_1 = list_alternat[1].split(":");
            if (1 < list_alternat_1.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_1" , list_alternat_1[1]);
            }
        }

        if (2 < list_alternat.count())
        {
            QStringList list_alternat_2 = list_alternat[2].split(":");
            if (1 < list_alternat_2.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_2" , list_alternat_2[1]);
            }
        }

        if (3 < list_alternat.count())
        {
            QStringList list_alternat_3 = list_alternat[3].split(":");
            if (1 < list_alternat_3.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_3" , list_alternat_3[1]);
            }
        }

        if (4 < list_alternat.count())
        {
            QStringList list_alternat_4 = list_alternat[4].split(":");
            if (1 < list_alternat_4.count())
            {
                m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_ALTERNAT_4" , list_alternat_4[1]);
            }
        }
    }

    if (19 < list.count())
    {
        QStringList list_datetime = list[19].split(QRegExp("\\s+"));
        if (1 < list_datetime.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_DATETIME"   , list_datetime[1]);
        }
    }

    if (20 < list.count())
    {
        QStringList list_ambtemp = list[20].split(QRegExp("\\s+"));
        if (1 < list_ambtemp.count())
        {
            m_list_data_plugin[INFORMATIONS_DATA].setValueData("PCAN_AMBTEMP"    , list_ambtemp[1]);
        }
    }

    emit signalUpdateServices ();
}


Q_EXPORT_PLUGIN2(pluginCANGine , CPluginCANGine)

