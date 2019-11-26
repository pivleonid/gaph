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

//    QGraphicsScene* scena = new QGraphicsScene(this);
//    ui->graphicsView->setScene(scena);
//    Glif_Person* g_pers = new Glif_Person();
//    Glif_Person* g_pers1 = new Glif_Person();
//    scena->addItem(g_pers);
//    scena->addItem(g_pers1);



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

    int a;
    a++;

}

MainWindow::~MainWindow()
{
    delete ui;
}

