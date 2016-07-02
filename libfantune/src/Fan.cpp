//
// Created by semoro on 01.07.16.
//

#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <zconf.h>
#include <cmath>
#include "Fan.h"

void Fan::setPWM(int p) {
    char *s = NULL;
    asprintf(&s, "%d", p);
    setAttr(controlPath, "%s", s);
}


void Fan::update() {
    rpm = (int) (strtol(getAttr(monitorPath, "%s_input"), 0, 10));
}

void Fan::setManual(bool manual) {
    char *val = nullptr;
    asprintf(&val, "%d", manual ? 1 : 5);
    setAttr(controlPath, "%s_enable", val);
    free(val);
}

void Fan::init() {
    controlMode = static_cast<int>(strtol(getAttr(controlPath, "%s_enable"), 0, 10));
    std::cout << "Control mode " << controlMode << std::endl;
}

char *Fan::getAttr(const char *base, const char *form) {
    char *query = NULL;
    asprintf(&query, form, base);
    int fd = open(query, O_RDONLY);
    read(fd, (void *) buf, 4096);
    close(fd);
    free(query);
    return (char *) buf;
}

void Fan::setAttr(const char *base, const char *form, const char *val) {
    char *path = NULL;
    asprintf(&path, form, base);
    int fd = open(path, O_WRONLY);
    if (write(fd, val, strlen(val)) <= 0) {
        fprintf(stderr, "FD write error %d at path: %s\n", errno, path);
    }
    close(fd);
    free(path);
}

int Fan::getRPM() {
    update();
    return rpm;
}


















