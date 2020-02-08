#ifndef CSVGRAPHICSVIEW_HPP
#define CSVGRAPHICSVIEW_HPP

#include <vector>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsItem>
#include "CSVOkuyucu.hpp"
#include "csvgraphicspathitem.hpp"

class CSVGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CSVGraphicsView(QWidget *parent= 0);
    QGraphicsScene scene;
    std::size_t DataSize;
    QList<CSVGraphicsPathItem*> extraSelectedItems();
    void clearExtraSelectedItems();
    std::vector<int> hideExtraSelectedItems();
    void showExtraHiddenItems(std::vector<int> const &items);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void wheelEvent(QWheelEvent *event);
    void prepareMenu();
    void saveSelection();

    QMenu menu;
    double zoomFactor;

signals:
    void linesSelected(QRect const &area, QList<QVariant> const &data);

public slots:
    void loadCSV();

private slots:
    void ozellikCizgileri();
};

#endif // CSVGRAPHICSVIEW_HPP
