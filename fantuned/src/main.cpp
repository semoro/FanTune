#include <iostream>

using namespace std;


#include <FanTest.h>


#include <signal.h>
#include <FanSelector.h>


Fan *fan1 = nullptr;

void stopTest(int sig) {
    if (fan1 != nullptr) {
        fan1->setManual(false);
    }
    exit(0);
}


int main() {

    signal(SIGINT, stopTest);

    FanSelector fanSelector;
    fanSelector.detectFans();

    return 0;
}