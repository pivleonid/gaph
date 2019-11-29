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
            QString event;
            for( auto var: m_pers->m_event)
                event.append(var + "\n");
            ui->plainTextEdit->setPlainText(event);

}

Edit_person::~Edit_person()
{
    m_pers->m_name.clear(); m_pers->m_name.append(ui->lineEdit_name->text());
    m_pers->m_nameFather.clear();  m_pers->m_nameFather.append(ui->lineEdit_nameFather->text());
    m_pers->m_die.clear();  m_pers->m_die.append(ui->lineEdit_die->text());
    m_pers->m_born.clear();  m_pers->m_born.append(ui->lineEdit_born->text());
    m_pers->m_notes.clear();  m_pers->m_notes.append(ui->lineEdit_notes->text());
    m_pers->m_event.clear();

    QString text = ui->plainTextEdit->toPlainText();
    QStringList event = text.split('\n');
    for(QString str : event)
        m_pers->m_event.append(str);
//            for( auto var: m_pers->m_event)
//                ui->plainTextEdit->setPlainText(var);


    delete ui;
}
