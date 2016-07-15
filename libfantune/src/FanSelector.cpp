//
// Created by semoro on 15.07.16.
//

#include <dirent.h>
#include <functional>
#include <regex>
#include <iostream>
#include "FanSelector.h"


using namespace std;


#define SysFSLoc "/sys/class/hwmon/"

typedef void (*FileCallback)(DIR *, dirent *);

void forEachFile(const char *loc, std::function<void(DIR *, dirent *)> callback) {
    DIR *dirPtr;
    dirent *dirEntryPtr;
    if ((dirPtr = opendir(loc)) != nullptr) {
        while ((dirEntryPtr = readdir(dirPtr)) != nullptr) {
            callback(dirPtr, dirEntryPtr);
        }
        closedir(dirPtr);
    }
}

regex pwmRegex("^pwm([0-9]+)$");
regex fanRegex("^fan([0-9]+)_input$");


struct Device {
    string controllerPath;
    string name;
};

vector<Fan *> FanSelector::detectFans() {


    vector<Device> pwms;
    vector<Device> fans;
    std::vector<Fan *> result;

    forEachFile(SysFSLoc, [&fans, &pwms](DIR *dirPtr, dirent *entryPtr) {
        string mon = SysFSLoc;
        mon += entryPtr->d_name;
        forEachFile(mon.c_str(), [&fans, &pwms, mon](DIR *dirPtr, dirent *entryPtr) {
            string file = entryPtr->d_name;
            Device dev{mon, file};
            if (regex_match(file, fanRegex)) {
                fans.push_back(dev);
            }
            if (regex_match(file, pwmRegex)) {
                pwms.push_back(dev);
            }
        });
    });

    for (auto iter = pwms.begin(); iter != pwms.end(); ++iter) {
        Device pwmDev = (*iter);
        smatch pRes;
        regex_search(pwmDev.name, pRes, pwmRegex);

        for (auto iter1 = fans.begin(); iter1 != fans.end(); ++iter1) {
            Device fanDev = (*iter1);
            if (fanDev.controllerPath == pwmDev.controllerPath) {
                smatch fRes;
                regex_search(fanDev.name, fRes, fanRegex);
                if (fRes[1] == pRes[1]) {
                    string path = (fanDev.controllerPath + "/" + fanDev.name);
                    char *monitorPath = (char *) malloc(path.size());
                    strcpy(monitorPath, path.c_str());

                    path = (pwmDev.controllerPath + "/" + pwmDev.name);
                    char *pwmPath = (char *) malloc(path.size());
                    strcpy(pwmPath, path.c_str());

                    result.push_back(new Fan(monitorPath, pwmPath));
                    break;
                }
            }
        }
    }

    for (auto iter = result.begin(); iter != result.end(); ++iter) {
        Fan *fan = *iter;

        if (fan->getRPM() == 0) {
            iter = result.erase(iter);
            delete fan;
        } else {
            printf("MON: %s\tPWM: %s\n", fan->monitorPath, fan->controlPath);
        }
    }

    return result;
}

std::vector<Fan *> FanSelector::loadFans(std::fstream &file) {
    return std::vector<Fan *>();
}



