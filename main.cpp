#include "mainwindow.hpp"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QTranslator translator;
  translator.load("trendline_analiz_qt_tr");
  a.installTranslator(&translator);
  MainWindow w;
  w.show();
  return a.exec();
}
