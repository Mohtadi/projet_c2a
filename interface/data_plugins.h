//! \brief   Classe de données
//! \author  Fabien Bradmetz
//! \version 1.00
//! \date    13 Décembre 2011 : création (Fabien Bradmetz)

#ifndef __DATA_PLUGINS_H__
#define __DATA_PLUGINS_H__

#include<QVariant>

//! \brief Répertoire de travail de l'application, c'est ici que je copi les fichiers . . .
#define WORKING_DIRECTORY QApplication::applicationDirPath()+"/data"

#define UNIT_NONE ""


#define DESCRIPTION_NAME_PLUGIN         "nom du plugin"
#define DESCRIPTION_TYPE                "type de périphérique"
#define DESCRIPTION_ID                  "identifiant unique à chaque plugin, ne pas mettre d'espace utilisé pour cré les tables de  la base de données"
#define DESCRIPTION_USED                "périphérique utilisé"
#define DESCRIPTION_DEVICE              "port du périphérique"

#define DESCRIPTION_BAUD_RATE           "vitesse de connexion"
#define DESCRIPTION_DATA_BITS           "nombre de bits pour un caractère de donnée"
#define DESCRIPTION_STOP_BITS           "bit qui indique la fin d'une communication"
#define DESCRIPTION_PARITY              "type de parité du signal None, Odd, Even, Mark ou Space"
#define DESCRIPTION_HANDSHAKE_SOFTWARE  "contrôle de flux logiciel"
#define DESCRIPTION_HANDCHAKE_HARDWARE  "contrôle de flux matériel"
#define DESCRIPTION_READING             "mode lecture"
#define DESCRIPTION_WRITING             "mode écriture"

//! \class CData
//! \brief Conteneur pour les données
class CData
{
public :

    //! \fn  CData (QString _type_data , QVariant _value_data , QString _unit_data = "" , QString _description = "")
    //! \brief Constructeur
    CData (QString _type_data , QVariant _value_data , QString _unit_data = "" , QString _description = "") :
        m_type_data   (_type_data) ,
        m_value_data  (_value_data) ,
        m_unit_data   (_unit_data) ,
        m_description (_description)
    {
    }

    //! \fn  ~CData()
    //! \brief Constructeur
    ~CData()
    {
    }

    //! \fn  void setTypeData    (QString _type_data)
    //! \brief Affecte le type de donnée, ce champs représente l'identificateur de la variable lorsque elle est utilisée dans les services
    void setTypeData    (QString _type_data)         { m_type_data = _type_data; }

    //! \fn  void setValueData   (QVariant _value_data)
    //! \brief Affecte la valeure de la donnée. Le type QVariant est un type générique à QT. Il est possible de mettre beaucoup de types différents.
    void setValueData   (QVariant _value_data)       { m_value_data = _value_data; }

    //! \fn  void setUnitData   (QString _unit_data)
    //! \brief Affecte l'unité à la donnée
    void setUnitData   (QString _unit_data)       { m_unit_data = _unit_data; }

    //! \fn  void setDescription (QString  _description)
    //! \brief Description de la donnée. Permet de fournir une description précise du champs.
    void setDescription (QString  _description)      { m_description = _description; }

    //! \fn   QString  getTypeData()
    //! \brief Renvoi le type de la donnée.
    QString  getTypeData()               { return m_type_data;}

    //! \fn  QVariant getValueData()
    //! \brief Renvoi la valeure de la donnée.
    QVariant getValueData()              { return m_value_data;}

    //! \fn  QString getUnitData()
    //! \brief Renvoi l'unité de la donnée.
    QString getUnitData()              { return m_unit_data;}

    //! \fn  QString  getDescription()
    //! \brief Renvoi la descritpion de la donnée.
    QString  getDescription()            { return m_description; }

    //! \fn  QStringList  getStringList()
    //! \brief Renvoi sous forme d'une string list les données, utilisé pour le QTreeWidgetItem
    QStringList getStringList()  { return QStringList()<<m_type_data<<m_value_data.toString()<<m_unit_data<<m_description; }

    //! \fn  QStringList  getStringListTitle()
    //! \brief Renvoi sous forme d'une string list le titre des données, utilisé pour les titre des QTreeWidget
    static QStringList getStringListTitle() { return QStringList()<<"Type"<<"Valeure"<<"Unité"<<"Description"; }

private:

    QString          m_type_data;

    QVariant         m_value_data;

    QString          m_unit_data;

    QString          m_description;
};

//! \class CListData
//! \brief Représente une liste de donnée. Cette classe possède les accesseurs pour manipuler les données.
class CListData : public QList<CData>
{
public :

    //! \fn  CListData ()
    //! \brief Constructeur
    CListData () {}

    //! \fn  ~CListData ()
    //! \brief Constructeur
    ~CListData () {}

    //! \fn   void setValueData (QString _type_data , QVariant _value_data, QString _unit_data = "" , QString _description = "")
    //! \brief Ajoute un CData si le _type_data n'existe pas dans la liste, ou le modifie sinon.
    void setValueData (QString _type_data , QVariant _value_data, QString _unit_data = "" , QString _description = "")
    {       
        bool exist = false;
        for (int i=0 ; i < count() ; i++)
        {
            if ((*this)[i].getTypeData() == _type_data)
            {
                exist = true;
                (*this)[i].setValueData(_value_data);
            }
        }
        if (exist == false)
        {
            append(CData(_type_data , _value_data , _unit_data , _description));
        }
    }

    //! \fn   QVariant getValueData(QString _type_data)
    //! \brief Renvoi la valeure en fonction du _type_data dans la liste.
    QVariant getValueData(QString _type_data)
    {
        bool find = false;
        QVariant result = 0;
        for (int i=0 ; i < count() && find == false; i++)
        {
            if ((*this)[i].getTypeData() == _type_data)
            {
               result = (*this)[i].getValueData();
               find = true;
            }
        }
        return result;
    }
};

//! \enum EDataInformations
//! \brief Permet d'identifier les différentes listes de données
enum EDataInformations
{
    INFORMATIONS_CONNECTIONS_SETTINGS = 0,
    INFORMATIONS_DATA = 1
};

//! \class CListDataPlugin
//! \brief Cette classe reprèsente la liste des données d'un plugin. Elle stocke plusieurs liste de donnée, ici les paramètres de connections et les données.
class CListDataPlugin : public QList<CListData>
{

public :

    //! \fn   CListDataPlugin ()
    //! \brief Constructeur
    CListDataPlugin ()
    {
       CListData list_data_1;
       CListData list_data_2;
       list_data_1.clear();
       list_data_2.clear();
       append (list_data_1);
       append (list_data_2);
    }


    //! \fn   ~CListDataPlugin ()
    //! \brief Desctructeur
    ~CListDataPlugin ()
    {
        clear();
    }

    //! \fn   CListData& index(int _i)
    //! \brief Renvoi la liste de donnée indexé par  EDataInformations.
    CListData& index(int _i)
    {
        return (*this)[_i];
    }

    //! \fn   CData& index(int _i , int _j)
    //! \brief Renvoi la liste de donnée indexé par  EDataInformations, et le _j ième élément de la liste
    CData& index(int _i , int _j)
    {
        return (*this)[_i][_j];
    }

    //! \fn   QString getTitle (int _i)
    //! \brief Renvoi une description de la liste de donnée indexé par EDataInformations.
    QString getTitle (int _i)
    {
        QString result = "";
        switch (_i)
        {
            case INFORMATIONS_CONNECTIONS_SETTINGS :
                result = "Informations de connexions";
            break;

            case INFORMATIONS_DATA :
                result = "Informations de données";
            break;

            default :
            break;
        }
        return result;
    }
};

//! \class CListDataService
//! \brief Cette classe reprèsente la liste des données d'un service. Un service à accée à toute les informations de tout les plugins. C'est donc une liste de liste de données de plugin.
class CListDataService : public QList<CListDataPlugin*>
{
   public :

    //! \fn   CListDataService ()
    //! \brief Constructeur.
    CListDataService ()
    {
    }

    //! \fn    ~CListDataService ()
    //! \brief Destructeur.
    ~CListDataService ()
    {

    }

    //! \fn  CListDataPlugin* getListDataPlugin (int _data_informations , QString _type_data , QVariant _value_data)
    //! \brief Renvoi la liste de donnée d'un plugin de type EDataInformations, qui contient la valeure _value_data dans le type _type_data.
    CListDataPlugin* getListDataPlugin (int _data_informations , QString _type_data , QVariant _value_data)
    {
        CListDataPlugin *list_data_plugin = NULL;
        bool m_stop = false;
        for (int i=0 ;  i < count() && m_stop == false ; i++)
        {
            if (index(i,_data_informations).getValueData(_type_data) == _value_data)
            {
                list_data_plugin = index(i);
                m_stop = true;
            }
        }
        return list_data_plugin;
    }

    //! \fn    CListDataPlugin* index (int _i)
    //! \brief Renvoi la liste de données d'un plugin. _i est la _ième liste de plugin.
    CListDataPlugin* index (int _i)
    {
        return (*this)[_i];
    }

    //! \fn    CListDataPlugin* index (int _i)
    //! \brief Renvoi la liste de données d'un plugin. _i est la _ième liste de plugin _j est le type de liste EDataInformations.
    CListData& index(int _i , int _j)
    {
        return (*(*this)[_i])[_j];
    }

    //! \fn    CData& index(int _i , int _j , int _k)
    //! \brief Renvoi la liste de données d'un plugin. _i est la _ième liste de plugin _j est le type de liste EDataInformations, et la _k ième données.
    CData& index(int _i , int _j , int _k)
    {
        return (*(*this)[_i])[_j][_k];
    }  
};

#endif
