//! \file    service_save_file_html.h
//! \brief   Service d'enregistremenr des données dans un fichiers html.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __SERVICE_SAVE_FILE_HTML_H__
#define __SERVICE_SAVE_FILE_HTML_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"


//! \class CServiceSaveFileHtmlThread
//! \brief Thread enregistre les informations cochées dans le treeWidget dans un fichiers, et génére un fichier html.
class CServiceSaveFileHtmlThread : public QThread
{
   public :
    CServiceSaveFileHtmlThread();

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

//! \class CServiceSaveFileHtml
//! \brief Permet de générer un fichier html, si on active le service ftp envoi directement le fichier html sur un serveur. Mais des fois à cause des rafraichissement intempestif et des copie sur le serveur, le fichier html s'affiche mal dans le navigateur, c'est pour ca qu'il y a aussi la possibilité de passer par le service de base de donnée.
class CServiceSaveFileHtml : public CServiceAbstractObject , public CServiceAbstract
{
    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSaveFileHtml();

    ~CServiceSaveFileHtml();

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

    CServiceSaveFileHtmlThread     *m_thread;

    QWidget     *m_widget;

    QTreeWidget *m_tree_widget;
    QLineEdit   *m_line_edit_dir_path;
    QLineEdit   *m_line_edit_file_name;


    QFile m_file;


};



#endif
