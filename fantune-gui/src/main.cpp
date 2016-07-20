#include <QApplication>
#include <qcustomplot.h>
#include <zconf.h>
#include "mainwindow.h"




int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}