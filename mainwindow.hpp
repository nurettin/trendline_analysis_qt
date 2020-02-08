#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <set>

#include <QMainWindow>
#include <QRubberBand>
#include <QMenu>
#include <QTextEdit>
#include <QMdiArea>
#include <QUndoStack>
#include <QAction>
#include "csvgraphicsview.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *);

private:
    Ui::MainWindow *ui;
    QMdiArea* mdi;
    CSVGraphicsView* view;
    QTextEdit* txt;
    QTextEdit* btxt;
    QUndoStack* undoStack;
    QAction* actionUndo;
    QAction* actionRedo;

private slots:
    void deleteSelectionData();
    void writeSelectionData(QRect const &, QList<QVariant> const &);
    void saveSelectionData();
    void resetWindows();
    void undo();
    void redo();
};

#endif // MAINWINDOW_HPP
