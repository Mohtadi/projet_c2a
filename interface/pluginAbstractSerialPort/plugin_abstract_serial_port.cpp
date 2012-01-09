#include "plugin_abstract_serial_port.h"

#include <unistd.h>

CPluginAbstractSerialPort::CPluginAbstractSerialPort()
{
    m_cute_com = new CCuteCom(NULL);

}

CPluginAbstractSerialPort::~CPluginAbstractSerialPort()
{
    m_cute_com->disconnectTTY();
    m_cute_com->deleteLater();
}





