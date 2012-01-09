#ifndef __CENTRAL_WIDGET_H__
#define __CENTRAL_WIDGET_H__

#include"define.h"
#include"device.h"

class CCentralWidget : public QWidget
{
    Q_OBJECT

public :

    CCentralWidget (QList<CDevice*> *_list_device , QWidget *_parent = 0);

public slots :

    void slotUpdateTabWidget();

protected :

private:

    QList<CDevice*> *m_list_device;

    QTabWidget *m_tab_widget;
};

#endif
