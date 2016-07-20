#include <qcustomplot.h>
#include <iostream>
#include "settingswidget.h"
#include "ui_settingswidget.h"


SettingsWidget::SettingsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SettingsWidget) {
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget() {
    delete ui;
}

SettingsWidget::SettingsWidget(Fan *fan, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SettingsWidget) {
    ui->setupUi(this);

    setWindowTitle(fan->monitorPath);

    initFanCurvePlot();
    initControlCurvePlot();
    //ui->tabWidget->widget(2)->setDisabled(true);



    connect(ui->pushButton_addPoint, &QPushButton::clicked, this, &SettingsWidget::addPoint);
    connect(ui->cancel, &QPushButton::clicked, [this]() {
        close();
    });
    connect(ui->pushButton_auto, &QPushButton::clicked, this, &SettingsWidget::setGraphToAuto);
    connect(ui->pushButton_fanTest, &QPushButton::clicked, this, &SettingsWidget::plotFanCurve);

}

void SettingsWidget::addPoint() {
    double x, y;
    x = ((*pointsX)[1] + (*pointsX)[2]) / 2;
    y = ((*pointsY)[1] + (*pointsY)[2]) / 2;
    pointsX->insert(2, 1, x);
    pointsY->insert(2, 1, y);

    pointsMarks->insert(2, 1, new PlotPoint(ui->controlCurvePlot));
    (*pointsMarks)[2]->moveCenter((*pointsX)[2], (*pointsY)[2]);
    (*pointsMarks)[2]->setBrush(QBrush(defaultColor));

    ui->controlCurvePlot->graph(0)->setData(*pointsX, *pointsY);
    ui->controlCurvePlot->replot();
}

void SettingsWidget::dragPointFlag(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QMouseEvent *e = event;
        if (!dragFlag) {
            for (int i = 0; i < (*pointsMarks).size(); ++i) {
                if ((*pointsMarks)[i]->selectTest(event->localPos(), false) < 10) {
                    current = (*pointsMarks)[i];
                    current->setBrush(QBrush(dragColor));
                    ui->controlCurvePlot->replot();
                    dragFlag = true;
                    (*currentState).setIndex(i);
                    //TODO Check point mark center position collision.
                }
            }
        }
    }
}


void SettingsWidget::dragPoint(QMouseEvent *event) {
    if (dragFlag) {
        double x, y, checkX, checkY, leftX = 0, rightX = 100;
        int i = (*currentState).index();
        checkX = ui->controlCurvePlot->xAxis->pixelToCoord(event->localPos().x());
        checkY = ui->controlCurvePlot->yAxis->pixelToCoord(event->localPos().y());


        if (i > 1) {
            leftX = (*pointsX)[i - 1];
        }
        if (i < (*pointsX).size() - 1) {
            rightX = (*pointsX)[i + 1];
        }
        if (i == 0 || i == 1) {
            leftX = 0;
            rightX = (*pointsX)[2];
        }

        if (checkX > leftX && checkX < rightX) {
            x = ui->controlCurvePlot->xAxis->pixelToCoord(event->localPos().x());
        }


        if (i == (*pointsX).size() - 1) {
            y = 100;
        } else if (i == 0) {
            y = 0;
        } else if (i == 1 && deadZone > 1) {
            y = deadZone;
        } else if (checkY >= 0 && checkY <= 100) {
            y = ui->controlCurvePlot->yAxis->pixelToCoord(event->localPos().y());
        }
        cPos = QPointF(x, y);
        (*pointsX).replace(i, cPos.x());
        (*pointsY).replace(i, cPos.y());
        current->moveCenter(cPos.x(), cPos.y());
        if (deadZone > 1) {
            if (i == 0) {
                (*pointsX).replace(1, cPos.x() + 0.001);
                (*pointsMarks)[1]->moveCenter(cPos.x() + 0.001, (*pointsY)[1]);

            }
            if (i == 1) {
                (*pointsX).replace(0, cPos.x() - 0.001);
                (*pointsMarks)[0]->moveCenter(cPos.x() - 0.001, (*pointsY)[0]);
            }
        }


        ui->controlCurvePlot->graph(0)->setData(*pointsX, *pointsY);
        ui->controlCurvePlot->replot();
    }
}

void SettingsWidget::setGraphToAuto() {

    delete pointsX;
    delete pointsY;
    for (int j = 0; j < (*pointsMarks).size(); ++j) {
        delete (*pointsMarks)[j];
    }
    delete pointsMarks;
    resetControlCurve();
    ui->controlCurvePlot->replot();
}

void SettingsWidget::initControlCurvePlot() {

    currentState = new PlotPoint(ui->controlCurvePlot);

    connect(ui->controlCurvePlot, &QCustomPlot::mousePress, this, &SettingsWidget::dragPointFlag);
    connect(ui->controlCurvePlot, &QCustomPlot::mouseMove, this, &SettingsWidget::dragPoint);
    connect(ui->controlCurvePlot, &QCustomPlot::mouseRelease, [this]() {
        dragFlag = false;
        if (current)
            current->setBrush(QBrush(defaultColor));
        ui->controlCurvePlot->replot();
    });

    ui->controlCurvePlot->xAxis->setLabel("°C");
    ui->controlCurvePlot->xAxis->setLabelColor(Qt::white);
    ui->controlCurvePlot->xAxis->setRange(0, 100);
    ui->controlCurvePlot->yAxis->setLabel("%");
    ui->controlCurvePlot->yAxis->setLabelColor(Qt::white);
    ui->controlCurvePlot->yAxis->setRange(0, 100);
    initPlotStyle(ui->controlCurvePlot);
    resetControlCurve();
}

void SettingsWidget::initFanCurvePlot() {

    ui->fanCurvePlot->xAxis->setLabel("PWM");
    ui->fanCurvePlot->xAxis->setLabelColor(Qt::white);
    ui->fanCurvePlot->xAxis->setRange(0, 255);

    ui->fanCurvePlot->yAxis->setLabel("RPM");
    ui->fanCurvePlot->yAxis->setLabelColor(Qt::white);

    initPlotStyle(ui->fanCurvePlot);
}

void SettingsWidget::resetControlCurve() {
    pointsX = new QVector<double>(4);
    pointsY = new QVector<double>(4);
    pointsMarks = new QVector<PlotPoint *>(4);

    (*pointsX)[0] = 20;
    (*pointsX)[1] = 20.001;
    (*pointsX)[2] = 60;
    (*pointsX)[3] = 100;

    (*pointsY)[0] = 0;
    (*pointsY)[1] = deadZone > 1 ? deadZone : 20;
    (*pointsY)[2] = 50;
    (*pointsY)[3] = 100;

    ui->controlCurvePlot->addGraph();
    ui->controlCurvePlot->graph(0)->setData(*pointsX, *pointsY);
    ui->controlCurvePlot->graph(0)->setPen(QPen(QBrush(QColor(graphColor)), 3));

    for (int i = 0; i < (*pointsX).size(); ++i) {
        (*pointsMarks)[i] = new PlotPoint(ui->controlCurvePlot);
        (*pointsMarks)[i]->moveCenter((*pointsX)[i], (*pointsY)[i]);
        (*pointsMarks)[i]->setBrush(QBrush(defaultColor));
    }
}

void SettingsWidget::plotFanCurve() {


    std::fstream config("curve_outtake.conf", std::ios::in);
    fanCurve.load(config);
    config.close();

    rpmP = new QVector<double>(256);
    x = new QVector<double>(256);
    for (int i = 0; i < 256; ++i) {
        (*rpmP)[i] = fanCurve.rpmFromPwm(i);
        (*x)[i] = i;
    }

    ui->fanCurvePlot->addGraph();
    ui->fanCurvePlot->graph(0)->setData(*x, *rpmP);
    ui->fanCurvePlot->graph(0)->setPen(QPen(QBrush(QColor(graphColor)), 3));
    ui->fanCurvePlot->rescaleAxes();
    ui->fanCurvePlot->replot();
    deadZone = fanCurve.deadZone() * 100;

}

void SettingsWidget::initPlotStyle(QCustomPlot *customPlot) {
    customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    customPlot->axisRect()->setBackground(axisRectGradient);
}










































