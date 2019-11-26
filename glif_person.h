#ifndef GLIF_PERSON_H
#define GLIF_PERSON_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

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
    QStringList  m_event1; ///< События у персоны
    QStringList  m_event2; ///< События у персоны

public:
    explicit Glif_Person(size_t radius = 50, QColor color = Qt::GlobalColor::green,QObject *parent = nullptr,
                         int id, QString name, QString name_father, QString born, QStringList  m_event1,
                         QString die, int id_father, QVector<int> id_brother, QVector<int> id_son,
                         QStringList  event2);
    Glif_Person(const Glif_Person&);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

signals:

public slots:
};

#endif // GLIF_PERSON_H
