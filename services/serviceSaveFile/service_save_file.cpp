#include "service_save_file.h"



CServiceSaveFileThread::CServiceSaveFileThread()
{
}

void CServiceSaveFileThread::setListDataService(CListDataService *_list_data_service)
{
    m_list_data_service = _list_data_service;
}

void CServiceSaveFileThread::setTreeWidget                  (QTreeWidget *_tree_widget)
{
    m_tree_widget = _tree_widget;
}

void  CServiceSaveFileThread::setFile (QFile *_file)
{
    m_file = _file;
}

void CServiceSaveFileThread::setStop (bool _stop)
{
    m_stop = _stop;
}

void CServiceSaveFileThread::run()
{
    if (m_file != NULL)
    {
        if (m_file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
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
                            QString chaine = m_list_data_service->index(i,j,k).getStringList().join(" ");

                            QTextStream out (m_file);
                            out<<chaine.toLocal8Bit()<<endl;
                        }
                    }
                }
            }

            m_file->close();
        }
        else
        {
            qDebug()<<"Erreur d'ouverture de fichier";
        }
    }
}


CServiceSaveFile::CServiceSaveFile()
{
    m_start = false;
    m_thread = new CServiceSaveFileThread;
    createWidget ();
}

CServiceSaveFile::~CServiceSaveFile()
{

}

void CServiceSaveFile::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceSaveFile::getObject()
{
    return this;
}

QString CServiceSaveFile::getNameService()
{
    return "service save file";
}


void CServiceSaveFile::createWidget ()
{
    m_widget = new QWidget;

    m_tree_widget = new QTreeWidget;
    m_tree_widget->setHeaderLabels(CData::getStringListTitle());

    QLabel *label_dir_path  = new QLabel ("Dans le dossier : " );

    QLabel *label_file_name = new QLabel ("Nom du fichier :");

    m_line_edit_dir_path = new QLineEdit;
    m_line_edit_dir_path->setText (WORKING_DIRECTORY);
    m_line_edit_dir_path->setReadOnly (true);

    m_line_edit_file_name = new QLineEdit;
    m_line_edit_file_name->setText ("fichier.txt");

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText("Ce service permet d'enregistrer les données périodiquement dans un fichier qui se situe dans le répertoire de travail. Peut être faudrait t'il sauvegarder les données que si il y a mise à jour de celle-ci. A voir.");
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (m_tree_widget           , 0 , 0 , 1 , 2);

        grid_layout->addWidget (label_dir_path          , 1 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_dir_path    , 1 , 1 , 1 , 1);

        grid_layout->addWidget (label_file_name         , 2 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_file_name   , 2 , 1 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 3 , 0  , 1 , 2);

        grid_layout->addWidget (m_text_edit_description   , 4 , 0 , 1 , 2);

        grid_layout->setRowStretch ( 0 , 80 );

        grid_layout->setRowStretch ( 4 , 15 );

    m_widget->setLayout (grid_layout);
}

void CServiceSaveFile::initWidget()
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

void CServiceSaveFile::updateWidget()
{
    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = m_tree_widget->topLevelItem(i);

        for (int j=0 ;  j <  m_list_data_service->index(i)->count() ; j++)
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

QWidget * CServiceSaveFile::getWidget()
{
    return m_widget;
}

QString CServiceSaveFile::getDescriptionService()
{
    return "sauver les données dans un fichier";
}


void CServiceSaveFile::start ()
{
    m_file.setFileName (WORKING_DIRECTORY+"/"+m_line_edit_file_name->text());

    m_thread->setFile                (&m_file);
    m_thread->setListDataService    (m_list_data_service);
    m_thread->setTreeWidget          (m_tree_widget);
    m_start = true;
}

void CServiceSaveFile::stop()
{
    m_thread->setStop(true);
    m_start = false;
}

void CServiceSaveFile::save (QDomDocument &_dom_document , QDomElement &_dom_element)
{
    QDomElement dom_element = _dom_document.createElement ("service");

    dom_element.setAttribute("name" , getNameService());
    dom_element.setAttribute("start", m_start);

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

    sub_dom_element.setAttribute ("filename"      , m_line_edit_file_name->text());

    dom_element.appendChild(sub_dom_element);


    _dom_element.appendChild(dom_element);
}

void CServiceSaveFile::load (QDomDocument & , QDomElement &_dom_element)
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
                            if (sub_dom_element.toElement().hasAttribute("filename"))
                            {
                                m_line_edit_file_name->setText(sub_dom_element.toElement().attribute("filename"));
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

void CServiceSaveFile::slotUpdate()
{
    updateWidget();
    m_thread->setStop(false);
    m_thread->start();

}

Q_EXPORT_PLUGIN2(serviceSaveFile , CServiceSaveFile)

