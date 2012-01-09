#include "service_flite.h"


CServiceFliteThread::CServiceFliteThread()
{
    flite_init();

    m_voice=register_cmu_us_kal();

}

void CServiceFliteThread::setListDataService (CListDataService *_list_data_service)
{
    m_list_data_service = _list_data_service;
}

void CServiceFliteThread::setTreeWidget                  (QTreeWidget *_tree_widget)
{
    m_tree_widget = _tree_widget;
}

void CServiceFliteThread::setStop (bool _stop)
{
    m_stop = _stop;
}

void CServiceFliteThread::run()
{
    for (int i=0 ;  i < m_list_data_service->count() && m_stop == false; i++)
    {
        QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

        for (int j=0 ;  j < m_list_data_service->index(i)->count()  && m_stop == false ; j++)
        {
            //Je parcourt les informations
            QTreeWidgetItem *item_informations = item_parent->child(j);

            for (int k = 0 ; k < m_list_data_service->index(i,j).count()  && m_stop == false ; k++)
            {
                CData data = m_list_data_service->index(i,j,k);

                QTreeWidgetItem *item = item_informations->child(k);

                if (item->checkState (0) == Qt::Checked)
                {
                    QString chaine = data.getTypeData()+" "+data.getValueData().toString()+" "+data.getDescription();
                    flite_text_to_speech(chaine.toLatin1(),m_voice,"play");
                }
            }
        }
    }
}

CServiceFlite::CServiceFlite()
{
    m_start = false;
    m_thread = new CServiceFliteThread;
    createWidget ();
}

CServiceFlite::~CServiceFlite()
{
    delete m_thread;
}


void CServiceFlite::init (CListDataService *_list_data_informations)
{
     //Je copie la liste
     m_list_data_service = _list_data_informations;

     initWidget();
}

QObject *CServiceFlite::getObject()
{
    return this;
}

QString CServiceFlite::getNameService()
{
    return "service flite";
}

void CServiceFlite::createWidget ()
{
    m_widget = new QWidget;

    m_tree_widget = new QTreeWidget;
    m_tree_widget->setHeaderLabels(CData::getStringListTitle());

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service permet d'activer une voie synthétique qui lit les données choisies. Si aucune données n'est mise à jour (dans le cas ou rien est branché) la voie ne lit rien. Peut être faudrait t'il mettre un timer pour lire quand même périodiquement les données. A voir. La version de la librairie flite utilisée ne fonctionne qu'à partir de ubuntu 10.10.");
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (m_tree_widget , 0 , 0 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 1 , 0  , 1 , 1);

        grid_layout->addWidget (m_text_edit_description , 2 , 0 , 1 , 1 );

        grid_layout->setRowStretch ( 0 , 80 );

        grid_layout->setRowStretch ( 1 , 5 );

        grid_layout->setRowStretch ( 2 , 15 );

    m_widget->setLayout (grid_layout);
}

void CServiceFlite::initWidget()
{
    m_tree_widget->clear();
    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = new QTreeWidgetItem(QStringList()<<(*(*m_list_data_service)[i])[INFORMATIONS_CONNECTIONS_SETTINGS].getValueData("NAME_PLUGIN").toString());
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

void CServiceFlite::updateWidget()
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


QWidget * CServiceFlite::getWidget()
{
    return m_widget;
}

QString CServiceFlite::getDescriptionService()
{
    return "voix synthétique";
}

//Le start est appelé qu'un seule fois lorsqu'on active le service
void CServiceFlite::start()
{
    m_thread->setStop(false);
    m_start = true;
}

void CServiceFlite::stop()
{
    m_thread->setStop(true);
    m_start = false;
}

void CServiceFlite::save (QDomDocument &_dom_document , QDomElement &_dom_element)
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

    _dom_element.appendChild(dom_element);
}

void CServiceFlite::load (QDomDocument & , QDomElement &_dom_element)
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

//A chaque fois qu'une donnée du plugin est rafraichit mon slot est lancé
void CServiceFlite::slotUpdate()
{
     updateWidget();
     m_thread->setListDataService     (m_list_data_service);
     m_thread->setTreeWidget          (m_tree_widget);
     m_thread->start();
}

Q_EXPORT_PLUGIN2(serviceFlite , CServiceFlite)

