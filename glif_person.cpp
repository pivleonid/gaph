#include "glif_person.h"

Glif_Person::Glif_Person(int id, QString name, QString name_father, QString born, QStringList  event,
                         QString die, int id_father, QVector<int> id_brother, QVector<int> id_son,
                         QString  notes, size_t radius, QColor color, QObject *parent)
    : QObject(parent), QGraphicsItem(), m_radius(radius), m_color(color)
{
    m_id = id;
    m_name = name;
    m_nameFather = name_father;
    m_born = born;
    m_event = event;
    m_die = die;
    m_id_father = id_father;
    m_id_brother = id_brother;
    m_id_son = id_son;
    m_notes = notes;

    m_color = Qt::GlobalColor::green;

}

Glif_Person::Glif_Person(int id, size_t radius, QColor color, QObject *parent)
    : QObject(parent), QGraphicsItem(), m_radius(radius), m_color(color)
{
    m_id_father = 0;
}


QRectF Glif_Person::boundingRect() const {
  return QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius));
}
void Glif_Person::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{


  painter->setPen(Qt::black);
  painter->setBrush(m_color);
  //Левая и правая координата
  painter->drawRect(QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius)));
  painter->drawRect(QRectF(QPoint(-m_radius, 0), QPoint(m_radius, m_radius)));

  //x, y ,weight, height
  painter->drawText(QRect(-m_radius, -m_radius, m_radius *2 , 20), Qt::AlignCenter, m_name);
  painter->drawText(QRect(-m_radius , -m_radius + m_radius/2,  m_radius *2,20), Qt::AlignCenter, m_nameFather);

  //painter->drawPolygon(polygon());
}
