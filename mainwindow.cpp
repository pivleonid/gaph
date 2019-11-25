#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glif_person.h"
#include "genus_tree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scena = new QGraphicsScene(this);
    ui->graphicsView->setScene(scena);
    Glif_Person* g_pers = new Glif_Person();
    Glif_Person* g_pers1 = new Glif_Person();
    scena->addItem(g_pers);
    scena->addItem(g_pers1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

