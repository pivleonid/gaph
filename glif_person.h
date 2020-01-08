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
#include <QPen>
class Glif_Person : public QObject, public QGraphicsItem
{
    Q_OBJECT

    bool m_flagBold_1 = false;
    bool m_flagBold_2 = false;
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



public:

    explicit Glif_Person(int id, QString name, QString name_father, QString born, QStringList  event,
                         QString die, int id_father, QVector<int> id_brother, QVector<int> id_son,
                         QString  notes, size_t radius = 50, QColor color = Qt::GlobalColor::green,
                         QObject *parent = nullptr);
    explicit Glif_Person(int id,  size_t radius = 50, QColor color = Qt::GlobalColor::green,
                         QObject *parent = nullptr);
    Glif_Person(const Glif_Person&);
    ~Glif_Person()
    {

    }
    void setBold_1();
    void setBold_2();
    void setNormal();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void set_EventAndNotes(QStringList ev, QString note)
    {
        m_event = ev;
        m_notes = note;
        setColorFrom_Notes_event();
    }
    void setColorFrom_Notes_event()
    {
        if( !this->m_notes.isEmpty() )
        {
            m_color = Qt::GlobalColor::red;
        }
        if(!m_event.isEmpty())
        {
            for( QString j : m_event)
            {
                if( j.isEmpty() )
                    m_event.pop_back();
            }
            if( !m_event.isEmpty() )
                    m_color = Qt::GlobalColor::yellow;
        }
        if( !this->m_notes.isEmpty() && !m_event.isEmpty())
            m_color = Qt::GlobalColor::darkYellow;
        if( this->m_notes.isEmpty() && m_event.isEmpty())
            m_color = Qt::GlobalColor::green;
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        /* Устанавливаем позицию графического элемента
         * в графической сцене, транслировав координаты
         * курсора внутри графического элемента
         * в координатную систему графической сцены
         * */

        if( event->buttons() == Qt::MouseButton::LeftButton)
        {
            this->setPos(mapToScene(event->pos()));
            emit moveElement(this);
        }
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
    void moveElement( Glif_Person* );

public slots:
};


class linesBetweenItems : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

    QLineF lineBetweenItems;
public:
    Glif_Person* m_father;
    Glif_Person* m_son;

    QRectF boundingRect() const override
    {
      QPointF point(0, m_son->m_radius);
      return QRectF(m_father->scenePos(), m_son->scenePos());
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)  override
    {
      painter->setPen(Qt::black);
      painter->setBrush(Qt::GlobalColor::black);

      //Левая и правая координата
      painter->setPen(QPen(Qt::darkRed, 5, Qt::DashDotLine));
      QPointF point(0, m_son->m_radius);
      QLineF line(m_father->scenePos() +  point, m_son->scenePos() - point);
      painter->drawLine(line);
    }
    linesBetweenItems(Glif_Person* father, Glif_Person* son,  QObject *parent = nullptr):
         QObject(parent), m_father( father ), m_son(son)
    {
        //lineBetweenItems.setP1()
        //lineBetweenItems = new QLineF;
    }

//    void drawLine(QGraphicsScene* scene)
//    {

//        QPointF point(0, m_son->m_radius);
//        lineBetweenItems->setP1(m_father->scenePos() +  point);
//        lineBetweenItems->setP2(m_son->scenePos() - point);
//        scene->addLine(*lineBetweenItems);
//    }

};




#endif // GLIF_PERSON_H
