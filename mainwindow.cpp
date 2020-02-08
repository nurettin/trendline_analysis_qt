#include <vector>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QStatusBar>
#include <QString>
#include <QTextCodec>
#include <csvdeletelinecommand.hpp>
#include <csvgraphicspathitem.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // https://doc.qt.io/qt-5/sourcebreaks.html#changes-to-qtextcodec
  // QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
  QLocale::setDefault(QLocale::Turkish);

  mdi = new QMdiArea(this);
  view = new CSVGraphicsView(mdi);
  txt = new QTextEdit(mdi);
  btxt = new QTextEdit(mdi);
  undoStack = new QUndoStack(this);

  mdi->addSubWindow(view)->setAttribute(Qt::WA_DeleteOnClose, false);
  mdi->addSubWindow(txt)->setAttribute(Qt::WA_DeleteOnClose, false);
  mdi->addSubWindow(btxt)->setAttribute(Qt::WA_DeleteOnClose, false);
  this->setCentralWidget(mdi);
  connect(view, SIGNAL(linesSelected(QRect const &, QList<QVariant> const &)),
          this,
          SLOT(writeSelectionData(QRect const &, QList<QVariant> const &)));
  connect(ui->actionSave_Selection, SIGNAL(triggered()), this,
          SLOT(saveSelectionData()));
  connect(ui->actionOpen_CSV, SIGNAL(triggered()), view, SLOT(loadCSV()));
  connect(ui->actionReset_Windows, SIGNAL(triggered()), this,
          SLOT(resetWindows()));
  connect(ui->actionDelete_Selection, SIGNAL(triggered()), this,
          SLOT(deleteSelectionData()));
  connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
  connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
  this->statusBar()->showMessage(tr("Right-click or space for menu"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void MainWindow::writeSelectionData(QRect const &area,
                                    QList<QVariant> const &data) {
  QString strData;
  // strData.append(QString(tr("Selected Area (x, y, w, h): %1, %2, %3,
  // %4\n")).arg(area.x()).arg(area.y()).arg(area.width()).arg(area.height()));
  for (int n = 0; n < data.count(); ++n)
    strData.append(QString(tr("%1\n")).arg(data[n].toInt()));
  txt->setText(strData);
}

void MainWindow::saveSelectionData() {
  QList<CSVGraphicsPathItem *> items = view->extraSelectedItems();
  if (items.isEmpty())
    return;
  QString fileName;
  try {
    fileName = QFileDialog::getSaveFileName(this, tr("Save Selection"), ".");
    if (fileName == "")
      return;

    qSort(items.begin(), items.end(), CSVGraphicsPathItem::lessThan);
    QByteArray toWrite;
    std::vector<std::vector<double>>::size_type bitpos = 1;
    for (int n = 0; n < items.count(); ++n) {
      for (; bitpos < std::vector<std::vector<double>>::size_type(
                          items[n]->data(0).toInt());
           ++bitpos)
        toWrite.append("0\n");
      toWrite.append("1\n");
      ++bitpos;
    }
    for (; bitpos < view->DataSize; ++bitpos)
      toWrite.append("0\n");

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(toWrite);
    btxt->setText(QString(toWrite));
    if (file.error())
      throw std::runtime_error(file.errorString().toStdString());
  } catch (std::exception &ex) {
    QMessageBox::information(this, tr("Error"), ex.what());
  } catch (...) {
    QMessageBox::information(
        this, tr("Error"),
        QString(tr("Unknown error saving file: %1").arg(fileName)));
  }
}

void MainWindow::resetWindows() {
  view->show();
  txt->show();
  btxt->show();
  view->clearExtraSelectedItems();
  txt->clear();
  btxt->clear();
  // mdi->tileSubWindows();
}

void MainWindow::deleteSelectionData() {
  undoStack->push(new CSVDeleteLineCommand(view, 0));
  //    view->deleteExtraSelectedItems();
}

void MainWindow::undo() { undoStack->undo(); }

void MainWindow::redo() { undoStack->redo(); }
