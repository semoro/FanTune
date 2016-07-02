//
// Created by semoro on 01.07.16.
//

#ifndef FANTUNE_FAN_H
#define FANTUNE_FAN_H


#include <sensors/sensors.h>
#include <libudev.h>

class Fan {


private:
    const char *monitorPath;
    const char *controlPath;
    char buf[4096];
    int controlMode;

    char *getAttr(const char *base, const char *form);

    void setAttr(const char *base, const char *form, const char *val);


public:

    void setPWM(int p);

    void setManual(bool manual);

    int getRPM();

    void init();

    Fan(const char *monitorPath, const char *controlPath) :
            monitorPath(monitorPath),
            controlPath(controlPath) { }

    ~Fan() {

    }

    int rpm = 0;

    void update();


};


#endif //FANTUNE_FAN_H
