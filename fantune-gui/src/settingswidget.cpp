#include <qcustomplot.h>
#include <iostream>
#include "settingswidget.h"
#include "ui_settingswidget.h"
#include "../../libfantune/includes/FanCurve.h"

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

    initFanCurveGraph();
    initSettingsGraph();

    connect(customPlot, &QCustomPlot::mousePress, this, &SettingsWidget::dragPointFlag);
    connect(customPlot, &QCustomPlot::mouseMove, this, &SettingsWidget::dragPoint);
    connect(customPlot, &QCustomPlot::mouseRelease, [this]() {
        dragFlag = false;
        if(current)
            current->setBrush(QBrush(defaultColor));
        customPlot->replot();
    });
    connect(ui->pushButton_addPoint, &QPushButton::clicked, this, &SettingsWidget::addPoint);
    connect(ui->cancel, &QPushButton::clicked, [this]() {
        close();
    });
    connect(ui->pushButton_auto, &QPushButton::clicked, this, &SettingsWidget::setGraphToAuto);

}

void SettingsWidget::addPoint() {
    double x, y;
    x = ((*pointsX)[1] + (*pointsX)[2]) / 2;
    y = ((*pointsY)[1] + (*pointsY)[2]) / 2;
    pointsX->insert(2, 1, x);
    pointsY->insert(2, 1, y);

    pointsMarks->insert(2, 1, new PlotPoint(customPlot));
    (*pointsMarks)[2]->moveCenter((*pointsX)[2], (*pointsY)[2]);
    (*pointsMarks)[2]->setBrush(QBrush(defaultColor));

    customPlot->graph(0)->setData(*pointsX, *pointsY);
    customPlot->replot();
}

void SettingsWidget::dragPointFlag(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QMouseEvent *e = event;
        if (!dragFlag) {
            for (int i = 0; i < (*pointsMarks).size(); ++i) {
                if ((*pointsMarks)[i]->selectTest(event->localPos(), false) < 10) {
                    current = (*pointsMarks)[i];
                    current->setBrush(QBrush(dragColor));
                    customPlot->replot();
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
        checkX = customPlot->xAxis->pixelToCoord(event->localPos().x());
        checkY = customPlot->yAxis->pixelToCoord(event->localPos().y());

        if (currentState->index() == (*pointsX).size() - 1) {
            x = 100;
        } else if (currentState->index() == 0) {
            x = 0;
        } else {
            if(i>0)
                leftX = (*pointsX)[i-1];
            if(i < (*pointsX).size() - 1)
                rightX = (*pointsX)[i+1];
            if (checkX > leftX && checkX < rightX) {
                x = customPlot->xAxis->pixelToCoord(event->localPos().x());
            }
        }

        if (checkY >= 0 && checkY <= 100) {
            y = customPlot->yAxis->pixelToCoord(event->localPos().y());
        }
        cPos = QPointF(x, y);
        (*pointsX).replace(i, cPos.x());
        (*pointsY).replace(i, cPos.y());
        current->moveCenter(cPos.x(), cPos.y());
        customPlot->graph(0)->setData(*pointsX, *pointsY);
        customPlot->replot();
    }
}

void SettingsWidget::setGraphToAuto() {

    delete pointsX;
    delete pointsY;
    for (int j = 0; j < (*pointsMarks).size(); ++j) {
        delete (*pointsMarks)[j];
    }
    delete pointsMarks;


    pointsX = new QVector<double>(4);
    pointsY = new QVector<double>(4);
    pointsMarks = new QVector<PlotPoint *>(4);

    (*pointsX)[0] = 0;
    (*pointsX)[1] = 40;
    (*pointsX)[2] = 60;
    (*pointsX)[3] = 100;

    (*pointsY)[0] = 20;
    (*pointsY)[1] = 20;
    (*pointsY)[2] = 50;
    (*pointsY)[3] = 80;

    customPlot->graph(0)->setData(*pointsX, *pointsY);
    for (int i = 0; i < (*pointsX).size(); ++i) {
        (*pointsMarks)[i] = new PlotPoint(customPlot);
        (*pointsMarks)[i]->moveCenter((*pointsX)[i], (*pointsY)[i]);
        (*pointsMarks)[i]->setBrush(QBrush(defaultColor));
    }
    customPlot->replot();
}

void SettingsWidget::initSettingsGraph() {
    customPlot = ui->controlCurveEdit;
    currentState = new PlotPoint(customPlot);


    pointsX = new QVector<double>(4);
    pointsY = new QVector<double>(4);
    pointsMarks = new QVector<PlotPoint *>(4);

    (*pointsX)[0] = 0;
    (*pointsX)[1] = 40;
    (*pointsX)[2] = 60;
    (*pointsX)[3] = 100;

    (*pointsY)[0] = 20;
    (*pointsY)[1] = 20;
    (*pointsY)[2] = 50;
    (*pointsY)[3] = 80;

    customPlot->addGraph();
    customPlot->graph(0)->setData(*pointsX, *pointsY);
    customPlot->graph(0)->setPen(QPen(QBrush(QColor(graphColor)), 3));

    for (int i = 0; i < (*pointsX).size(); ++i) {
        (*pointsMarks)[i] = new PlotPoint(customPlot);
        (*pointsMarks)[i]->moveCenter((*pointsX)[i], (*pointsY)[i]);
        (*pointsMarks)[i]->setBrush(QBrush(defaultColor));
    }

    customPlot->xAxis->setLabel("°C");
    customPlot->xAxis->setLabelColor(Qt::white);
    customPlot->xAxis->setRange(0, 100);
    customPlot->yAxis->setLabel("%");
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->setRange(0, 100);

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

void SettingsWidget::initFanCurveGraph() {
    QCustomPlot *customPlot = ui->fanCurveDisplay;

    FanCurve fanCurve;
    std::fstream config("curve_outtake.conf", std::ios::in);
    fanCurve.load(config);
    config.close();

    rpmP = new QVector<double>(256);
    x = new QVector<double>(256);
    for (int i = 0; i < 256; ++i) {
        (*rpmP)[i] = fanCurve.rpmFromPwm(i);
        (*x)[i] = i;
    }

    customPlot->addGraph();
    customPlot->graph(0)->setData(*x, *rpmP);
    customPlot->graph(0)->setPen(QPen(QBrush(QColor(graphColor)), 3));
    customPlot->xAxis->setLabel("PWM");
    customPlot->xAxis->setLabelColor(Qt::white);
    customPlot->yAxis->setLabel("RPM");
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->rescaleAxes();



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

void SettingsWidget::getFanCurve() {

}






































