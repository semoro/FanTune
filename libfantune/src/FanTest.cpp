//
// Created by semoro on 02.07.16.
//

#include <zconf.h>
#include <FanTest.h>


void stopFan(Fan *fan) {
    printf("[LOG] PWM 0, waiting fan to lower speed\n");
    fan->setPWM(0);
    sleep(5);
}


FanCurve *FanTest::techCurve(Fan *fan) {
    timespec tw{2, 100 * 1000 * 1000};
    timespec tv;
    stopFan(fan);
    int minRPM = fan->getRPM();
    int startPWM = 0;
    int *RPMs = new int[CURVE_POINTS];
    printf("[LOG] Started curve filling\n");
    for (int i = 0; i < CURVE_POINTS; i++) {
        fan->setPWM(i * PWM_STEP);
        nanosleep(&tw, &tv);
        RPMs[i] = fan->getRPM();
        printf("%d%%,\t PWM: %d,\t RPM: %d\n", (int) (i / 52.0 * 100.0), i * PWM_STEP, fan->rpm);
    }
    int maxRPM = fan->rpm;
    printf("[LOG] Done.\n");

    if (minRPM == 0) {
        for (int i = 0; i < CURVE_POINTS; i++) {
            if (RPMs[i] >= maxRPM + 1000) {
                RPMs[i] = 0;
            }
            if (RPMs[i] > 0 && startPWM == 0) {
                startPWM = i * PWM_STEP;
            }
        }
    }


    FanCurve *result = new FanCurve();
    result->fill(RPMs, minRPM, maxRPM, startPWM);
    return result;
}

CurveTestRecord *FanTest::testCurve(Fan *fan, FanCurve *curve) {
    timespec tw{2, 100 * 1000 * 1000};
    timespec tv;
    stopFan(fan);
    printf("[LOG] Started curve testing\n");
    CurveTestRecord *results = new CurveTestRecord[101];
    for (int i = 0; i <= 100; ++i) {
        double p = i / 100.0;
        int pwm = curve->pwmFromValue(p);
        fan->setPWM(pwm);
        nanosleep(&tw, &tv);
        results[i].rpm = fan->getRPM();
        results[i].targetRPM = curve->targetRPM(p);
        printf("%d%%,\t PWM: %d,\t Target: %lf,\t Real: %d\n", i, pwm, results[i].targetRPM, results[i].rpm);
    }
    printf("[LOG] Done.\n");
    return results;
}



