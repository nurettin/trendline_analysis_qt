#include <QFileDialog>
#include <QGraphicsPathItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QString>
//#include <QGLWidget>
#include "Matematik.hpp"
#include "csvgraphicspathitem.hpp"
#include "csvgraphicsview.hpp"

CSVGraphicsView::CSVGraphicsView(QWidget *parent)
    : QGraphicsView(parent), menu(this) {
  setParent(parent);
  // this->setViewport(new QGLWidget(parent));
  setScene(&scene);
  scene.setSceneRect(QRect(0, 0, 640, 480));
  setDragMode(QGraphicsView::RubberBandDrag);
  setRubberBandSelectionMode(Qt::IntersectsItemShape);
  // setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
  prepareMenu();
  zoomFactor = 1.;
}

void CSVGraphicsView::contextMenuEvent(QContextMenuEvent *e) {
  menu.exec(e->globalPos());
}

void CSVGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);
  if (event->button() != Qt::LeftButton)
    return;
  if (scene.selectedItems().isEmpty()) {
    clearExtraSelectedItems();
    return;
  }
  QList<CSVGraphicsPathItem *> items = extraSelectedItems();
  qSort(items.begin(), items.end(), CSVGraphicsPathItem::lessThan);
  QList<QVariant> data;
  for (int n = 0; n < items.size(); ++n)
    data.push_back(items[n]->data(0));
  emit linesSelected(scene.selectionArea().boundingRect().toRect(), data);
}

void CSVGraphicsView::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
  case Qt::Key_Space:
    menu.exec(this->contentsRect().center());
    break;
  case Qt::Key_Control:
    setDragMode(QGraphicsView::ScrollHandDrag);
    break;
  }
}

void CSVGraphicsView::keyReleaseEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Control)
    setDragMode(QGraphicsView::RubberBandDrag);
}

void CSVGraphicsView::wheelEvent(QWheelEvent *event) {
  zoomFactor += 2 * event->delta() / 1200.;
  setMatrix(QMatrix().scale(zoomFactor, zoomFactor));
}

void CSVGraphicsView::prepareMenu() {
  QAction *act = 0;
  act = new QAction(tr("&Load"), this);
  act->setStatusTip(tr("Load File"));
  connect(act, SIGNAL(triggered()), this, SLOT(loadCSV()));
  menu.addAction(act);

  act = new QAction(tr("&Property Lines"), this);
  act->setCheckable(true);
  connect(act, SIGNAL(toggled(bool)), this, SLOT(ozellikCizgileri()));
  menu.addAction(act);
}

void CSVGraphicsView::ozellikCizgileri() {}

void CSVGraphicsView::loadCSV() {
  QString dosyaIsmi = QFileDialog::getOpenFileName(
      this, tr("Load File"), "", tr("CSV Files (*.csv *.txt)"));
  scene.clear();
  try {
    // this->statusBar()->showMessage(tr("Loading file..."));
    onur::bilim::CSVOkuyucu::CSVData csv =
        onur::bilim::CSVOkuyucu::Oku(dosyaIsmi.toStdString());
    QRect alan = this->rect();
    double w = double(alan.width()) / (csv.SutunSayisi() - 1);
    for (std::vector<std::vector<double>>::iterator r = csv.Data.begin();
         r != csv.Data.end(); ++r) {
      QPainterPath yol;
      std::vector<double>::iterator c = r->begin();
      double bx = (c - r->begin()) * w;
      double by = alan.height() - onur::bilim::normalizasyon<double>(
                                      csv.Min, csv.Max, 0, alan.height(), *c);
      yol.moveTo(bx, by);
      ++c;
      for (; c != r->end(); ++c) {
        double px = (c - r->begin()) * w;
        double py = alan.height() - onur::bilim::normalizasyon<double>(
                                        csv.Min, csv.Max, 0, alan.height(), *c);
        yol.lineTo(px, py);
      }
      QGraphicsPathItem *pyol = new CSVGraphicsPathItem(yol);
      pyol->setData(0,
                    QVariant(static_cast<long long>(r - csv.Data.begin() + 1)));
      pyol->setFlag(QGraphicsItem::ItemIsSelectable, true);
      scene.addItem(pyol);
    }
    DataSize = csv.Data.size();
    // this->statusBar()->showMessage(tr("File loaded."));
  } catch (std::exception &ex) {
    QMessageBox::information(this, tr("Error"),
                             QString(tr("An error occured reading %1: %2"))
                                 .arg(dosyaIsmi, ex.what()));
    // this->statusBar()->showMessage(tr("Unable to load file."));
    return;
  }
  clearExtraSelectedItems();
}

QList<CSVGraphicsPathItem *> CSVGraphicsView::extraSelectedItems() {
  QList<CSVGraphicsPathItem *> extra =
      CSVGraphicsPathItem::extract(scene.items());
  for (QList<CSVGraphicsPathItem *>::Iterator i = extra.begin();
       i != extra.end();)
    if (!(*i)->IsSelected)
      i = extra.erase(i);
    else
      ++i;
  return extra;
}

void CSVGraphicsView::clearExtraSelectedItems() {
  QList<CSVGraphicsPathItem *> extra =
      CSVGraphicsPathItem::extract(scene.items());
  for (int n = 0; n < extra.size(); ++n)
    extra[n]->IsSelected = false;
  scene.clearSelection();
  scene.clearFocus();
  scene.update(this->rect());
}

std::vector<int> CSVGraphicsView::hideExtraSelectedItems() {
  QList<CSVGraphicsPathItem *> extra =
      CSVGraphicsPathItem::extract(scene.items());
  std::vector<int> index;
  for (int n = 0; n < extra.size(); ++n)
    if (extra[n]->IsSelected) {
      index.push_back(extra[n]->data(0).toInt());
      extra[n]->IsSelected = false;
      extra[n]->hide();
    }
  scene.clearSelection();
  scene.clearFocus();
  scene.update(this->rect());
  return index;
}

// MAYBETODO: n^2 algoritmayi iyilestirmek mumkun, gerekirse yap
void CSVGraphicsView::showExtraHiddenItems(std::vector<int> const &items) {
  QList<CSVGraphicsPathItem *> extra =
      CSVGraphicsPathItem::extract(scene.items());
  for (int n = 0; n < extra.count(); ++n) {
    for (std::vector<int>::const_iterator e = items.begin(); e != items.end();
         ++e) {
      if (extra[n]->data(0).toInt() == *e)
        extra[n]->show();
    }
  }
  scene.clearSelection();
  scene.clearFocus();
  scene.update(this->rect());
}
