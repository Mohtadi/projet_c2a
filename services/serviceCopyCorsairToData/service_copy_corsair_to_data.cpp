#include "service_copy_corsair_to_data.h"


CServiceCopyCorsairToDataThread::CServiceCopyCorsairToDataThread()
{
    //Permet de lancer la copie que si le répertoire est modifié.
    /*connect (&m_file_system_watcher , SIGNAL (fileChanged ( const QString &)) ,  this , SLOT (slotFileChanged(const QString &)));
    m_refresh = true;*/
}

void CServiceCopyCorsairToDataThread::setListDataService   (CListDataService *_list_data_service)
{
    m_list_data_service = _list_data_service;
}

void CServiceCopyCorsairToDataThread::setTreeWidget (QTreeWidget *_tree_widget)
{
    m_tree_widget = _tree_widget;
}

void CServiceCopyCorsairToDataThread::setStop (bool _stop)
{
    m_stop = _stop;
}


void  CServiceCopyCorsairToDataThread::slotFileChanged(const QString & )
{
   // m_refresh = true;
}

void CServiceCopyCorsairToDataThread::run()
{
    while (m_stop == false)
    {
        CListDataPlugin *list_data_plugin = m_list_data_service->getListDataPlugin(INFORMATIONS_CONNECTIONS_SETTINGS , "NAME_PLUGIN" , "Plugin CORSAIR");

        if (list_data_plugin != NULL)
        {
            if (list_data_plugin->index(INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("USED").toBool() == true)
            {

                for (int i=0 ; i < list_data_plugin->index(INFORMATIONS_DATA).count() ; i++)
                {
                    QTreeWidgetItem *item = m_tree_widget->topLevelItem(0)->child(0)->child(i);
                    if (item->checkState(0) == Qt::Checked)
                    {

                        if (list_data_plugin->index(INFORMATIONS_DATA,i).getTypeData() == "1_FILE")
                        {
                            m_stop = true;
                            QDir dir = QDir("/media/CORSAIR/");
                            int kk = 0;
                            foreach (QString fileName , dir.entryList(QDir::Files))
                            {
                                if (kk==0)
                                {
                                    QFile file(dir.absolutePath()+"/" + fileName);

                                    if (file.copy(WORKING_DIRECTORY+"/"+ fileName) == false)
                                    {
                                        qDebug()<<"Fichier non copié";
                                    }

                                    m_file_system_watcher.addPath(WORKING_DIRECTORY+"/"+fileName);

                                }
                                kk++;
                            }
                        }

                        if (list_data_plugin->index(INFORMATIONS_DATA,i).getTypeData() == "ALL_FILE")
                        {
                            m_stop = true;
                            QDir dir = QDir("/media/CORSAIR/");
                            foreach (QString fileName , dir.entryList(QDir::Files))
                            {
                                QFile file(dir.absolutePath()+"/" + fileName);

                                if (file.copy(WORKING_DIRECTORY+"/"+fileName) == false)
                                {
                                    qDebug()<<"Fichier non copié";
                                }

                                m_file_system_watcher.addPath(WORKING_DIRECTORY+"/"+fileName);

                            }
                        }

                        if (list_data_plugin->index(INFORMATIONS_DATA,i).getTypeData() == "END_FILE")
                        {
                            m_stop = true;
                            QDir dir = QDir("/media/CORSAIR/");
                            int kk = 0;
                            foreach (QString fileName , dir.entryList(QDir::Files))
                            {
                                if (kk==dir.entryList(QDir::Files).count() - 1)
                                {
                                    QFile file(dir.absolutePath()+"/" + fileName);

                                    if (file.copy(WORKING_DIRECTORY+"/"+fileName) == false)
                                    {
                                        qDebug()<<"Fichier non copié";
                                    }

                                    m_file_system_watcher.addPath(WORKING_DIRECTORY+"/"+fileName);
                                }
                                kk++;
                            }
                        }
                    }
                }
            }
        }

        //Si le thread tourne tout seul en boucle il prend 100% du cpu il faut donc mettre un usleep
        usleep(500);
    }
}


CServiceCopyCorsairToData::CServiceCopyCorsairToData()
{
    m_start = false;
    m_thread = new CServiceCopyCorsairToDataThread;

    createWidget ();
}

CServiceCopyCorsairToData::~CServiceCopyCorsairToData()
{

}

void CServiceCopyCorsairToData::init (CListDataService *_list_data_informations)
{
    m_list_data_service = _list_data_informations;

    initWidget();
}

QObject *CServiceCopyCorsairToData::getObject()
{
    return this;
}

QString CServiceCopyCorsairToData::getNameService()
{
    return "service copy CORSAIR";
}

void CServiceCopyCorsairToData::createWidget ()
{
    m_widget = new QWidget;

    m_tree_widget = new QTreeWidget;
    m_tree_widget->setHeaderLabels(CData::getStringListTitle());

    QLabel *label_dir_path  = new QLabel ("Dans le dossier : " );

    m_line_edit_dir_path = new QLineEdit;
    m_line_edit_dir_path->setText (WORKING_DIRECTORY);
    m_line_edit_dir_path->setReadOnly (true);

    QTextEdit *m_text_edit_description = new QTextEdit;
    m_text_edit_description->setText(("Ce service permet de copier le premier, tout ou le dernier fichier de la clé usb CORSAIR vers le répertoire de travail. L'action à effectuer peut être choisie avant de brancher la tablette ou une fois branchée. Si une modification, une suppression d'un fichier dans le répertoire de travail est faite, il recopie à nouveau les fichiers. Par contre si la tablette reste branché et qu'un fichier est ajouté dessus il ne copie pas le fichier. A voir. Il faudrait faire un plugin générique à l'aide de libusb pour les clés usb Il faudrait copier les fichiers que quand c'est nécessaire."));
    m_text_edit_description->setReadOnly(true);

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget (m_tree_widget           , 0 , 0 , 1 , 2);

        grid_layout->addWidget (label_dir_path          , 1 , 0 , 1 , 1);

        grid_layout->addWidget (m_line_edit_dir_path    , 1 , 1 , 1 , 1);

        grid_layout->addItem (new QSpacerItem (-1 , -1 , QSizePolicy::Expanding ,  QSizePolicy::Expanding) , 2 , 0  , 1 , 1);

        grid_layout->addWidget (m_text_edit_description , 3 , 0 , 1 , 2);

    m_widget->setLayout (grid_layout);
}

void CServiceCopyCorsairToData::initWidget()
{
    m_tree_widget->clear();


    CListDataPlugin *list_data_plugin = m_list_data_service->getListDataPlugin(INFORMATIONS_CONNECTIONS_SETTINGS , "NAME_PLUGIN" , "Plugin CORSAIR");

    if (list_data_plugin != NULL)
    {
        //Je crée l'item parent
        QTreeWidgetItem *item_parent = new QTreeWidgetItem(QStringList()<<list_data_plugin->index(INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("NAME_PLUGIN").toString());
        item_parent->setFont (0, QFont("", 10, QFont::Bold) );

        m_tree_widget->addTopLevelItem(item_parent);

        //Je parcourt les informations de connections
        QTreeWidgetItem *item_informations = new QTreeWidgetItem(QStringList());
        item_parent->addChild (item_informations);
        item_informations->setText (0 , list_data_plugin->getTitle(INFORMATIONS_CONNECTIONS_SETTINGS));
        item_informations->setFont (0, QFont("", 10 , QFont::Normal) );

        for (int i = 0 ; i < list_data_plugin->index(INFORMATIONS_DATA).count() ;i++)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(list_data_plugin->index(INFORMATIONS_DATA,i).getStringList());
            item->setFont (0, QFont("", 8 , QFont::Normal) );
            item->setFont (1, QFont("", 8 , QFont::Normal) );
            item->setFont (2, QFont("", 8 , QFont::Normal) );
            item->setFont (3, QFont("", 8 , QFont::Normal) );
            item->setFlags (item->flags() |Qt::ItemIsUserCheckable);
            item->setCheckState (0 , Qt::Unchecked);
            item_informations->addChild(item);
        }
    }
    m_tree_widget->expandAll ();
    for (int i=0 ; i < m_tree_widget->columnCount() ; i++)
    {
        m_tree_widget->resizeColumnToContents(i) ;
    }
    m_tree_widget->header()->resizeSections (QHeaderView::ResizeToContents);
}

void CServiceCopyCorsairToData::updateWidget()
{
    for (int i=0 ;  i < m_list_data_service->count() ; i++)
    {
        if (m_list_data_service->index(i,INFORMATIONS_CONNECTIONS_SETTINGS).getValueData("NAME_PLUGIN").toString() == "Plugin CORSAIR")
        {

            for (int j = 0 ; j < m_list_data_service->index(i,INFORMATIONS_DATA).count() ; j++)
            {
                QTreeWidgetItem *item = m_tree_widget->topLevelItem(0)->child(0)->child(j);

                QStringList string_list = m_list_data_service->index(i,INFORMATIONS_DATA,j).getStringList();
                for (int l = 0 ; l < string_list.count() ; l++)
                {
                    item->setText (l , string_list[l]);
                }
            }
        }
    }
}

QWidget * CServiceCopyCorsairToData::getWidget()
{
    return m_widget;
}

QString CServiceCopyCorsairToData::getDescriptionService()
{
    return "copie les fichiers de la clé usb corsair vers le répertoire data";
}

void CServiceCopyCorsairToData::start ()
{
    m_thread->setListDataService(m_list_data_service);
    m_thread->setTreeWidget (m_tree_widget);
    m_thread->setStop(false);
    m_thread->start();
    m_start = true;
}

void CServiceCopyCorsairToData::stop()
{
    m_thread->setStop(true);
    m_start = false;
}

void CServiceCopyCorsairToData::save (QDomDocument &_dom_document , QDomElement &_dom_element)
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

void CServiceCopyCorsairToData::load (QDomDocument & , QDomElement &_dom_element)
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

void CServiceCopyCorsairToData::slotUpdate()
{
    updateWidget();
    start();
}


Q_EXPORT_PLUGIN2(serviceCopyCorsairToData , CServiceCopyCorsairToData)

