#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include "csvgraphicspathitem.hpp"

CSVGraphicsPathItem::CSVGraphicsPathItem(QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    //setCacheMode(QGraphicsItem::DeviceCoordinateCache);
     IsSelected= false;
}

CSVGraphicsPathItem::CSVGraphicsPathItem(QPainterPath const &path, QGraphicsItem *parent)
    : QGraphicsPathItem(path, parent)
{
}

void CSVGraphicsPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    if(isSelected()|| IsSelected)
    {
        IsSelected= true;
        painter->setPen(Qt::red);
    }
    else
        painter->setPen(Qt::darkGray);
    painter->drawPath(this->path());
}

bool CSVGraphicsPathItem::lessThan(QGraphicsItem* const &i1, QGraphicsItem* const &i2)
{
    return i1->data(0).toInt()< i2->data(0).toInt();
}
