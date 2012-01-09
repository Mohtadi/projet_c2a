//! \brief   Classe abstraite des plugins port série.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __PLUGIN_ABSTRACT_SERIAL_PORT_H__
#define __PLUGIN_ABSTRACT_SERIAL_PORT_H__

#include<QtGui>
#include "../pluginAbstract.h"
#include "../pluginAbstractObject.h"
#include "cutecom.h"



//! \class CPluginAbstractSerialPort
//! \brief Classe mère des plugins de port en série, j'utilise une instance de cutecom pour gérer le paramétrage la récéption des données et la transmission des données pour les périphériques en séries. Il faudra otpimiser et allégé le code de cutecom.
class CPluginAbstractSerialPort : public CPluginAbstractObject , public CPluginAbstract
{
Q_OBJECT

public :

    //! \fn  CPluginAbstractSerialPort()
    //! \brief Constructeur.
    CPluginAbstractSerialPort();

    //! \fn  ~CPluginAbstractSerialPort()
    //! \brief Destructeur.
    ~CPluginAbstractSerialPort();

protected :

    CCuteCom *m_cute_com;
};



#endif
