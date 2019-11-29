#ifndef EDIT_PERSON_H
#define EDIT_PERSON_H

#include <QDialog>
#include <glif_person.h>

namespace Ui {
class Edit_person;
}

class Edit_person : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_person(QWidget *parent = nullptr,  Glif_Person* pers = nullptr);
    ~Edit_person();

private:
    Ui::Edit_person *ui;
    Glif_Person     *m_pers;
};

#endif // EDIT_PERSON_H
