#include "central_widget.h"

CCentralWidget::CCentralWidget (QList<CDevice*> *_list_device , QWidget *_parent) : QWidget(_parent) , m_list_device(_list_device)
{
    WRITE_ERROR_LOGGER()
    m_tab_widget = new QTabWidget;

    QGridLayout *grid_layout = new QGridLayout;

        grid_layout->addWidget(m_tab_widget , 0 , 0 , 1 , 1);

    setLayout (grid_layout);
}

void CCentralWidget::slotUpdateTabWidget ()
{
    WRITE_ERROR_LOGGER()
    m_tab_widget->clear();

    for (int i=0 ; i<m_list_device->count() ; i++)
    {
        if ((*m_list_device)[i]->getPlugin() != NULL)
        {
            if ((*m_list_device)[i]->getPlugin()->getWidget() != NULL)
            {
                m_tab_widget->addTab((*m_list_device)[i]->getPlugin()->getWidget() , (*m_list_device)[i]->getPlugin()->getNamePlugin());
            }
        }
    }
}
