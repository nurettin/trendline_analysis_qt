# -------------------------------------------------
# Project created by QtCreator 2010-06-24T21:16:30
# -------------------------------------------------
QT += widgets gui
TARGET = trendline_analiz_qt
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    csvgraphicsview.cpp \
    csvgraphicspathitem.cpp \
    csvdeletelinecommand.cpp
HEADERS += mainwindow.hpp \
    CSVOkuyucu.hpp \
    Matematik.hpp \
    csvgraphicsview.hpp \
    csvgraphicspathitem.hpp \
    csvdeletelinecommand.hpp
FORMS += mainwindow.ui
TRANSLATIONS = trendline_analiz_qt_tr.ts
CODECFORTR = UTF-8
CODECFORSRC = UTF-8
RESOURCES += trendline_analiz_qt.qrc
