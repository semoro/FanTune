//
// Created by semoro on 02.07.16.
//

#ifndef FANTUNE_FANCURVE_H
#define FANTUNE_FANCURVE_H


#include <fstream>
#include "Fan.h"

#define PWM_STEP 5
#define CURVE_POINTS 255 / PWM_STEP + 1

class FanCurve {
private:
    int *RPMs;
    int minRPM = 0;
    int maxRPM = 0;
    int startPWM = 0;

public:
    double targetRPM(double p);


    int getMinRPM() const {
        return minRPM;
    }

    int getMaxRPM() const {
        return maxRPM;
    }

    int getStartPWM() const {
        return startPWM;
    }

    bool isStopable() {
        return startPWM != 0;
    }

    void save(std::fstream &out);

    void load(std::fstream &in);

    int rpmFromPwm(int pwm);

    int pwmFromValue(double p);

    double deadZone();

    void fill(int *RPMs, int minRPM, int maxRPM, int startPWM);
};

#endif //FANTUNE_FANCURVE_H
