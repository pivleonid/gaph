#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glif_person.h"
#include "genus_tree.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scena = new QGraphicsScene(this);
    ui->graphicsView->setScene(scena);



    QFile file ("Книга1_КМРД.csv");
    QTextStream in(&file);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.

    QStringList list, list_split;
    if(file.open(QIODevice::ReadOnly))
    {
        while(!in.atEnd())
        {
            QString line = in.readLine();
            list.append(line);
            line.clear();
        }

    }
    else qDebug() << "No open!";

    for( auto var: list)
    {
        list_split.append(var.split(";"));
    }
    const int count_pos = 24;
    int count = list_split.count()/count_pos;

    QVector<Glif_Person*> vec_per;

    QList<genus_tree*> tree_list;
    //Glif_Person* g_pers = new Glif_Person();
    //i==0 - заголовок
    for( int i = 1; i < count; i++)
    {
        int id = list_split.at(i * count_pos).toInt();
        QString name = list_split.at(i * count_pos + 1);
        QString name_father = list_split.at(i * count_pos + 2);
        QString born = list_split.at(i * count_pos + 3);
        QStringList  event;
        event << list_split.at(i * count_pos + 4)
              << list_split.at(i * count_pos + 5)
              << list_split.at(i * count_pos + 6)
              << list_split.at(i * count_pos + 7)
              << list_split.at(i * count_pos + 8);
        QString die = list_split.at(i * count_pos + 9);
        int id_father = list_split.at(i * count_pos + 10).toInt();
        QVector<int> id_brother;
        id_brother << list_split.at(i * count_pos + 11).toInt()
                   << list_split.at(i * count_pos + 12).toInt()
                   << list_split.at(i * count_pos + 13).toInt()
                   << list_split.at(i * count_pos + 14).toInt()
                   << list_split.at(i * count_pos + 15).toInt()
                   << list_split.at(i * count_pos + 16).toInt();
        QVector<int> id_son;
        id_son << list_split.at(i * count_pos + 17).toInt()
               << list_split.at(i * count_pos + 18).toInt()
               << list_split.at(i * count_pos + 19).toInt()
               << list_split.at(i * count_pos + 20).toInt()
               << list_split.at(i * count_pos + 21).toInt()
               << list_split.at(i * count_pos + 22).toInt();

        QString notes = list_split.at(i * count_pos + 23);

        Glif_Person* g_pers = new Glif_Person(id, name, name_father, born, event, die, id_father,
                                              id_brother, id_son, notes);
        g_pers->setEvent(event);
        name.clear(); name_father.clear(); born.clear(); event.clear(); die.clear();
        id_brother.clear(); id_son.clear(); notes.clear();

        if( id_father != 0)
        {
           vec_per << g_pers;
        }
        else
        {
            genus_tree* g_tree = new genus_tree();
            g_tree->addPerson(g_pers);
            tree_list.append(g_tree);
        }

//        scena->addItem(g_pers);

//        static int x = 0;
//        static int y = 0;

//        g_pers->setPos(x, y);

//        x+=100;
//        y+=100;


    }


    //tree_list - там одни отцы
    //теперь надо рассортировать детей

    bool flag = false;
    for( auto child : vec_per)
    {
//        if( flag == true)
//        {
//            vec_per.pop_back();
//            flag = false;
//        }
        int id_father = child->m_id_father;
        for( auto node_tree : tree_list)
        {
            flag = node_tree->foundId(id_father);
            if( flag )
            {
                node_tree->addPerson(child);
                vec_per.pop_back();
                break;
            }
        }
    }


        qDebug() << "Остались неотсортированные персоны:" << vec_per.count();


    //отобразим на экране дерево
    auto node_tree = tree_list.at(0);
    QList<Glif_Person*> g_pers = node_tree->v_gP;

    scena->addItem(g_pers.at(0));
    int x = 0;
    int y = 0;
    g_pers.at(0)->setPos(x, y);
    QVector<int> childrens;
    childrens = g_pers.at(0)->m_id_son;
    while( childrens.isEmpty() == true)
    {
        for( )
    }

    int a;
    a++;

}

MainWindow::~MainWindow()
{
    delete ui;
}

