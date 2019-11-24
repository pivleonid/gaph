#include "glif_person.h"

Glif_Person::Glif_Person(size_t radius, QColor color,QObject *parent)
    : QObject(parent), QGraphicsItem(), m_radius(radius), m_color(color)
{

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
  painter->drawText(QRect(-m_radius, -m_radius, m_radius *2 , 20), Qt::AlignCenter, "Hello");
  painter->drawText(QRect(-m_radius , -m_radius + m_radius/2,  m_radius *2,20), Qt::AlignCenter, "World");

  //painter->drawPolygon(polygon());
}
