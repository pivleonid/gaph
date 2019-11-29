#ifndef GENUS_TREE_H
#define GENUS_TREE_H

#include "glif_person.h"
#include "qvector.h"

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

typedef QList<Glif_Person*> vecGliph;
class genus_tree
{

public:
    vecGliph v_gP;
    QVector<int> all_id;

    bool addPerson(Glif_Person* gp)
    {
       v_gP.append(gp);
       all_id.append(gp->m_id);
    }
    Glif_Person* getPerson(int id)
    {
        for( auto person : v_gP)
        {
            if ( person->m_id == id )
                return person;
        }
        return nullptr;
    }
    bool foundId(int id)
    {
        for(auto var : v_gP)
        {
            if( var->m_id == id )
                return true;
        }
        return  false;
    }

    void reviewSons()
    {
        for( int i : all_id)
        {
            Glif_Person* son = getPerson( i );
            for( int s : son->m_id_son)
            {
                if( s == 0)
                    son->m_id_son.pop_back();
            }
            for( QString j : son->m_event)
            {
                if( j == 0)
                    son->m_event.pop_back();
            }
            Glif_Person* father = getPerson(son->m_id_father);
            if( father == nullptr)
                continue;
            //если таких номеров нет- добавляем
            if( father->m_id_son.indexOf(son->m_id) < 0 )
                father->m_id_son.append(son->m_id);

        }
    }

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
