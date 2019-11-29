#include "mainwindow.h"
#include "ui_mainwindow.h"


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
        g_pers->setNotes(notes);
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

    connect(g_pers, &Glif_Person::moveElement, this, &MainWindow::redraw);
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

        int y = 0;
        for( auto node_tree : tree_list)
        {
            //отобразим на экране дерево
            //auto node_tree = tree_list.at(0);
            node_tree->reviewSons();
            QList<Glif_Person*> g_pers = node_tree->v_gP;

            scena->addItem(g_pers.at(0));
            int x = 0;

            g_pers.at(0)->setPos(x, y);
            QVector<int> childrens;
            QVector<int> childrens_temp;
            childrens = g_pers.at(0)->m_id_son;

            while( childrens.isEmpty() == false)
            {
                y += 150;
                x = 0;
                for( int i : childrens )
                {
                    Glif_Person* son = node_tree->getPerson(i);
                    if( son == nullptr)
                        qDebug() << "Wtf?";
                    childrens_temp.append(son->m_id_son);
                    scena->addItem(son);
                    son->setPos(x, y);
                    childrens.pop_back();
                    x += 120;
                    //Установка линий
                    QLineF lineBetweenItems;
                    QPointF point(0, son->m_radius);

                    lineBetweenItems.setP1(node_tree->getPerson(son->m_id_father)->scenePos() +  point);
                    lineBetweenItems.setP2(son->scenePos() - point);
                    scena->addLine(lineBetweenItems);
                }
                childrens.append(childrens_temp);
                childrens_temp.clear();
            }

            y+=300;
        }


       ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

void MainWindow::redraw()
{
    int j;
    j++;
}

 void MainWindow::slotCustomMenuRequested(const QPoint pos)
 {
     QMenu menu(this);
     //Устанавливаю контекстное меню относительно позиции курсора
     menu.popup(ui->graphicsView->viewport()->mapToGlobal(pos));
     Glif_Person* element = dynamic_cast<Glif_Person*> (ui->graphicsView->itemAt(pos));
     m_element = element;
     if( element == nullptr)
     {
          QAction* addPerson = menu.addAction("Добавить элемент");
          QAction* redraw = menu.addAction("Перерисовка");
          connect(addPerson, SIGNAL(triggered()), this, SLOT(addPerson()));
          connect(redraw, SIGNAL(triggered()), this, SLOT(redraw()));
     }
     else{
         QAction* removeItem = menu.addAction("Удалить");
         QAction* addLink    = menu.addAction("Добавить связь");
         QAction* editPers   = menu.addAction("Редактирование");
         connect(removeItem, SIGNAL(triggered()), this, SLOT(removeItem()));
         connect(addLink   , SIGNAL(triggered()), this, SLOT(addLink   ()));
         connect(editPers  , SIGNAL(triggered()), this, SLOT(editPers()));
     }
     QAction* selectedAction = menu.exec();
 }

 void MainWindow::editPers()
 {
     Edit_person form(this, m_element);
     form.show();
     form.exec();
 }

MainWindow::~MainWindow()
{
    delete ui;
}


