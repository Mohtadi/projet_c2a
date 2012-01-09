#include "service_send_bluetooth.h"


CServiceSendBluetooth::CServiceSendBluetooth()
{
    m_start = false;
    m_timer.setSingleShot(false);
    connect (&m_timer , SIGNAL (timeout()) , this , SLOT(slotSendFile()) );

    createWidget ();
}

CServiceSendBluetooth::~CServiceSendBluetooth()
{

}

void CServiceSendBluetooth::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceSendBluetooth::getObject()
{
    return this;
}

QString CServiceSendBluetooth::getNameService()
{
    return "service save file bluetooth";
}


QString CServiceSendBluetooth::getDescriptionService()
{
    return "synchronize le dossier data avec un téléphone via bluetooth";
}
void CServiceSendBluetooth::createWidget ()
{
    m_widget = new QWidget;

    QLabel *label_adresse  = new QLabel ("Addresse mac :");
    m_line_edit_addresse_mac  = new QLineEdit("6c:d6:8a:94:51:c4");

    QLabel *label_dir = new QLabel ("Synchronize le dossier :");
    m_line_edit_dir    = new QLineEdit();
    m_line_edit_dir->setText (WORKING_DIRECTORY);
    m_line_edit_dir->setReadOnly (true);

    QLabel *label_interval = new QLabel ("Rafraichissement en minutes : ");
    m_spin_box_interval = new QSpinBox;
    m_spin_box_interval->setMinimum (1);
    m_spin_box_interval->setMaximum (120);

    QLabel *label_error = new QLabel ("Etat :");
    m_label_error = new QLabel;

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service permet d'envoyer les fichiers du répertoire de travail sur un apareil bluetooth. Le module utilise la librairie blueZ et obexFtp. Le bluetooth ne fonctionne pas sur Ubuntu 11.10. Attention les périphériques doivent êtres apparié sur le système d'expoitation avant. Les test avec un iphone n'ont pas était concluant car l'iphone bloque le bluetooth. Peut être faudrait t'il envoyer les fichiers que si il y a modification du répertoire de travail à voir.");
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (label_adresse               , 0 , 0 , 1 , 1);
        grid_layout->addWidget (m_line_edit_addresse_mac    , 0 , 1 , 1 , 1);

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

void CServiceSendBluetooth::initWidget()
{

}

void CServiceSendBluetooth::updateWidget()
{

}

QWidget * CServiceSendBluetooth::getWidget()
{
    return m_widget;
}

void CServiceSendBluetooth::start ()
{
    slotSendFile ();

    m_timer.setInterval(m_spin_box_interval->value() * 1000*60);
    m_timer.start();
    m_start = true;
}

void CServiceSendBluetooth::stop ()
{
    m_timer.stop();

    CListDataPlugin *list_data_plugin = m_list_data_service->getListDataPlugin(INFORMATIONS_CONNECTIONS_SETTINGS , "NAME_PLUGIN" , "Plugin bluetooth");

    if (list_data_plugin != NULL)
    {
        list_data_plugin->index(INFORMATIONS_DATA).setValueData ("ACTION"            , "");
    }
    m_start = false;
}

void CServiceSendBluetooth::save (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    QDomElement dom_element = _dom_document.createElement ("service");

    dom_element.setAttribute("name" , getNameService());
    dom_element.setAttribute("start", m_start);

    QDomElement sub_dom_element = _dom_document.createElement ("parameters");

    sub_dom_element.setAttribute ("address"     ,m_line_edit_addresse_mac->text());

    sub_dom_element.setAttribute ("interval"    ,m_spin_box_interval->value());

    dom_element.appendChild(sub_dom_element);

    _dom_element.appendChild(dom_element);
}

void CServiceSendBluetooth::load (QDomDocument & , QDomElement &_dom_element)
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
                            if (sub_dom_element.toElement().hasAttribute("address"))
                            {
                                m_line_edit_addresse_mac->setText(sub_dom_element.toElement().attribute("address"));
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


void CServiceSendBluetooth::slotUpdate()
{
}

void CServiceSendBluetooth::slotSendFile ()
{

    CListDataPlugin *list_data_plugin = m_list_data_service->getListDataPlugin(INFORMATIONS_CONNECTIONS_SETTINGS , "NAME_PLUGIN" , "Plugin bluetooth");

    if (list_data_plugin != NULL)
    {
        if (list_data_plugin->index(INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("USED").toBool() == true)
        {
            list_data_plugin->index(INFORMATIONS_DATA).setValueData ("DEVICE_USED"       , m_line_edit_addresse_mac->text());
            list_data_plugin->index(INFORMATIONS_DATA).setValueData ("ACTION"            , "COPY_FILE");

            QDir dir = QDir(WORKING_DIRECTORY);
            QStringList list_file;
            foreach (QString fileName , dir.entryList(QDir::Files))
            {
                list_file.append (dir.absolutePath()+"/"+fileName);
            }

            list_data_plugin->index(INFORMATIONS_DATA).setValueData ("FILES"  , list_file);

        }
        emit signalSendData();
    }
}



Q_EXPORT_PLUGIN2(serviceSendBluetooth , CServiceSendBluetooth)

