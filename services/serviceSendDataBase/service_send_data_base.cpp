#include "service_send_data_base.h"

CServiceSendDataBase::CServiceSendDataBase()
{
    m_start = false;
    m_timer.setSingleShot(false);

    connect (&m_timer , SIGNAL (timeout()) , this , SLOT(slotUpdateDataBase()));

    m_network_access_manager = NULL;

    createWidget ();
}

CServiceSendDataBase::~CServiceSendDataBase()
{

}

void CServiceSendDataBase::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceSendDataBase::getObject()
{
    return this;
}

QString CServiceSendDataBase::getNameService()
{
    return "service data base";
}


void CServiceSendDataBase::createWidget ()
{
    m_widget = new QWidget;

    m_tree_widget = new QTreeWidget;
    m_tree_widget->setHeaderLabels(CData::getStringListTitle());

    QLabel *label_interval = new QLabel ("Intervalle de rafraichissement en secondes :");
    m_spin_box_interval = new QSpinBox;
    m_spin_box_interval->setMinimum (5);
    m_spin_box_interval->setMaximum (7200);

    QLabel *label_dir_path_data_base  = new QLabel ("Adresse : " );

    m_line_edit_dir_path_data_base = new QLineEdit;
    m_line_edit_dir_path_data_base->setText ("ayaida@sql.free.fr");

    QLabel * label_user = new QLabel ("Utilisateur : " );

    m_line_edit_user = new QLineEdit;
    m_line_edit_user->setText ("ayaida");

    QLabel * label_password = new QLabel ("Mot de passe : " );

    m_line_edit_password = new QLineEdit;
    m_line_edit_password->setText ("cresticc2a");

    QLabel * label_data_base = new QLabel ("Base de donnée : " );

    m_line_edit_data_base = new QLineEdit;
    m_line_edit_data_base->setText ("ayaida");

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service crée les tables associées à chaque info activées. Des fois une erreure QSocketNotifier: Invalid socket s'affiche dans la console, je ne sais pas d'ou ca viens, quand on recompile tout ca marche mieux :/, ou en dehors de qtCreator ca a l'air de marcher mieux. J'ai essayé sur 11.10 je ne l'ai pas eu. Dans le répertoire du service il y a un dossier site ou il y a les fichiers php. Il faut placer ces fichiers sur le serveur sinon le service ne peut pas fonctionner.La fonction createDataFile permet de générer un fichier php avec les paramètres, il faudrait envoyer sur le ftp de manière automatique.");
    m_text_edit_description->setReadOnly(true);

    QLabel *label_error = new QLabel ("Etat : ");
    m_list_widget_error = new QListWidget;

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (m_tree_widget                       , 0 , 0 , 1 , 2);

        grid_layout->addWidget (label_interval                      , 1 , 0 , 1 , 1);

        grid_layout->addWidget (m_spin_box_interval                 , 1 , 1 , 1 , 1);

        grid_layout->addWidget (label_dir_path_data_base            , 2 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_dir_path_data_base      , 2 , 1 , 1 , 1);

        grid_layout->addWidget (label_user                          , 3 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_user                    , 3, 1 , 1 , 1);

        grid_layout->addWidget (label_password                      , 4 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_password                , 4 , 1 , 1 , 1);

        grid_layout->addWidget (label_data_base                     , 5 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_data_base               , 5 , 1 , 1 , 1);

        grid_layout->addWidget (label_error                         , 6 , 0 , 1 , 1);

        grid_layout->addWidget (m_list_widget_error                 , 6 , 1 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 7 , 0  , 1 , 1);

        grid_layout->addWidget (m_text_edit_description , 8 , 0 , 1 , 2);

        grid_layout->setRowStretch ( 0 , 80 );

        grid_layout->setRowStretch ( 6 , 10 );

        grid_layout->setRowStretch ( 8 , 10 );

    m_widget->setLayout (grid_layout);
}

void CServiceSendDataBase::initWidget()
{
    m_tree_widget->clear();

    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = new QTreeWidgetItem(QStringList()<<m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("NAME_PLUGIN").toString());
        item_parent->setFont (0, QFont("", 10, QFont::Bold) );

        m_tree_widget->addTopLevelItem(item_parent);

        for (int j=0 ;  j < m_list_data_service->index(i)->count() ; j++)
        {
            //Je parcourt les informations de connections
            QTreeWidgetItem *item_informations = new QTreeWidgetItem(QStringList());
            item_parent->addChild (item_informations);

            item_informations->setText (0 ,  m_list_data_service->index(i)->getTitle(j));
            item_informations->setFont (0, QFont("", 10 , QFont::Normal) );

            for (int k = 0 ; k < m_list_data_service->index(i,j).count() ;k++)
            {
                QTreeWidgetItem *item = new QTreeWidgetItem(m_list_data_service->index(i,j,k).getStringList());
                item->setFont (0, QFont("", 8 , QFont::Normal) );
                item->setFont (1, QFont("", 8 , QFont::Normal) );
                item->setFont (2, QFont("", 8 , QFont::Normal) );
                item->setFlags (item->flags() |Qt::ItemIsUserCheckable);
                item->setCheckState (0 , Qt::Unchecked);
                item_informations->addChild(item);
            }
        }
    }
    m_tree_widget->expandAll ();
    for (int i=0 ; i < m_tree_widget->columnCount() ; i++)
    {
        m_tree_widget->resizeColumnToContents(i) ;
    }
    m_tree_widget->header()->resizeSections (QHeaderView::ResizeToContents);
}

void CServiceSendDataBase::updateWidget()
{
    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

        for (int j=0 ;  j < m_list_data_service->index(i)->count() ; j++)
        {
            //Je parcourt les informations
            QTreeWidgetItem *item_informations = item_parent->child(j);

            for (int k = 0 ; k < m_list_data_service->index(i,j).count() ; k++)
            {
                QTreeWidgetItem *item = item_informations->child(k);

                QStringList string_list = m_list_data_service->index(i,j,k).getStringList();
                for (int l = 0 ; l < string_list.count() ; l++)
                {
                    item->setText (l , string_list[l]);
                }
            }
        }
    }
}

QWidget * CServiceSendDataBase::getWidget()
{
    return m_widget;
}

QString CServiceSendDataBase::getDescriptionService()
{
    return "envoi les données sur une base de donnée";
}

void CServiceSendDataBase::start ()
{
    m_list_network_reply.clear();

    if (m_network_access_manager != NULL)
    {
        delete m_network_access_manager;
    }

    m_network_access_manager =  new QNetworkAccessManager();
    connect (m_network_access_manager , SIGNAL (finished(QNetworkReply*)) , this , SLOT (slotFinished(QNetworkReply*)));

    //createDataFile();
    detectTablesAndCreate();

    m_timer.setInterval(m_spin_box_interval->value() * 1000);
    m_timer.start();

    m_start = true;
}

//Creation du fichier data.php qui contient les paramètrees de connections
void CServiceSendDataBase::createDataFile ()
{
    //Pour l'instant je n'utilise pas cette fonction
    //C'est paut être pas une bonne idée de créer le fichier dans le répertoire de travail.
    QFile file (WORKING_DIRECTORY+"/"+"data.php");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out (&file);

        QString chaine = QString("<?php\n")+
                         QString("$host = ")+"'"+m_line_edit_dir_path_data_base->text()+"';\n"+
                         QString("$user = ")+"'"+m_line_edit_user->text()+"';\n"+
                         QString("$pass = ")+"'"+m_line_edit_password->text()+"';\n"+
                         QString("$bdd = " )+"'"+m_line_edit_data_base->text()+"';\n"+
                         QString("?>");

        out<<chaine.toLocal8Bit()<<endl;
    }
    else
    {
        qDebug()<<"Erreur de crétion de fichier de data.php";
    }
    file.close();
}

//Détecte les cases cochées pour savoir quelle table recrée, supprime toutes les tables dans la base de données, puis crée les nouvelles
void CServiceSendDataBase::detectTablesAndCreate()
{
    QString list_tables = "";
    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        QString id = m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("ID").toString();

        bool exist_child_checked = false;

        for (int j = 0 ; j < m_list_data_service->index(i)->count()  && exist_child_checked==false ; j++)
        {
            for (int k = 0 ; k < m_list_data_service->index(i,j).count() && exist_child_checked==false ;k++)
            {
                QTreeWidgetItem *item = m_tree_widget->topLevelItem(i)->child(j)->child(k);
                if (item->checkState(0) == Qt::Checked)
                {
                    exist_child_checked = true;
                }
            }
        }
        if (exist_child_checked == true)
        {

            list_tables += id+"-";
        }
    }

    //Suppression du dernier -
    list_tables.remove (list_tables.count() - 1 , 1);

    QNetworkReply *reply = createTablesDataBase(list_tables);

    m_list_network_reply.append (reply);
}

QNetworkReply * CServiceSendDataBase::createTablesDataBase(QString _table)
{
    addText ("Création des tables");

    QUrl params;

    params.addQueryItem("action","CREATE_TABLE");
    params.addQueryItem("table",_table);

    QNetworkReply *reply = m_network_access_manager->post(QNetworkRequest(QUrl("http://ayaida.free.fr/utils.php")), params.encodedQuery());

    connect (reply , SIGNAL (error (QNetworkReply::NetworkError)) , this , SLOT (slotError(QNetworkReply::NetworkError)));

    return reply;
}

QNetworkReply * CServiceSendDataBase::insertDataBase(QString _table , QString _type , QString _value , QString _unit , QString _description)
{
    addText ("Mise à jour des données");

    QUrl params;

    params.addQueryItem("action","INSERT");
    params.addQueryItem("table" ,_table);
    params.addQueryItem("type"  ,_type);
    params.addQueryItem("value" ,_value);
    params.addQueryItem("unit"  ,_unit);
    params.addQueryItem("description",_description);

    QNetworkReply *reply = m_network_access_manager->post(QNetworkRequest(QUrl("http://ayaida.free.fr/utils.php")), params.encodedQuery());

    connect (reply , SIGNAL (error (QNetworkReply::NetworkError)) , this , SLOT (slotError(QNetworkReply::NetworkError)));

    return reply;
}


void CServiceSendDataBase::stop()
{
    m_timer.stop();
    m_start = false;
}


void CServiceSendDataBase::save (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    QDomElement dom_element = _dom_document.createElement ("service");

    dom_element.setAttribute("name" , getNameService());
    dom_element.setAttribute("start" , m_start);

    for (int i=0 ; i < m_tree_widget->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

        for (int j=0 ; j < item_parent->childCount() ; j++)
        {
            QTreeWidgetItem *item_sub_parent = item_parent->child(j);

            for (int k=0 ; k < item_sub_parent->childCount() ; k++)
            {
                QTreeWidgetItem *item = item_sub_parent->child(k);

                if (item->checkState(0) == Qt::Checked)
                {
                    QString plugin      = item_parent->text(0);
                    QString information = item_sub_parent->text(0);
                    QString type        = item->text(0);

                    QDomElement sub_dom_element = _dom_document.createElement ("checked");

                    sub_dom_element.setAttribute ("plugin"      , plugin);
                    sub_dom_element.setAttribute ("information" ,information);
                    sub_dom_element.setAttribute ("type"        ,type);

                    dom_element.appendChild(sub_dom_element);
                }
            }
        }
    }

    QDomElement sub_dom_element = _dom_document.createElement ("parameters");

    sub_dom_element.setAttribute ("interval"   , m_spin_box_interval->value());
    sub_dom_element.setAttribute ("address"    , m_line_edit_dir_path_data_base->text());
    sub_dom_element.setAttribute ("user"       , m_line_edit_user->text());
    sub_dom_element.setAttribute ("password"   , m_line_edit_password->text());
    sub_dom_element.setAttribute ("database"   , m_line_edit_data_base->text());

    dom_element.appendChild(sub_dom_element);

    _dom_element.appendChild(dom_element);
}

void CServiceSendDataBase::load (QDomDocument & , QDomElement &_dom_element)
{
    //Je réinitialise l'arbre en décochant tout
    for (int i=0 ; i < m_tree_widget->topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

        for (int j=0 ; j < item_parent->childCount() ; j++)
        {
            QTreeWidgetItem *item_sub_parent = item_parent->child(j);

            for (int k=0 ; k < item_sub_parent->childCount() ; k++)
            {
                QTreeWidgetItem *item = item_sub_parent->child(k);

                item->setCheckState(0 , Qt::Unchecked);
            }
        }
    }


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
                            if (sub_dom_element.toElement().hasAttribute("interval"))
                            {
                                m_spin_box_interval->setValue(sub_dom_element.toElement().attribute("interval").toInt());
                            }
                            if (sub_dom_element.toElement().hasAttribute("address"))
                            {
                                m_line_edit_dir_path_data_base->setText(sub_dom_element.toElement().attribute("address"));
                            }
                            if (sub_dom_element.toElement().hasAttribute("user"))
                            {
                                m_line_edit_user->setText(sub_dom_element.toElement().attribute("user"));
                            }
                            if (sub_dom_element.toElement().hasAttribute("password"))
                            {
                                m_line_edit_password->setText(sub_dom_element.toElement().attribute("password"));
                            }
                            if (sub_dom_element.toElement().hasAttribute("database"))
                            {
                                m_line_edit_data_base->setText(sub_dom_element.toElement().attribute("database"));
                            }
                        }


                        if (sub_dom_element.toElement().tagName() == "checked")
                        {
                            QString plugin = "";
                            QString information = "";
                            QString type = "";

                            if (sub_dom_element.toElement().hasAttribute("plugin"))
                            {
                                plugin = sub_dom_element.toElement().attribute("plugin");
                            }

                            if (sub_dom_element.toElement().hasAttribute("information"))
                            {
                                information = sub_dom_element.toElement().attribute("information");
                            }

                            if (sub_dom_element.toElement().hasAttribute("type"))
                            {
                                type = sub_dom_element.toElement().attribute("type");
                            }

                            if (plugin != "" && information != "" && type != "")
                            {

                                bool is_find = false;
                                //Je parcourt tout l'arbre
                                for (int i=0 ; i < m_tree_widget->topLevelItemCount() && is_find == false ; i++)
                                {
                                    QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

                                    for (int j=0 ; j < item_parent->childCount()  && is_find == false ; j++)
                                    {
                                        QTreeWidgetItem *item_sub_parent = item_parent->child(j);

                                        for (int k=0 ; k < item_sub_parent->childCount()  && is_find == false; k++)
                                        {
                                            QTreeWidgetItem *item = item_sub_parent->child(k);

                                            QString plugin_aux      = item_parent->text(0);
                                            QString information_aux = item_sub_parent->text(0);
                                            QString type_aux        = item->text(0);

                                            if (plugin_aux == plugin && information_aux == information && type_aux == type)
                                            {
                                                item->setCheckState(0 , Qt::Checked);
                                                is_find = true;
                                            }
                                        }
                                    }
                                }
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

void CServiceSendDataBase::addText (QString _text)
{
    m_list_widget_error->addItem (_text);

    if (m_list_widget_error->count() > 7)
    {
        m_list_widget_error->takeItem(0);
    }
}

void CServiceSendDataBase::slotUpdate()
{
    updateWidget();
}

void CServiceSendDataBase::slotUpdateDataBase()
{
    if (m_list_network_reply.isEmpty() == true)
    {
        if (m_index_service > m_list_data_service->count() -1)
        {
            m_index_service = 0;
        }

        bool refresh = false;

        while (m_index_service<m_list_data_service->count() && refresh == false)
        {
            int i = m_index_service;
            QString id = m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("ID").toString();
            QString list_type        = "";
            QString list_value       = "";
            QString list_unit        = "";
            QString list_description = "";

            for (int j = 0 ; j < m_list_data_service->index(i)->count() ; j++)
            {
                for (int k = 0 ; k < m_list_data_service->index(i,j).count() ;k++)
                {
                    QString type        =  m_list_data_service->index(i,j,k).getTypeData();
                    QString value       =  m_list_data_service->index(i,j,k).getValueData().toString();
                    QString unit        =  m_list_data_service->index(i,j,k).getUnitData();
                    QString description =  m_list_data_service->index(i,j,k).getDescription();

                    QTreeWidgetItem *item = m_tree_widget->topLevelItem(i)->child(j)->child(k);
                    if (item->checkState(0) == Qt::Checked)
                    {
                        list_type        += type + "-";
                        list_value       += value + "-";
                        list_unit        += unit+"-";
                        list_description += description + "-";
                    }
                }
            }

            if (list_type !="" && list_value !="" && list_unit !="" && list_description !="")
            {
                list_type.remove        (list_type.count() - 1 , 1);
                list_value.remove       (list_value.count() - 1 , 1);
                list_unit.remove        (list_unit.count() - 1 , 1);
                list_description.remove (list_description.count() - 1 , 1);
                refresh = true;
                QNetworkReply *reply = insertDataBase(id , list_type ,list_value, list_unit ,list_description);

                m_list_network_reply.append (reply);
            }

            m_index_service++;
        }
    }
}

void CServiceSendDataBase::slotFinished(QNetworkReply* _reply)
{
    if (m_list_network_reply.contains(_reply) == true)
    {
        m_list_network_reply.takeAt(m_list_network_reply.indexOf(_reply));
    }

    addText ("finished");

    _reply->reset();

    _reply->deleteLater();
    _reply = NULL;
}

void CServiceSendDataBase::slotError(QNetworkReply::NetworkError _network_error)
{
    QString error= "";
    switch (_network_error)
    {
        case QNetworkReply::NoError :
            error = "no error condition. Note: When the HTTP protocol returns a redirect no error will be reported. You can check if there is a redirect with the QNetworkRequest::RedirectionTargetAttribute attribute.";
        break;

        case QNetworkReply::ConnectionRefusedError :
            error = "the remote server refused the connection (the server is not accepting requests)";
        break;

        case QNetworkReply::RemoteHostClosedError :
            error = "the remote server closed the connection prematurely, before the entire reply was received and processed";
        break;

        case QNetworkReply::HostNotFoundError :
            error = "the remote host name was not found (invalid hostname)";
        break;

        case QNetworkReply::TimeoutError :
            error = "the connection to the remote server timed out";
        break;

        case QNetworkReply::OperationCanceledError :
            error = "the operation was canceled via calls to abort() or close() before it was finished.";
        break;

        case QNetworkReply::SslHandshakeFailedError:
            error = "the SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted.";
        break;

        case QNetworkReply::TemporaryNetworkFailureError:
            error = "the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established.";
        break;

        case QNetworkReply::ProxyConnectionRefusedError:
            error = "the connection to the proxy server was refused (the proxy server is not accepting requests)";
        break;

        case QNetworkReply::ProxyConnectionClosedError:
            error = "the proxy server closed the connection prematurely, before the entire reply was received and processed";
        break;

        case QNetworkReply::ProxyNotFoundError:
            error = "the proxy host name was not found (invalid proxy hostname)";
        break;

        case QNetworkReply::ProxyTimeoutError:
            error = "the connection to the proxy timed out or the proxy did not reply in time to the request sent";
        break;

        case QNetworkReply::ProxyAuthenticationRequiredError :
            error = "the proxy requires authentication in order to honour the request but did not accept any credentials offered (if any)";
        break;

        case QNetworkReply::ContentAccessDenied	:
            error = "the access to the remote content was denied (similar to HTTP error 401)";
        break;

        case QNetworkReply::ContentOperationNotPermittedError :
            error = "the operation requested on the remote content is not permitted";
        break;

        case QNetworkReply::ContentNotFoundError:
            error = "the remote content was not found at the server (similar to HTTP error 404)";
        break;

        case QNetworkReply::AuthenticationRequiredError:
            error = "the remote server requires authentication to serve the content but the credentials provided were not accepted (if any)";
        break;

        case QNetworkReply::ContentReSendError:
            error = "the request needed to be sent again, but this failed for example because the upload data could not be read a second time.";
        break;

        case QNetworkReply::ProtocolUnknownError:
            error = "the Network Access API cannot honor the request because the protocol is not known";
        break;

        case QNetworkReply::ProtocolInvalidOperationError :
            error = "the requested operation is invalid for this protocol";
        break;

        case QNetworkReply::UnknownNetworkError :
            error = "an unknown network-related error was detected";
        break;

        case QNetworkReply::UnknownProxyError :
            error = "an unknown proxy-related error was detected";
        break;

        case QNetworkReply::UnknownContentError :
            error = "an unknown error related to the remote content was detected";
        break;

        case QNetworkReply::ProtocolFailure :
            error = "a breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)";
        break;

        default :
        break;
     }

    addText (error);
}


Q_EXPORT_PLUGIN2(serviceSendDataBase , CServiceSendDataBase)

