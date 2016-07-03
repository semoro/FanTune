#include <QApplication>
#include <qcustomplot.h>
#include "mainwindow.h"
#include "../../libfantune/includes/FanCurve.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    // setup customPlot as central widget of window:
    QCustomPlot customPlot;
    window.setCentralWidget(&customPlot);
    FanCurve fanCurve;
    std::fstream config("curve_outtake.conf", std::ios::in);
    fanCurve.load(config);
    config.close();
    // create plot (from quadratic plot example):
    QVector<double> x(256), rpmP(256);
    for (int i = 0; i < 256; ++i) {
        rpmP[i] = fanCurve.rpmFromPwm(i);
        x[i] = i;
    }
    customPlot.addGraph();
    customPlot.graph(0)->setData(x, rpmP);
    customPlot.xAxis->setLabel("x");
    customPlot.yAxis->setLabel("y");
    customPlot.rescaleAxes();
    window.show();
    return a.exec();
}