#ifndef __SERVICE_SEND_DATA_BASE_H__
#define __SERVICE_SEND_DATA_BASE_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class CServiceSendDataBase : public CServiceAbstractObject , public CServiceAbstract
{

    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSendDataBase();

    ~CServiceSendDataBase();

    virtual void init (CListDataService *_list_data_informations);

    virtual QObject *getObject();

    virtual QString getNameService();

    virtual QString getDescriptionService();

    virtual void createWidget();

    virtual void initWidget();

    void updateWidget();

    virtual QWidget * getWidget();

    void start ();

    void createDataFile ();

    void detectTablesAndCreate();

    QNetworkReply * createTablesDataBase(QString _table);

    QNetworkReply * insertDataBase(QString _table , QString _type , QString _value , QString _unit ,  QString _description);

    void stop();

    void save (QDomDocument &_dom_document , QDomElement &_dom_element);

    void load (QDomDocument &_dom_document , QDomElement &_dom_element);

    void addText (QString _text);


public slots :

    virtual void slotUpdate();

    void slotUpdateDataBase();

    void slotFinished(QNetworkReply*);

    void slotError(QNetworkReply::NetworkError _network_error);

signals :

    void signalSendData();

private :

    QWidget     *m_widget;

    QTreeWidget *m_tree_widget;

    QSpinBox    *m_spin_box_interval;

    QLineEdit   *m_line_edit_dir_path_data_base;

    QLineEdit   *m_line_edit_user;

    QLineEdit   *m_line_edit_password;

    QLineEdit   *m_line_edit_data_base;

    QListWidget *m_list_widget_error;

    QNetworkAccessManager *m_network_access_manager;

    QTimer m_timer;

    QList<QNetworkReply *> m_list_network_reply;

    int m_index_service;
};



#endif
