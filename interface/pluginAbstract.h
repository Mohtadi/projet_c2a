//! \file    pluginAbstract.h
//! \brief   Classe abstraite des plugins.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)


#ifndef  __PLUGIN_ABSTRACT_H__
#define  __PLUGIN_ABSTRACT_H__

#include<QtPlugin>
#include"data_plugins.h"

//! \class CPluginAbstract
//! \brief Classe abstraite qui contient la déclaration des méthodes génériques aux plugins.
class CPluginAbstract
{

public :

    //! \fn  CPluginAbstract
    //! \brief Constructeur
    CPluginAbstract ()                          {}

    //! \fn  ~CPluginAbstract ()
    //! \brief Déstructeur
    virtual ~CPluginAbstract ()                 {}

    //! \fn  QString getNamePlugin()
    //! \brief Renvoi le nom du plugin
    virtual QString getNamePlugin()             = 0;

    //! \fn  QObject *getObject()
    //! \brief Renvoi l'object, ca permet de connecter les signaux
    virtual QObject *getObject()                = 0;

    //! \fn  void setDevice (QString _device)
    //! \brief Affecte le nom du périphérique. Ex : /dev/ttyS0
    virtual void setDevice (QString _device)    = 0;

    //! \fn  bool start()
    //! \brief Lance le plugin, renvoi vrai si le plugin détécte le périphérique associé. La fonction peut être bloquante mais pas plus de quelques seconde. C'est cette fonction qui est apellé pour tester les plugins un à un par le thread.
    virtual bool start()                        = 0;

    //! \fn  bool stop()
    //! \brief Stop le plugin, lors d'une déconnection par exemple
    virtual void stop()                         = 0;

    //! \fn  QWidget *getWidget()
    //! \brief Renvoi le widget associé, pour les plugins série, le widget est cutecom, les autres n'ont pas de widgets. Lorsqu'on enlévera cutecom cette fonction sera peut être inutile, si on a plus besoin de widget.
    virtual QWidget *getWidget()                = 0;

    //! \fn  int getPriority()
    //! \brief Cette variable permet de donner une priorité lorsque deux ou plusieurs plugins sont valide pour dététer un périphérique. Par exemple le plugin gps et serial port sont valide, mais le gps est prioritaire lors de l'assignation du plugin au périphérique.
    virtual int getPriority()                   = 0;

    //! \fn  CListDataPlugin& getListDataPlugin()
    //! \brief Renvoi la liste de données du plugin. C'est pas cette liste que transite toutes les informations et les données.
    CListDataPlugin& getListDataPlugin()   { return m_list_data_plugin; }

    //! \fn  bool isUsed()
    //! \brief Utilisé par l'application pour savoir si le plugin est associé à un périphérique ou pas.
    virtual bool isUsed()                       = 0 ;

    //! \fn  void setUsed  (bool _used)
    //! \brief Utilisé par l'application pour indiquer l'utilisation d'un plugin par un périphérique.
    virtual void setUsed  (bool _used)          = 0 ;

protected:

    //! \fn  void setDataConnectionSettings ()
    //! \brief Initialisation de la liste de données de connections des plugins.
    virtual void setDataConnectionSettings ()  = 0;

    //! \fn  void setDefaultData()
    //! \brief Initialisation de la liste de données des plugins.
    virtual void setDefaultData()              = 0;

    //! \brief Liste qui contient toutes les données du plugin
    CListDataPlugin m_list_data_plugin;
};

Q_DECLARE_INTERFACE (CPluginAbstract , "projet_c2a.CPluginAbstract");

#endif
