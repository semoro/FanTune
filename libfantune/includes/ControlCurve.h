//
// Created by semoro on 18.07.16.
//

#ifndef FANTUNE_CONTROLCURVE_H
#define FANTUNE_CONTROLCURVE_H

#include <cmath>

typedef struct {
    double x; // Temperature
    double y; // Power
} ControlCurvePoint;

bool controlCurvePointCompare(ControlCurvePoint *p1, ControlCurvePoint *p2);

class ControlCurve {
public:
    double powerByTemperature(double temperature);

    ControlCurvePoint *points = nullptr; // must be sorted using controlCurvePointCompare
    unsigned long pointsCount = 0;
};

#endif //FANTUNE_CONTROLCURVE_H
