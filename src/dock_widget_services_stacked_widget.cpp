#include "dock_widget_services_stacked_widget.h"

CDockWidgetServicesStackedWidget::CDockWidgetServicesStackedWidget (QList<CServiceAbstract*> *_list_services , QWidget *_parent) : QDockWidget (_parent) , m_list_services(_list_services)
{
    WRITE_ERROR_LOGGER()

    setWindowTitle("Paramètres du service");

    m_stacked_widget_services = new QStackedWidget;

    QWidget *widget = new QWidget;

        QGridLayout * grid_layout = new QGridLayout;

            grid_layout->addWidget (m_stacked_widget_services , 0 , 0 , 1 , 1);

        widget->setLayout (grid_layout);

    grid_layout->setContentsMargins(0 , 0 , 0 , 0);

    setWidget (widget);

    createStackedWidgetServices();
}

CDockWidgetServicesStackedWidget::~CDockWidgetServicesStackedWidget()
{
     WRITE_ERROR_LOGGER()
}

void CDockWidgetServicesStackedWidget::slotUpdateStackedWidgetServices (int _index)
{
     m_stacked_widget_services->setCurrentIndex (_index);
}

void CDockWidgetServicesStackedWidget::createStackedWidgetServices()
{
    WRITE_ERROR_LOGGER()

    for (int i=0 ; i < m_list_services->count() ; i++)
    {
        if ((*m_list_services)[i]->getWidget() != NULL)
        {
            m_stacked_widget_services->addWidget ((*m_list_services)[i]->getWidget());
        }
        else
        {
            m_stacked_widget_services->addWidget (new QLabel("Pas de widget associé au service"));
        }
    }
}
