#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "glif_person.h"
#include "genus_tree.h"
#include "edit_person.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Glif_Person* m_element; // -- выделенный элемент
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotCustomMenuRequested(QPoint pos);
    void editPers();
    void redraw();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
