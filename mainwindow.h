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

#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Glif_Person* m_element = nullptr; ///< выделенный элемент на сцене
    Glif_Person* m_el_father = nullptr;///< выделенный элемент отца
    Glif_Person* m_el_son = nullptr;///< выделенный элемент сына
    QList<genus_tree*> tree_list; ///< QList деревьев
    /**
     * @brief getTree получить указатель на дерево
     * @param person ячейка дерева
     * @return nullptr- такой ячейки нет
     */
    genus_tree* getTree(Glif_Person* person)
    {
        genus_tree* genus = nullptr;
        for( auto tree : tree_list)
        {
            if( tree->foundId(person->m_id) == true )
                genus = tree;
        }
        return genus;
    }
    int m_id_count;
    QPoint m_pos;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotCustomMenuRequested(QPoint pos);
    void editPers();
    void redraw( Glif_Person*);
    void addPerson();
    void addBrother();
    void addSon();
    void removeItem();

    void openCSV();
    void saveCSV();

    void boldFather();
    void boldSon();

private:
    Ui::MainWindow *ui;
    QList<linesBetweenItems*> m_listLine;


};
#endif // MAINWINDOW_H
