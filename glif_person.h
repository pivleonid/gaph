#ifndef GLIF_PERSON_H
#define GLIF_PERSON_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class Glif_Person : public QObject, public QGraphicsItem
{
    Q_OBJECT

    size_t      m_radius;
    QColor      m_color;
    int         m_id;
    QString     m_name;
    QString     m_nameFather;
    QString     m_born;
    QString     m_die;
    QStringList m_event; ///< События у персоны

public:
    explicit Glif_Person(size_t radius = 50, QColor color = Qt::GlobalColor::green,QObject *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

signals:

public slots:
};

#endif // GLIF_PERSON_H
