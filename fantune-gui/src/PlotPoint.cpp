//
// Created by knize on 11.07.16.
//

#include "PlotPoint.h"

PlotPoint::PlotPoint(QCustomPlot *parentPlot) : QCPItemEllipse(parentPlot) {
    mCenterTracer = new QCPItemTracer(parentPlot);
    countPoint();


}

void PlotPoint::moveCenter(double x, double y) {
    mCenterTracer->position->setCoords(x, y);
    //topLeft->setParentAnchor(mCenterTracer->position);
    //bottomRight->setParentAnchor(mCenterTracer->position);
}

void PlotPoint::countPoint() {
    mCenterTracer->setStyle(QCPItemTracer::tsNone);

    topLeft->setParentAnchor(mCenterTracer->position);
    bottomRight->setParentAnchor(mCenterTracer->position);

    topLeft->setCoords(-xRadius/2.0, -yRadius/2.0);
    bottomRight->setCoords(xRadius/2.0, yRadius/2.0);

    //topLeft->setType(QCPItemPosition::ptAbsolute);
    //bottomRight->setType(QCPItemPosition::ptAbsolute);
}

PlotPoint::~PlotPoint() {
    delete mCenterTracer;
    mCenterTracer = nullptr;
}

void PlotPoint::setIndex(int i) {
    m_index = i;
}

int PlotPoint::index() {
    return m_index;
}











