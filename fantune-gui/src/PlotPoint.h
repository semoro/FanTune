//
// Created by knize on 11.07.16.
//

#ifndef FANTUNE_PLOTPOINT_H
#define FANTUNE_PLOTPOINT_H


#include <qcustomplot.h>

class PlotPoint : public QCPItemEllipse {

    QCPItemTracer *mCenterTracer;
    double xRadius = 15, yRadius = 15;
    int m_index;
public:
    PlotPoint(QCustomPlot *parentPlot);
    ~PlotPoint();

    void moveCenter(double x, double y);
    void countPoint();
    void setIndex(int i);
    int index();
};


#endif //FANTUNE_PLOTPOINT_H
