#ifndef __SERVICE_SEND_FTP_H__
#define __SERVICE_SEND_FTP_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"


#include<QFtp>

class CServiceSendFtp : public CServiceAbstractObject , public CServiceAbstract
{

    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSendFtp();

    ~CServiceSendFtp();

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

    void addText (QString _text);

    void save (QDomDocument &_dom_document , QDomElement &_dom_element);

    void load (QDomDocument &_dom_document , QDomElement &_dom_element);

public slots :

    virtual void slotUpdate();

    void slotSendFile ();

    void slotStateChanged (int);

    void slotCommandFinished (int id, bool error);

signals :

    void signalSendData();

private :



    QWidget     *m_widget;

    QLineEdit   *m_line_edit_serveur_ftp;
    QLineEdit   *m_line_edit_login_ftp;
    QLineEdit   *m_line_edit_password_ftp;
    QLineEdit   *m_line_edit_port;
    QLineEdit   *m_line_edit_dir;

    QListWidget   *m_text_edit_error;

    QSpinBox    *m_spin_box_interval;
    QFile m_file;

    QFtp * m_ftp;

    QTimer m_timer;
    QList<QFile*> m_list_files;


};



#endif
