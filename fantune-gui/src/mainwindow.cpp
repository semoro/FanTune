#include <qcustomplot.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //TODO get fans to vector
    fans.push_back(Fan{"Fan 001", 1488});
    fans.push_back(Fan{"Fan 002", 228});
    FansScrollArea* fansArea = new FansScrollArea(this);
    for (int i = 0; i < fans.size(); ++i) {
        fansArea->addRow(fans[i].fanID, fans[i].RPM, fansArea);
    }


    ui->initVerticalLayout->addWidget(fansArea);

    //setCentralWidget(fansArea);

/*
    fansHBoxLayout = new QVBoxLayout(this);

    for (int i = 0; i < fans.size(); ++i) {
        layouts.push_back(new QHBoxLayout());
    }
    for (int i = 0; i < fans.size(); ++i) {
        fansHBoxLayout->addLayout(layouts[i]);
        layouts[i]->addWidget(new QGroupBox(fans[i].fanID, this), 0, Qt::AlignCenter);
        QList<QWidget *> list = layouts[i] -> findChildren<QWidget *> ();

        layouts[i]->addWidget(new QLabel("Current RPM", this), 0, Qt::AlignCenter);
        layouts[i]->addWidget(new QProgressBar(this), 0, Qt::AlignCenter);
        layouts[i]->addWidget(new QPushButton("Settings", this), 0, Qt::AlignCenter);

    }
*/
    /*QCustomPlot* customPlot = ui->initScreen;
    // create plot (from quadratic plot example):
    QVector<double> x(101), y(101);
    for (int i = 0; i < 101; ++i) {
        x[i] = i / 50.0 - 1;
        y[i] = x[i] * x[i];
    }
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->rescaleAxes();
     */
}

MainWindow::~MainWindow() {
    delete ui;
}
