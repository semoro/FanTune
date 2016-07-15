//
// Created by semoro on 02.07.16.
//

#ifndef FANTUNE_FANTEST_H
#define FANTUNE_FANTEST_H


#include "FanCurve.h"

typedef struct {
    int rpm;
    double targetRPM;
} CurveTestRecord;

typedef void (*ProgressCallback)(double);

class FanTest {
public:
    FanCurve *techCurve(Fan *fan, ProgressCallback callback);

    CurveTestRecord *testCurve(Fan *fan, FanCurve *curve);
};


#endif //FANTUNE_FANTEST_H
