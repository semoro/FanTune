#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <Fan.h>
#include "PlotPoint.h"
#include "FanCurve.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

    QVector<double> *rpmP, *x;
    QVector<double> *pointsX, *pointsY;
    QVector<PlotPoint*> *pointsMarks;
    PlotPoint* current;
    PlotPoint* currentState;
    QPointF cPos;
    QCustomPlot* customPlot;
    bool dragFlag = false;
    FanCurve fanCurve;

    QColor defaultColor = Qt::lightGray,
    dragColor = Qt::red,
    graphColor = QColor(92, 170, 21);


public:
    explicit SettingsWidget(QWidget *parent = 0);

    explicit SettingsWidget(Fan *fan, QWidget *parent = 0);
    void addPoint();
    void setGraphToAuto();
    ~SettingsWidget();
public slots:
    void dragPointFlag(QMouseEvent *event);
    void dragPoint(QMouseEvent *event);
private:
    void initSettingsGraph();
    void initFanCurveGraph();
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
