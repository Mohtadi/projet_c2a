#include "service_send_ftp.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>


CServiceSendFtp::CServiceSendFtp()
{
    m_start = false;
    m_ftp = NULL;

    m_timer.setSingleShot(false);
    connect (&m_timer , SIGNAL (timeout()) , this , SLOT(slotSendFile()) );

    createWidget ();
}

CServiceSendFtp::~CServiceSendFtp()
{

}

void CServiceSendFtp::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceSendFtp::getObject()
{
    return this;
}

QString CServiceSendFtp::getNameService()
{
    return "service save file ftp";
}


void CServiceSendFtp::createWidget ()
{
    m_widget = new QWidget;

    QLabel *label_serveur  = new QLabel ("Serveur ftp :");
    m_line_edit_serveur_ftp  = new QLineEdit();
    m_line_edit_serveur_ftp->setText ("ftpperso.free.fr");

    QLabel *label_login    = new QLabel ("Login ftp :");
    m_line_edit_login_ftp    = new QLineEdit();
    m_line_edit_login_ftp->setText ("ayaida");

    QLabel *label_passowrd = new QLabel ("Password ftp :");
    m_line_edit_password_ftp = new QLineEdit();
    m_line_edit_password_ftp->setText ("cresticc2a");

    QLabel *label_port = new QLabel("Port :");
    m_line_edit_port = new QLineEdit;
    m_line_edit_port->setText ("21");

    QLabel *label_dir = new QLabel ("Synchronize le dossier :");
    m_line_edit_dir    = new QLineEdit;
    m_line_edit_dir->setText (WORKING_DIRECTORY);
    m_line_edit_dir->setReadOnly (true);

    QLabel *label_interval = new QLabel ("Rafraichissement en secondes : ");
    m_spin_box_interval = new QSpinBox;
    m_spin_box_interval->setMinimum (5);
    m_spin_box_interval->setMaximum (3600);

    QLabel *label_error = new QLabel ("Etat :");
    m_text_edit_error = new QListWidget;

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service permet d'envoyer les fichiers du répertoire de travail sur un serveur ftp. La librairie utilisée est QT. Peut être faudrait t'il envoyer les fichiers que si ils sont modifiés, et pas tout à chaque fois. A voir.");
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (label_serveur               , 0 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_serveur_ftp     , 0 , 1 , 1 , 1);

        grid_layout->addWidget (label_login                 , 1 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_login_ftp       , 1 , 1 , 1 , 1);

        grid_layout->addWidget (label_passowrd              , 2 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_password_ftp    , 2 , 1 , 1 , 1);

        grid_layout->addWidget (label_port                  , 3 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_port            , 3 , 1 , 1 , 1);

        grid_layout->addWidget (label_dir                   , 4 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_dir             , 4 , 1 , 1 , 1);

        grid_layout->addWidget (label_interval              , 5 , 0 , 1 , 1);
        grid_layout->addWidget (m_spin_box_interval         , 5 , 1 , 1 , 1);

        grid_layout->addWidget (label_error                 , 6 , 0 , 1 , 1);
        grid_layout->addWidget (m_text_edit_error           , 6 , 1 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 7 , 0  , 1 , 1);

        grid_layout->addWidget (m_text_edit_description               , 8 , 0. , 1 , 2);

    m_widget->setLayout (grid_layout);
}

void CServiceSendFtp::initWidget()
{

}

void CServiceSendFtp::updateWidget()
{

}

QWidget * CServiceSendFtp::getWidget()
{
    return m_widget;
}

QString CServiceSendFtp::getDescriptionService()
{
    return "synchronize le dossier data avec un serveur ftp via ethernet";
}

void CServiceSendFtp::start ()
{
    if (m_ftp != NULL)
    {
        m_ftp->abort();
        m_ftp->deleteLater();
        m_ftp = 0;
    }
    m_ftp = new QFtp (this);

    connect (m_ftp , SIGNAL (stateChanged(int)) , this , SLOT(slotStateChanged(int)) );
    connect (m_ftp , SIGNAL (commandFinished(int,bool)) , this , SLOT (slotCommandFinished(int,bool)));

    m_ftp->connectToHost(m_line_edit_serveur_ftp->text() , m_line_edit_port->text().toInt());

    m_ftp->login        (m_line_edit_login_ftp->text() , m_line_edit_password_ftp->text());

    m_timer.setInterval(m_spin_box_interval->value() * 1000);
    m_timer.start();
    m_start = true;
    //slotSendFile();
}

void CServiceSendFtp::stop()
{
    m_timer.stop();
    if (m_ftp != NULL)
    {
        m_ftp->close();
    }

    m_start = false;
}

void CServiceSendFtp::save (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    QDomElement dom_element = _dom_document.createElement ("service");

    dom_element.setAttribute("name" , getNameService());
    dom_element.setAttribute("start", m_start);

    QDomElement sub_dom_element = _dom_document.createElement ("parameters");

    sub_dom_element.setAttribute ("serveur"     ,m_line_edit_serveur_ftp->text());

    sub_dom_element.setAttribute ("login"       ,m_line_edit_login_ftp->text());

    sub_dom_element.setAttribute ("password"    ,m_line_edit_password_ftp->text());

    sub_dom_element.setAttribute ("port"        ,m_line_edit_port->text());

    sub_dom_element.setAttribute ("interval"    ,m_spin_box_interval->value());

    dom_element.appendChild(sub_dom_element);

    _dom_element.appendChild(dom_element);
}

void CServiceSendFtp::load (QDomDocument & , QDomElement &_dom_element)
{
    QDomNode dom_element = _dom_element.toElement().firstChild();

    while (!dom_element.isNull())
    {
        if (dom_element.toElement().tagName() == "service")
        {
            if (dom_element.toElement().hasAttribute ("name"))
            {
                if (dom_element.toElement().attribute ("name") == getNameService())
                {
                    if (dom_element.toElement().hasAttribute ("start"))
                    {
                        m_start = dom_element.toElement().attribute ("start").toInt();
                    }


                    //Je parcourt tout les checked et je reparcour l'arbre à chaque fois pour cocher les info. Ca permet de gérer si l'arbre possède plus ou moins de plugins.
                    QDomNode sub_dom_element = dom_element.toElement().firstChild();
                    while (!sub_dom_element.isNull())
                    {
                        if (sub_dom_element.toElement().tagName() == "parameters")
                        {
                            if (sub_dom_element.toElement().hasAttribute("serveur"))
                            {
                                m_line_edit_serveur_ftp->setText(sub_dom_element.toElement().attribute("serveur"));
                            }

                            if (sub_dom_element.toElement().hasAttribute("login"))
                            {
                                m_line_edit_login_ftp->setText(sub_dom_element.toElement().attribute("login"));
                            }

                            if (sub_dom_element.toElement().hasAttribute("password"))
                            {
                                m_line_edit_password_ftp->setText(sub_dom_element.toElement().attribute("password"));
                            }

                            if (sub_dom_element.toElement().hasAttribute("port"))
                            {
                                m_line_edit_port->setText(sub_dom_element.toElement().attribute("port"));
                            }

                            if (sub_dom_element.toElement().hasAttribute("interval"))
                            {
                                m_spin_box_interval->setValue(sub_dom_element.toElement().attribute("interval").toInt());
                            }
                        }

                        sub_dom_element = sub_dom_element.nextSibling();
                    }
                }
            }
        }
        dom_element = dom_element.nextSibling();
    }
}


void CServiceSendFtp::slotUpdate()
{

}

void CServiceSendFtp::slotSendFile ()
{ 
    if (m_list_files.count() == 0)
    {
        QDir dir = QDir(m_line_edit_dir->text());

        foreach (QString fileName , dir.entryList(QDir::Files))
        {
           QFile *file = new QFile (WORKING_DIRECTORY+"/"+ fileName);

           if (file->open(QIODevice::ReadOnly) == true)
           {
                m_ftp->put (file , fileName );

                m_list_files.append (file);
           }
        }
    }
}

void CServiceSendFtp::slotStateChanged (int)
{
    switch (m_ftp->state())
    {
        case QFtp::Unconnected :
            addText("Pas de connection à l'hôte");
        break;

        case QFtp::HostLookup :
            addText("Recherche de nom d'hôte en cours");
        break;

        case QFtp::Connecting :
            addText("Tentative de connection en cours");
        break;

        case QFtp::Connected :
            addText("Connection à l'hôte établie");
        break;

        case QFtp::LoggedIn :
            addText("Login de l'utilisateur valide");
        break;

        case QFtp::Closing :
            addText("Déconnection");
        break;

        default :
            addText("problème inconnu");
        break;
    }
}

void CServiceSendFtp::slotCommandFinished ( int , bool error )
{
    QString command = "";

    if (error == true)
    {
        command = "error : ";
    }

    switch (m_ftp->currentCommand())
    {
        case QFtp::None	:
            command += "No command is being executed";
         break;

        case QFtp::SetTransferMode :
            command += "set the transfer mode";
        break;

        case QFtp::SetProxy :
            command += "'switch proxying on or off";
        break;

        case QFtp::ConnectToHost :
            command += "connectToHost() is being executed";
        break;

        case QFtp::Login :
            command +="login() is being executed";
        break;

        case QFtp::Close:
            command +="close() is being executed";
        break;

        case QFtp::List:
            command +="list() is being executed";
        break;

        case QFtp::Cd:
           command +=" cd() is being executed";
        break;

        case QFtp::Get:
            command +="get() is being executed";
        break;

        case QFtp::Put:

            m_list_files[0]->close();

            delete m_list_files.takeAt(0);

            command +="put() is being executed";

        break;

        case QFtp::Remove:
            command +="remove() is being executed";
        break;

        case QFtp::Mkdir:
            command +="mkdir() is being executed";
        break;

        case QFtp::Rmdir:
            command +="rmdir() is being executed";
        break;

        case QFtp::Rename:
            command +="rename() is being executed";
        break;

        case QFtp::RawCommand:
            command +="rawCommand() is being executed";
        break;

        default :
        break;
    }
    addText (command);
}

void CServiceSendFtp::addText (QString _text)
{
    m_text_edit_error->addItem (_text);

    if (m_text_edit_error->count() > 7)
    {
        m_text_edit_error->takeItem(0);
    }
}
Q_EXPORT_PLUGIN2(serviceSendFtp , CServiceSendFtp)

