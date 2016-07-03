//
// Created by semoro on 02.07.16.
//

#include <cmath>
#include "FanCurve.h"

void FanCurve::fill(int *RPMs, int minRPM, int maxRPM, int startPWM) {
    this->RPMs = RPMs;
    this->minRPM = minRPM;
    this->maxRPM = maxRPM;
    this->startPWM = startPWM;
}

void FanCurve::save(std::fstream &out) {
    out << maxRPM << std::endl;
    out << minRPM << std::endl;
    out << startPWM << std::endl;
    for (int i = 0; i < CURVE_POINTS; i++) {
        out << RPMs[i] << std::endl;
    }
}

void FanCurve::load(std::fstream &in) {

    in >> maxRPM;
    in >> minRPM;
    in >> startPWM;
    RPMs = new int[CURVE_POINTS];
    for (int i = 0; i < CURVE_POINTS; i++) {
        in >> RPMs[i];
    }
}

double FanCurve::targetRPM(double p) {
    return (maxRPM - minRPM) * p + minRPM;
}


int FanCurve::pwmFromValue(double p) {
    double target = targetRPM(p);
    if (target == 0)
        return 0;
    int low, high;
    low = startPWM / PWM_STEP;
    high = CURVE_POINTS - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (RPMs[mid] >= target) {
            high = mid;
        } else {
            low = mid;
        }
    }
    double step = (RPMs[high] - RPMs[low]) / PWM_STEP;
    if (step == 0)
        return low * PWM_STEP;
    return low * PWM_STEP + (int) round((target - RPMs[low]) / step);
}


int FanCurve::rpmFromPwm(int pwm) {

    int low, high;
    low = pwm / PWM_STEP;
    high = std::min((pwm + PWM_STEP) / PWM_STEP, CURVE_POINTS - 1);
    double step = (RPMs[high] - RPMs[low]) / PWM_STEP;
    if (step == 0)
        return RPMs[low];
    int ppwm = pwm % PWM_STEP;
    return ((PWM_STEP - ppwm) * RPMs[low] + ppwm * RPMs[high]) / PWM_STEP;
}

















