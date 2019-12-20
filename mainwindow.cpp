#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    m_id_count = 1; // 0 индекс считается отцом
    ui->setupUi(this);
    QGraphicsScene* scena = new QGraphicsScene(this);
    ui->graphicsView->setScene(scena);

    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    connect(ui->action_open, SIGNAL(triggered()), this, SLOT(openCSV()));
    connect(ui->action_save, SIGNAL(triggered()), this, SLOT(saveCSV()));

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


 void MainWindow::addSon()
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

     Glif_Person* son = new Glif_Person(m_id_count);
     m_id_count++;

     father->m_id_son << son->m_id;
     son->m_id_father = father->m_id;
     genus->addPerson(son);

     QGraphicsScene* scena = ui->graphicsView->scene();
     scena->addItem(son);
     son->setPos(father->pos().rx(), father->pos().ry() + 120);

     Edit_person form(this, son);
     form.show();
     form.exec();

     linesBetweenItems* line = new linesBetweenItems(father, son);
     scena->addItem(line);
     m_listLine << line;

     connect(son, &Glif_Person::moveElement, this, &MainWindow::redraw);



 }
 void MainWindow::addBrother()
 {
     Glif_Person* element = m_element;
     genus_tree* genus = nullptr;
     for( auto tree : tree_list)
     {
         if( tree->foundId(element->m_id) == true )
             genus = tree;
     }
     if( genus == nullptr)
     {
         qDebug() << "genus == nullptr";
         return;
     }
     //Glif_Person* person;
     //person = genus->getPerson(father->m_id);

     //
     Glif_Person* brother = new Glif_Person(m_id_count);
     m_id_count++;
     element->m_id_brother.append(brother->m_id);
     brother->m_id_brother.append(element->m_id);
     brother->m_id_father = element->m_id_father;
     genus->addPerson(brother);

     QGraphicsScene* scena = ui->graphicsView->scene();
     scena->addItem(brother);
     brother->setPos(element->pos().rx() + 120, element->pos().ry());

     Edit_person form(this, brother);
     form.show();
     form.exec();
     //отец не известен
     if(brother->m_id_father == element->m_id_father && element->m_id_father == 0 )
     {
         Glif_Person* father = new Glif_Person(m_id_count);
         m_id_count++;
         genus->addFather(father);
         brother->m_id_father = father->m_id;
         element->m_id_father = father->m_id;

         scena->addItem(father);
         father->setPos(element->pos().rx() + 60, element->pos().ry() - 120);

         Edit_person form(this, father);
         form.show();
         form.exec();

         linesBetweenItems* line = new linesBetweenItems(father, brother);
         linesBetweenItems* line1 = new linesBetweenItems(father, element);
         scena->addItem(line);
         scena->addItem(line1);
         m_listLine << line << line1;

         connect(brother, &Glif_Person::moveElement, this, &MainWindow::redraw);
         connect(father, &Glif_Person::moveElement, this, &MainWindow::redraw);

     }
     {

         linesBetweenItems* line = new linesBetweenItems(genus->getPerson(element->m_id_father), brother);
         scena->addItem(line);
         m_listLine << line;
         connect(brother, &Glif_Person::moveElement, this, &MainWindow::redraw);
     }

 }
void MainWindow::addPerson()
{
    Glif_Person* pers = new Glif_Person(m_id_count);
    m_id_count++;

    QPointF pos = ui->graphicsView->mapToScene(m_pos);
    genus_tree* tree = new genus_tree ;
    tree->addPerson(pers);
    tree_list.append(tree);

    QGraphicsScene* scena = ui->graphicsView->scene();
    scena->addItem(pers);
    pers->setPos(pos);
    Edit_person form(this, pers);
    form.show();
    form.exec();

    connect(pers, &Glif_Person::moveElement, this, &MainWindow::redraw);


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



void MainWindow::openCSV()
{
    QString nameFile = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QDir::currentPath(), tr("Файл csv (*.csv)"));
    if(nameFile.size() != 0) {

        QGraphicsScene* scena = ui->graphicsView->scene();
        QFile file (nameFile);
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



    }
    //--поиск макс номера
    for( genus_tree* tree : tree_list)
    {
         int id = tree->getMaxId();
         if( m_id_count < id )
             m_id_count = id + 2;
    }
}


void MainWindow::saveCSV()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Сохраненить файл"), tr("tree.csv"), tr("Древо (*.csv)"));
    if(file_name.isEmpty() == false && file_name.indexOf(tr(".csv")) > 0)
    {

        QFile file(file_name);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            in.setGenerateByteOrderMark(true);

            //шапка
            QString hat = "№ п/п;ИМЯ;ОТЧЕСТВО;Год рождения;СОБЫТИЯ;;;;;Год смерти;ОТЕЦ;БРАТЬЯ;;;;;;СЫНОВЬЯ;;;;;;Примечания\n";
            in << hat;

            for( genus_tree* tree : tree_list )
            {
                QList<Glif_Person*> vecGliph = tree->v_gP;
                for( Glif_Person* person : vecGliph)
                {
                    QStringList string;
                    string << QString::number(person->m_id);
                    string.append(person->m_name);
                    string.append(person->m_nameFather);
                    string.append(person->m_born);
                    int count = person->m_event.count();
                    for( int i = 0; i < 5; i++ )
                    {
                        if( i < count )
                            string.append(person->m_event.at(i));
                        else
                            string.append("");
                    }
                    string.append(person->m_die);
                    string << QString::number( person->m_id_father);

                    count = person->m_id_brother.count();
                    for( int i = 0; i < 6; i++ )
                    {
                        if( i < count )
                            string<< QString::number(person->m_id_brother.at(i));
                        else
                            string.append("");
                    }

                    count = person->m_id_son.count();
                    for( int i = 0; i < 6; i++ )
                    {
                        if( i < count )
                        {
                            string << QString::number(person->m_id_son.at(i));
                        }
                        else
                        {
                            string.append("");
                        }
                    }
                    string.append(person->m_notes);
                    in << string.join( ';' )+"\n";
                }
            }
            file.close();
        }



    }
}

