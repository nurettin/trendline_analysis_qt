/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu Nov 18 00:29:45 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Selection;
    QAction *actionOpen_CSV;
    QAction *actionReset_Windows;
    QAction *actionDelete_Selection;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(920, 570);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionSave_Selection = new QAction(MainWindow);
        actionSave_Selection->setObjectName(QString::fromUtf8("actionSave_Selection"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico/ico/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Selection->setIcon(icon);
        actionOpen_CSV = new QAction(MainWindow);
        actionOpen_CSV->setObjectName(QString::fromUtf8("actionOpen_CSV"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ico/ico/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_CSV->setIcon(icon1);
        actionReset_Windows = new QAction(MainWindow);
        actionReset_Windows->setObjectName(QString::fromUtf8("actionReset_Windows"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ico/ico/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset_Windows->setIcon(icon2);
        actionDelete_Selection = new QAction(MainWindow);
        actionDelete_Selection->setObjectName(QString::fromUtf8("actionDelete_Selection"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ico/ico/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_Selection->setIcon(icon3);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ico/ico/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon4);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ico/ico/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpen_CSV);
        toolBar->addAction(actionSave_Selection);
        toolBar->addAction(actionReset_Windows);
        toolBar->addAction(actionDelete_Selection);
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Line Analyzer", 0, QApplication::UnicodeUTF8));
        actionSave_Selection->setText(QApplication::translate("MainWindow", "Save Selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_Selection->setToolTip(QApplication::translate("MainWindow", "Save Graphics Selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_Selection->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionOpen_CSV->setText(QApplication::translate("MainWindow", "Open CSV", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen_CSV->setToolTip(QApplication::translate("MainWindow", "Opens a CSV File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen_CSV->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionReset_Windows->setText(QApplication::translate("MainWindow", "Reset Windows", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionReset_Windows->setToolTip(QApplication::translate("MainWindow", "Reset Windows", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionReset_Windows->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        actionDelete_Selection->setText(QApplication::translate("MainWindow", "Delete Selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDelete_Selection->setToolTip(QApplication::translate("MainWindow", "Delete Selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDelete_Selection->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
