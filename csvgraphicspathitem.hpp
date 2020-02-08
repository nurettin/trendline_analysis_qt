#ifndef CSVGRAPHICSPATHITEM_HPP
#define CSVGRAPHICSPATHITEM_HPP

#include <QGraphicsPathItem>

class CSVGraphicsPathItem : public QGraphicsPathItem
{
public:
    CSVGraphicsPathItem(QGraphicsItem *parent= 0);
    CSVGraphicsPathItem(QPainterPath const &path, QGraphicsItem *parent= 0);
    static bool lessThan(QGraphicsItem* const &i1, QGraphicsItem* const &i2);
    bool IsSelected;
    static QList<CSVGraphicsPathItem*> extract(QList<QGraphicsItem*> const &items)
    {
        QList<CSVGraphicsPathItem*> csvItems;
        for(int n= 0; n< items.size(); ++ n)
        {
            CSVGraphicsPathItem* csvItem= qgraphicsitem_cast<CSVGraphicsPathItem*>(items[n]);
            if(csvItem) csvItems.push_back(csvItem);
        }
        return csvItems;
    }
    enum { Type= QGraphicsItem::UserType+ 1 };
    int type() const{ return Type; }
protected:
    QPainterPath shape() const
    {
        QPainterPath path(this->path());
        QPainterPathStroker stroke;
        return stroke.createStroke(path);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CSVGRAPHICSPATHITEM_HPP
