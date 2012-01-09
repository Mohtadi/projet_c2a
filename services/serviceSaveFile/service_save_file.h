//! \file    service_save_file.h
//! \brief   Service pour enregistrer les données dans un fichiers text. Peut être améliorer le format d'enregistrement.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __SERVICE_SAVE_FILE_H__
#define __SERVICE_SAVE_FILE_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"

//! \class CServiceSaveFileThread
//! \brief Thread enregistre les informations cochées dans le treeWidget dans un fichier.
class CServiceSaveFileThread : public QThread
{
   public :
    CServiceSaveFileThread();

    void setListDataService        (CListDataService *_list_data_service);
    void setTreeWidget                  (QTreeWidget *_tree_widget);
    void setFile (QFile *_file);
    void setStop (bool _stop);

   protected:

       void run();

   private :
    CListDataService *m_list_data_service;
    QTreeWidget *m_tree_widget;
    QFile *m_file;
    bool         m_stop;
};


//! \class CServiceSaveFile
//! \brief Service d'enregistrement des données dans un fichier text, il faut revoir des fois c'est pas très propre dans le fichier (quand il y a plusieur info à la suite). On peut aussi faire le même service mais en enregistrant un fichier xml.
class CServiceSaveFile : public CServiceAbstractObject , public CServiceAbstract
{
    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSaveFile();

    ~CServiceSaveFile();

    virtual void init (CListDataService *_list_data_informations);

    virtual QObject *getObject();

    virtual QString getNameService();

    virtual QString getDescriptionService();

    virtual void createWidget();

    virtual void initWidget();

    void updateWidget();

    virtual QWidget * getWidget();

    void start ();

    void stop();

    void save (QDomDocument &_dom_document , QDomElement &_dom_element);

    void load (QDomDocument &_dom_document , QDomElement &_dom_element);

public slots :

    virtual void slotUpdate();

signals :

    void signalSendData();

private :

    CServiceSaveFileThread     *m_thread;

    QWidget     *m_widget;

    QTreeWidget *m_tree_widget;
    QLineEdit   *m_line_edit_dir_path;
    QLineEdit   *m_line_edit_file_name;


    QFile m_file;
};



#endif
