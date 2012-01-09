//! \file    serviceAbstract.h
//! \brief   Classe abstraite des services.
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef  __SERVICE_ABSTRACT_H__
#define  __SERVICE_ABSTRACT_H__

#include<QtPlugin>
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>
#include"data_plugins.h"

//! \class CServiceAbstract
//! \brief Cette classe reprèsente la classe abstraite des services.
class CServiceAbstract
{

public :

    //! \fn CServiceAbstract ()
    //! \brief Constructeur.
    CServiceAbstract ()                          {}

    //! \fn CServiceAbstract ()
    //! \brief Destructeur.
    virtual ~CServiceAbstract ()                 {}

    //! \fn void init (CListDataService  *_list_data_service)
    //! \brief Initialise le service avec la liste de tout les plugins. Une seule liste de service est utilisée dans l'application, et tout les services y ont accés.
    virtual void init (CListDataService  *_list_data_service) = 0;

    //! \fn QObject *getObject()
    //! \brief Renvoi l'object pour la connection des signaux et des slots.
    virtual QObject *getObject()            = 0;

    //! \fn QString getNameService()
    //! \brief Renvoi le nom du service.
    virtual QString getNameService()        = 0;

    //! \fn QString getDescriptionService()
    //! \brief Renvoi une description basique du service.
    virtual QString getDescriptionService() = 0;

    //! \fn void createWidget()
    //! \brief Méthode utilisé pour créer le widget associé au paramètrage du service.
    virtual void createWidget()             = 0;

    //! \fn void initWidget()
    //! \brief Méthode utilisé pour initialiser le widget associé au paramètrage du service.
    virtual void initWidget()               = 0;

    //! \fn QWidget * getWidget()
    //! \brief Renvoi la widget. Chaque service doit avoir un widget de crée.
    virtual QWidget * getWidget()           = 0;

    //! \fn  bool isStart()
    //! \brief Indique si le service est démarré ou pas.
    virtual bool isStart()                  { return m_start;}

    //! \fn  void start ()
    //! \brief Lance le démarrage du service.
    virtual void start ()                   = 0;

    //! \fn  void stop ()
    //! \brief Stop le service.
    virtual void stop()                     = 0;

    //! \fn  CListDataService * getListDataService()
    //! \brief Renvoi la liste de données du service.
    CListDataService * getListDataService()         { return m_list_data_service; }

    //! \fn  virtual void save (QDomDocument &_dom_document , QDomElement &_dom_element) = 0
    //! \brief Fonction d'enregistrement des paramètres pour le fichier projet.
    virtual void save (QDomDocument &_dom_document , QDomElement &_dom_element) = 0;

    //! \fn  virtual void load (QDomDocument &_dom_document , QDomElement &_dom_element) = 0
    //! \brief Fonction de chargement des paramètres pour le fichier projet.
    virtual void load (QDomDocument &_dom_document , QDomElement &_dom_element) = 0;

protected:

    CListDataService *m_list_data_service;

    bool m_start;

};

Q_DECLARE_INTERFACE (CServiceAbstract , "projet_c2a.CServiceAbstract");

#endif
