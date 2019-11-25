#ifndef GENUS_TREE_H
#define GENUS_TREE_H

#include "glif_person.h"
#include "qvector.h"

template <class T> class CNode
{
public:
    CNode* m_parent;
    CNode* m_son;
    CNode* m_brother;
    T m_data;
    CNode()
    {
        m_parent  = nullptr;
        m_son     = nullptr;
        m_brother = nullptr;
    }
    CNode(const T& value) : m_data(value)
    {
        m_parent  = nullptr;
        m_son     = nullptr;
        m_brother = nullptr;
    }
    ~CNode()
    {

    }

};

class genus_tree
{
public:
    genus_tree();
    QVector<int> all_id;
    int count;
    int count_attachment; ///< Кол-во вложений (для анализа)

    CNode<Glif_Person> genus; ///< Род

    void add_person(Glif_Person pers)
    {
        if( pers.m_id_father == 0 )
        {
            //genus = new CNode(pers);
        }
    }
    void add_son(Glif_Person* pers);
    void add_father(Glif_Person* pers);
    void add_brother(Glif_Person* pers);

};





#endif // GENUS_TREE_H
