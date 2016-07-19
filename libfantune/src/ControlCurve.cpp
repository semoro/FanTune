//
// Created by semoro on 18.07.16.
//

#include <ControlCurve.h>

double ControlCurve::powerByTemperature(double temperature) {
    ControlCurvePoint *a = nullptr;
    ControlCurvePoint *b = nullptr;
    for (int i = 0; i < pointsCount; ++i) {
        ControlCurvePoint *point = points + i;
        double d = temperature - point->x;
        if (d >= 0 && (a == nullptr || fabs(d) < fabs(temperature - a->x)))
            a = point;
        if (d <= 0 && (b == nullptr || fabs(d) < fabs(temperature - b->x)))
            b = point;
    }
    if (a == b)
        return a->y;
    double mT = temperature - a->x;
    double dT = b->x - a->x;
    double dP = b->y - a->y;
    return dP * (mT / dT) + a->y;
}


bool controlCurvePointCompare(ControlCurvePoint *p1, ControlCurvePoint *p2) {
    if (p1->x > p2->x)
        return true;
    else if (p1->x == p2->x)
        return p1->y > p1->y;
    else
        return false;
}

