#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    m_id_count = 5000;
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

    //QList<genus_tree*> tree_list;
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
                    linesBetweenItems* line = new linesBetweenItems(node_tree->getPerson(son->m_id_father),son);
                    scena->addItem(line);
                    m_listLine.append(line);
                }
                childrens.append(childrens_temp);
                childrens_temp.clear();
            }

            y+=300;
        }


       ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

void MainWindow::redraw( Glif_Person* element)
{

    element->scene()->update();
}

 void MainWindow::slotCustomMenuRequested(const QPoint pos)
 {
     QMenu menu(this);
     m_pos = pos;
     //Устанавливаю контекстное меню относительно позиции курсора
     menu.popup(ui->graphicsView->viewport()->mapToGlobal(pos));
     Glif_Person* element = dynamic_cast<Glif_Person*> (ui->graphicsView->itemAt(pos));
     m_element = element;
     if( element == nullptr)
     {
          QAction* addPerson = menu.addAction("Добавить отца");
          connect(addPerson, SIGNAL(triggered()), this, SLOT(addPerson()));
     }
     else{
         QAction* removeItem = menu.addAction("Удалить");
         QAction* addBrother = menu.addAction("Добавить брата");
         QAction* addSon     = menu.addAction("Добавить сына");
         QAction* editPers   = menu.addAction("Редактирование");
         connect(removeItem, SIGNAL(triggered()), this, SLOT(removeItem()));
         connect(addBrother, SIGNAL(triggered()), this, SLOT(addBrother()));
         connect(addSon    , SIGNAL(triggered()), this, SLOT(addSon()));
         connect(editPers  , SIGNAL(triggered()), this, SLOT(editPers()));
     }
     QAction* selectedAction = menu.exec();
 }

 void MainWindow::addBrother()
 {
     Glif_Person* father = m_element;
     genus_tree* genus = nullptr;
     for( auto tree : tree_list)
     {
         if( tree->foundId(father->m_id) == true )
             genus = tree;
     }
     if( genus == nullptr)
     {
         qDebug() << "genus == nullptr";
         return;
     }
     Glif_Person* person;
     person = genus->getPerson(father->m_id);

     //
     Glif_Person* brother = new Glif_Person(m_id_count);
     m_id_count++;
     person->m_id_brother.append(brother->m_id);
     brother->m_id_father = person->m_id_father;
     genus->addPerson(brother);

     QGraphicsScene* scena = ui->graphicsView->scene();
     scena->addItem(brother);
     brother->setPos(person->pos().rx() + 120, person->pos().ry());

     Edit_person form(this, brother);
     form.show();
     form.exec();
     //отец не известен
     if(brother->m_id_father == person->m_id_father && person->m_id_father == 0 )
     {
         Glif_Person* father = new Glif_Person(m_id_count);
         m_id_count++;
         genus->addFather(father);
         brother->m_id_father = father->m_id;
         person->m_id_father = father->m_id;

         scena->addItem(father);
         father->setPos(person->pos().rx() + 60, person->pos().ry() - 120);

         Edit_person form(this, brother);
         form.show();
         form.exec();

         linesBetweenItems* line = new linesBetweenItems(father, brother);
         linesBetweenItems* line1 = new linesBetweenItems(father, person);
         scena->addItem(line);
         scena->addItem(line1);
         m_listLine << line << line1;

         connect(brother, &Glif_Person::moveElement, this, &MainWindow::redraw);
         connect(father, &Glif_Person::moveElement, this, &MainWindow::redraw);

     }
     {

         linesBetweenItems* line = new linesBetweenItems(genus->getPerson(person->m_id_father), brother);
         scena->addItem(line);
         m_listLine << line;

         connect(brother, &Glif_Person::moveElement, this, &MainWindow::redraw);
     }

 }
void MainWindow::addPerson()
{
    Glif_Person* pers = new Glif_Person(m_id_count);
    m_id_count++;
    genus_tree* tree = new genus_tree ;
    tree->addPerson(pers);
    tree_list.append(tree);

    QGraphicsScene* scena = ui->graphicsView->scene();
    scena->addItem(pers);
    pers->setPos(m_pos);

    Edit_person form(this, pers);
    form.show();
    form.exec();
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


