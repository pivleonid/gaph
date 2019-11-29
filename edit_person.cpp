#include "edit_person.h"
#include "ui_edit_person.h"

Edit_person::Edit_person(QWidget *parent, Glif_Person* pers) :
    QDialog(parent), m_pers(pers), ui(new Ui::Edit_person)
{
    ui->setupUi(this);
    if ( pers == nullptr)
        this->close();

    ui->lineEdit_name->setText(m_pers->m_name);
            ui->lineEdit_nameFather->setText(m_pers->m_nameFather);
            ui->lineEdit_die->setText(m_pers->m_die);
            ui->lineEdit_born->setText(m_pers->m_born);
            ui->lineEdit_notes->setText(m_pers->m_notes);
            for( auto var: m_pers->m_event)
                ui->plainTextEdit->setPlainText(var);

}

Edit_person::~Edit_person()
{
    m_pers->m_name.clear(); m_pers->m_name.append(ui->lineEdit_name->text());
    m_pers->m_nameFather.clear();  m_pers->m_nameFather.append(ui->lineEdit_nameFather->text());
//            ui->lineEdit_die->setText(m_pers->m_die);
//            ui->lineEdit_born->setText(m_pers->m_born);
//            ui->lineEdit_notes->setText(m_pers->m_notes);
//            for( auto var: m_pers->m_event)
//                ui->plainTextEdit->setPlainText(var);


    delete ui;
}
