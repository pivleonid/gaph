#include "genus_tree.h"

void genus_tree::addFather(Glif_Person* gp)
{
    v_gP.prepend(gp);
    all_id.prepend(gp->m_id);
}
Glif_Person* genus_tree::getFather()
{
   return v_gP.at(0);
}

bool genus_tree::addPerson(Glif_Person* gp)
{
   v_gP.append(gp);
   all_id.append(gp->m_id);
   return true;
}
Glif_Person* genus_tree::getPerson(int id)
{
    for( auto person : v_gP)
    {
        if ( person->m_id == id )
            return person;
    }
    return nullptr;
}
bool genus_tree::foundId(int id)
{
    for(auto var : v_gP)
    {
        if( var->m_id == id )
            return true;
    }
    return  false;
}

void genus_tree::reviewSons()
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

int genus_tree::getMaxId()
{
    return  *std::max_element(all_id.constBegin(), all_id.constEnd());
}
/**
 * @brief deletePerson
 * @param person
 * @return false - если дерево пустое
 */
bool genus_tree::deletePerson(Glif_Person* person)
{
    //удаляем связь между персоной и сыновьями
    for( int id_child : person->m_id_son)
    {
        Glif_Person* son = this->getPerson(id_child);
        if( son == nullptr)
            qDebug() << "son == nulptr, id_child:" << id_child;
        son->m_id_father = 0;
    }
    //если есть отец- стираем информацию о предке
    if(person->m_id_father != 0)
    {
        Glif_Person* father = this->getPerson(person->m_id_father);
        if( father == nullptr)
            qDebug() << "father == nulptr";
        int index = father->m_id_son.indexOf(person->m_id);
        father->m_id_son.remove(index);
    }

    //стираю инфомцию из дерева
    all_id.remove(all_id.indexOf(person->m_id));
    v_gP.removeAt(v_gP.indexOf(person));
    //delete person;

    if( all_id.count() > 0)
        return true;
    return  false;
}
void genus_tree::addTree(Glif_Person* person, genus_tree* tree)
{
    Glif_Person* person_copy = tree->getFather();
    person->m_id_son.append(person_copy->m_id);
    person_copy->m_id_father = person->m_id;
    all_id.append(person_copy->m_id);
    v_gP.append(person_copy);

    QVector<int> childrens;
    QVector<int> childrens_temp;
    childrens = person_copy->m_id_son;

    while( childrens.isEmpty() == false)
    {
        for( int i : childrens )
        {
            Glif_Person* son = tree->getPerson(i);
            if( son == nullptr)
            {
                qDebug() << "Wtf?";
                return;
            }
            childrens_temp.append(son->m_id_son);
            //
            this->addPerson(son);
            childrens.pop_back();
        }
        childrens.append(childrens_temp);
        childrens_temp.clear();
    }

    tree->v_gP.clear();
    tree->all_id.clear();

}


genus_tree::~genus_tree()
{
    for(Glif_Person* gliph : v_gP)
    {
        //v_gP.removeFirst();
        delete gliph;
    }
}
