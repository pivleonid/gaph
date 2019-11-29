#ifndef GLIF_PERSON_H
#define GLIF_PERSON_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>


//#include "edit_person.h"
#include <QMenu>

#include <QGraphicsScene>

class Glif_Person : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    size_t       m_radius;
    QColor       m_color;
    int          m_id;
    int          m_id_father;
    QVector<int> m_id_brother;
    QVector<int> m_id_son;
    QString      m_name;
    QString      m_nameFather;
    QString      m_born;
    QString      m_die;
    QStringList  m_event; ///< События у персоны
    QString      m_notes; ///< События у персоны
//    Edit_Person  m_ed_pers;

public:

    explicit Glif_Person(int id, QString name, QString name_father, QString born, QStringList  event,
                         QString die, int id_father, QVector<int> id_brother, QVector<int> id_son,
                         QString  notes, size_t radius = 50, QColor color = Qt::GlobalColor::green,
                         QObject *parent = nullptr);
    Glif_Person(const Glif_Person&);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setEvent(QStringList ev)
    {
        m_event = ev;
        for( QString j : ev)
        {
            if( j.isEmpty() )
                m_event.pop_back();
        }
        if( !m_event.isEmpty() )
                m_color = Qt::GlobalColor::yellow;
    }

    void setNotes(QString note)
    {
        m_notes = note;
        if( !note.isEmpty() )
            m_color = Qt::GlobalColor::red;
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        /* Устанавливаем позицию графического элемента
         * в графической сцене, транслировав координаты
         * курсора внутри графического элемента
         * в координатную систему графической сцены
         * */

        if( event->buttons() == Qt::MouseButton::LeftButton)
            this->setPos(mapToScene(event->pos()));
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        /* При нажатии мышью на графический элемент
         * заменяем курсор на руку, которая держит этот элемента
         * */
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        /* При отпускании мышью элемента
         * заменяем на обычный курсор стрелку
         * */
        Qt::MouseButton btn = event->button();
        if( btn == Qt::MouseButton::RightButton)
        {
        }
        else
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
            Q_UNUSED(event);
        }
    }
signals:

public slots:
};

#endif // GLIF_PERSON_H
