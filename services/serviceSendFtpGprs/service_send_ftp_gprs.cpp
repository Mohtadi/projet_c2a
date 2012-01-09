#include "service_send_ftp_gprs.h"


CServiceSendFtpGprsThread::CServiceSendFtpGprsThread()
{
}

void CServiceSendFtpGprsThread::setServeur     (QString _serveur)
{
    m_serveur_ftp = _serveur;
}

void CServiceSendFtpGprsThread::setLogin       (QString _login)
{
    m_login = _login;
}

void CServiceSendFtpGprsThread::setPassword    (QString _password)
{
    m_password = _password;
}

void CServiceSendFtpGprsThread::setDir         (QString _dir)
{
    m_dir = _dir;
}

void CServiceSendFtpGprsThread::setLabelError  (QLabel *_label_error)
{
    m_label_error = _label_error;
}

void CServiceSendFtpGprsThread::run()
{

}

CServiceSendFtpGprs::CServiceSendFtpGprs()
{
    m_start = false;
    m_thread = new CServiceSendFtpGprsThread;


    m_timer.setSingleShot(false);
    connect (&m_timer , SIGNAL (timeout()) , this , SLOT(slotSendFile()) );

    createWidget ();
}

CServiceSendFtpGprs::~CServiceSendFtpGprs()
{

}

void CServiceSendFtpGprs::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceSendFtpGprs::getObject()
{
    return this;
}

QString CServiceSendFtpGprs::getNameService()
{
    return "service save file gprs";
}


void CServiceSendFtpGprs::createWidget ()
{
    m_widget = new QWidget;

    QLabel *label_serveur  = new QLabel ("Serveur ftp :");
    m_line_edit_serveur_ftp  = new QLineEdit();
    m_line_edit_serveur_ftp->setText ("ftpperso.free.fr");

    QLabel *label_login    = new QLabel ("Login ftp :");
    m_line_edit_login_ftp    = new QLineEdit();
    m_line_edit_login_ftp->setText ("theamy");

    QLabel *label_passowrd = new QLabel ("Password ftp :");
    m_line_edit_password_ftp = new QLineEdit();
    m_line_edit_password_ftp->setText ("matrix7");

    QLabel *label_dir = new QLabel ("Synchronize le dossier :");
    m_line_edit_dir    = new QLineEdit();
    m_line_edit_dir->setText (WORKING_DIRECTORY);
    m_line_edit_dir->setReadOnly (true);

    QLabel *label_interval = new QLabel ("Rafraichissement en secondes : ");
    m_spin_box_interval = new QSpinBox;
    m_spin_box_interval->setMinimum (5);
    m_spin_box_interval->setMaximum (3600);

    QLabel *label_error = new QLabel ("Etat :");
    m_label_error = new QLabel;

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service permet d'envoyer les fichiers du répertoire de travail sur un serveur ftp via le gprs. Pour l'instant le gprs est repartit chez le vendeur pour cause de problème.");
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (label_serveur               , 0 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_serveur_ftp     , 0 , 1 , 1 , 1);

        grid_layout->addWidget (label_login                 , 1 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_login_ftp       , 1 , 1 , 1 , 1);

        grid_layout->addWidget (label_passowrd              , 2 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_password_ftp    , 2 , 1 , 1 , 1);

        grid_layout->addWidget (label_dir                   , 3 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_dir             , 3 , 1 , 1 , 1);

        grid_layout->addWidget (label_interval              , 4 , 0 , 1 , 1);
        grid_layout->addWidget (m_spin_box_interval         , 4 , 1 , 1 , 1);

        grid_layout->addWidget (label_error                 , 5 , 0 , 1 , 1);
        grid_layout->addWidget (m_label_error               , 5 , 1 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 6 , 0  , 1 , 1);

        grid_layout->addWidget (m_text_edit_description     , 7 , 0 , 1 , 2);

    m_widget->setLayout (grid_layout);
}

void CServiceSendFtpGprs::initWidget()
{

}

void CServiceSendFtpGprs::updateWidget()
{

}

QWidget * CServiceSendFtpGprs::getWidget()
{
    return m_widget;
}

QString CServiceSendFtpGprs::getDescriptionService()
{
    return "synchronize le dossier data avec un serveur ftp via gprs";
}

void CServiceSendFtpGprs::start ()
{
    /*m_timer.start();*/

    for (int i=0 ; i < m_list_data_service->count() ; i++)
    {
        if (m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("USED").toBool() == true &&
            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("TYPE").toString() == "gprs" )
        {
            QString send_input_text = "AT";

            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT"  , send_input_text);
            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("OUTPUT_TEXT" , "");
            emit signalSendData();
        }
    }
    m_start = true;
}

void CServiceSendFtpGprs::stop()
{
    /*m_timer.stop();*/
    m_start = false;
}


//AT+CGMR renvoi la version
//http://www.roundsolutions.com/forum/thread.php?postid=18895 forum
//http://www.roundsolutions.com/techdocs/index.php#firmwareNew version des firmware

void CServiceSendFtpGprs::slotUpdate()
{
    for (int i=0 ; i < m_list_data_service->count() ; i++)
    {
        if (m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("USED").toBool() == true &&
            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("TYPE").toString() == "gprs" )
        {
            QString input_text  = m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("INPUT_TEXT").toString();
            QString output_text = m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("OUTPUT_TEXT").toString();

            QString send_input_text = "";

            if (input_text == "AT")
            {
                if (output_text == "OK")
                {
                    send_input_text = "AT#SELINT=2";
                    m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                    emit signalSendData();
                }
                else
                {
                    //send_input_text = "AT";
                }
            }
            else
            {
                if (input_text == "AT#SELINT=2")
                {
                    if (output_text == "OK")
                    {
                        send_input_text = "AT#GPRS=1";
                        m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                        emit signalSendData();
                    }
                    else
                    {
                        //send_input_text = "AT";
                    }
                }
                else
                {

                    if (input_text == "AT#GPRS=0")
                    {
                        if (output_text == "OK")
                        {
                            send_input_text = "AT#GPRS=1";
                            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                            emit signalSendData();
                        }
                        else
                        {
                            send_input_text = "AT#GPRS=0";
                            m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                            emit signalSendData();
                        }
                    }
                    else
                    {
                        if (input_text == "AT#GPRS=1")
                        {
                            if (output_text == "IP")
                            {
                                send_input_text = "AT#FTPTO=1000";
                                m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                emit signalSendData();
                            }
                            else
                            {
                                send_input_text = "AT#GPRS=0";
                                m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                emit signalSendData();
                            }
                        }
                        else
                        {
                            if (input_text == "AT#FTPTO=1000")
                            {
                                if (output_text == "OK")
                                {
                                    QString serveur  = "\"" + m_line_edit_serveur_ftp->text() + "\"";
                                    QString login    = "\"" + m_line_edit_login_ftp->text() + "\"";
                                    QString passowrd = "\"" + m_line_edit_password_ftp->text() + "\"";

                                    send_input_text = "AT#FTPOPEN="+serveur+","+login+","+passowrd+",";
                                    m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                    emit signalSendData();
                                }
                                else
                                {
                                    //send_input_text = "AT#FTPTO=1000";
                                    //m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                    //emit signalSendData();
                                }
                            }
                            else
                            {
                                if (input_text.contains ("AT#FTPOPEN=") )
                                {
                                    if (output_text == "OK")
                                    {
                                        send_input_text = "AT#FTPTYPE=0";
                                        m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                        emit signalSendData();
                                    }
                                    else
                                    {
                                        send_input_text = "AT#FTPCLOSE";
                                        m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                        emit signalSendData();
                                    }
                                }
                                if (input_text == "AT#FTPCLOSE")
                                {
                                    if (output_text == "OK")
                                    {
                                        QString serveur  = "\"" + m_line_edit_serveur_ftp->text() + "\"";
                                        QString login    = "\"" + m_line_edit_login_ftp->text() + "\"";
                                        QString passowrd = "\"" + m_line_edit_password_ftp->text() + "\"";

                                        send_input_text = "AT#FTPOPEN="+serveur+","+login+","+passowrd+",";
                                        m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                        emit signalSendData();
                                    }
                                }
                                if (input_text.contains ("AT#FTPTYPE") )
                                {
                                    if (output_text == "OK")
                                    {
                                        QString fileName = "\"fichier.txt\"";
                                        send_input_text = "AT#FTPPUT="+fileName;
                                        m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , send_input_text);
                                        emit signalSendData();
                                    }
                                    else
                                    {

                                    }
                                }
                                else
                                {
                                    if (input_text.contains("AT#FTPPUT="))
                                    {
                                        if (output_text == "CONNECT")
                                        {
                                            m_file.setFileName( QApplication::applicationDirPath()+"/data/fichier.txt");

                                            if (m_file.open(QIODevice::ReadOnly))
                                            {
                                                    qDebug() <<"Le fichier est ouvert";
                                                m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_TEXT" , "");
                                                m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).setValueData("INPUT_DATA" , m_file.readAll());
                                                 emit signalSendData();
                                                 m_file.close();
                                            }
                                        }
                                        else
                                        {

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CServiceSendFtpGprs::slotSendFile ()
{

}


void CServiceSendFtpGprs::slotStateChanged (int)
{

}

Q_EXPORT_PLUGIN2(serviceSendFtpGprs , CServiceSendFtpGprs)

