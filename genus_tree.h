#ifndef GENUS_TREE_H
#define GENUS_TREE_H

#include "glif_person.h"
#include "qvector.h"

#include <QDebug>

//template <class T> class CTree_node
//{
//public:
//    CTree_node*        m_parent;
//    QList<CTree_node*> m_son;
//    T           *m_data;
//    CTree_node()
//    {
//        //m_parent  = nullptr;
//        // m_son     = nullptr;
//        //m_brother = nullptr;
//    }
//    CTree_node( T* value) : m_data(value)
//    {
//        //m_parent  = nullptr;
//        //m_son     = nullptr;
//        // m_brother = nullptr;
//    }
//    ~CTree_node()
//    {

//    }


//};

#include <algorithm>
typedef QList<Glif_Person*> vecGliph;
class genus_tree
{

public:
    vecGliph v_gP;
    QVector<int> all_id;

    void addFather(Glif_Person* gp);
    Glif_Person* getFather();

    bool addPerson(Glif_Person* gp);
    Glif_Person* getPerson(int id);
    /**
     * @brief foundId
     * @param id
     * @return возвращает указатель на глиф в дереве
     */
    bool foundId(int id);
    void reviewSons();
    /**
     * @brief getMaxId- получение max id
     * @return
     */
    int getMaxId();
    /**
     * @brief deletePerson
     * @param person
     * @return false - если дерево пустое
     */
    bool deletePerson(Glif_Person* person);
    /**
     * @brief addTree добавление дерева к текущему дереву
     * @param person - глиф, начиная с которого будет добавлено дерево
     * @param tree - указатель на добавляемое дерево
     * @return
     */
    void addTree(Glif_Person* person, genus_tree* tree);
    genus_tree* removeTree(Glif_Person* person);
    ~genus_tree();


};


//typedef CTree_node<Glif_Person> treeNodePers;

//class genus_tree
//{
//public:
//    genus_tree()//(Glif_Person father) : m_father(father){};
//    {
//        m_father = nullptr;
//    }

//    QVector<int> all_id;
//    int count;
//    int count_attachment; ///< Кол-во вложений (для анализа)

//    treeNodePers* m_father;


//    bool addFather(Glif_Person* person)
//    {
//        m_father = new treeNodePers(person);
//        all_id.append(person->m_id);
//    }


//    treeNodePers* foundId(int id)
//    {
//        if ( m_father == nullptr )
//            return nullptr;
//        if( m_father->m_data->m_id == id)
//            return  m_father;
//        QList<treeNodePers*> children; //очередь CTree_node<Glif_Person*>
//        children = m_father->m_son;
//        while( children.empty() == false )
//        {
//            treeNodePers* node = children.front();
//            if( node->m_data->m_id == id)
//                return  node;
//            else {
//                children.append(node->m_son);
//            }
//        }
//        return nullptr;
//    }

//    bool add_person(Glif_Person pers)
//    {
//        treeNodePers* treePers = foundId(pers.m_id_father);
//        if( treePers == nullptr)
//        {
//            return false;
//        }



//    }
//    void add_son    (Glif_Person pers);
//    void add_father (Glif_Person pers);
//    void add_brother(Glif_Person pers);

//};





#endif // GENUS_TREE_H
