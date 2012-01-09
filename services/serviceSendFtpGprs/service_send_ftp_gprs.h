#ifndef __SERVICE_SEND_FTP_GPRS_H__
#define __SERVICE_SEND_FTP_GPRS_H__

#include<QtGui>

#include "../../interface/serviceAbstractObject.h"
#include "../../interface/serviceAbstract.h"


#include<QFile>

class CServiceSendFtpGprsThread : public QThread
{
   public :
    CServiceSendFtpGprsThread();

    void setServeur     (QString _serveur);
    void setLogin       (QString _login);
    void setPassword    (QString _password);
    void setDir         (QString _dir);
    void setLabelError  (QLabel *_label_error);

   protected:

       void run();

   private :


    QString m_serveur_ftp;
    QString m_login;
    QString m_password;
    QString m_dir;
    QLabel  *m_label_error;

};



class CServiceSendFtpGprs : public CServiceAbstractObject , public CServiceAbstract
{

    Q_OBJECT
    Q_INTERFACES(CServiceAbstract)

public :

    CServiceSendFtpGprs();

    ~CServiceSendFtpGprs();

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

    void save (QDomDocument &_dom_document , QDomElement &_dom_element) {}

    void load (QDomDocument &_dom_document , QDomElement &_dom_element) {}

public slots :

    virtual void slotUpdate();

    void slotSendFile ();


    void slotStateChanged (int);

signals :

    void signalSendData();

private :


    QWidget     *m_widget;

    QLineEdit   *m_line_edit_serveur_ftp;
    QLineEdit   *m_line_edit_login_ftp;
    QLineEdit   *m_line_edit_password_ftp;

    QLineEdit   *m_line_edit_dir;

    QLabel      *m_label_error;

    QSpinBox    *m_spin_box_interval;
    QFile m_file;



    CServiceSendFtpGprsThread *m_thread;
    QTimer m_timer;




};



#endif
