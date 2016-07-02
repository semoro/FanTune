#include <iostream>

using namespace std;


#include <sensors/sensors.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <FanTest.h>


void enumerate(struct udev *udev) {

    udev_enumerate *enumerate;
    udev_list_entry *devices, *dev_list_entry;

    udev_list_entry *sysattrs, *sysattr_list_entry;
    udev_device *dev;
    /* Create a list of the devices in the 'hidraw' subsystem. */
    enumerate = udev_enumerate_new(udev);


    udev_enumerate_add_match_subsystem(enumerate, "hwmon");

    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    /* For each item enumerated, print out its information.
       udev_list_entry_foreach is a macro which expands to
       a loop. The loop will be executed for each member in
       devices, setting dev_list_entry to a list entry
       which contains the device's path in /sys. */
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;

        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);
        printf("Path: %s\n", path);

        sysattrs = udev_device_get_sysattr_list_entry(dev);
        udev_list_entry_foreach(sysattr_list_entry, sysattrs) {
            const char *attributeName;

            attributeName = udev_list_entry_get_name(sysattr_list_entry);
            printf(" Name: %s", attributeName);
            printf("\tValue: %s\n", udev_device_get_sysattr_value(dev, attributeName));

        }
        udev_device_unref(dev);
    }
    /* Free the enumerator object */
    udev_enumerate_unref(enumerate);
}


#include <signal.h>


Fan *fan1 = nullptr;

void stopTest(int sig) { // can be called asynchronously
    if (fan1 != nullptr) {
        fan1->setManual(false);
    }
    exit(0);
}


int main() {

    sensors_init(NULL);
    cout << libsensors_version << endl;


    sensors_chip_name const *cn;
    int c = 0;
    while ((cn = sensors_get_detected_chips(0, &c)) != 0) {
        std::cout << "Chip: " << cn->prefix << "/" << cn->path << std::endl;

        sensors_feature const *feature;
        int f = 0;

        while ((feature = sensors_get_features(cn, &f)) != 0) {
            std::cout << f << ": " << feature->name << std::endl;
        }
    }


    udev *udev;
    udev_device *dev;

    /* Create the udev object */
    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }
    enumerate(udev);

    dev = udev_device_new_from_syspath(udev, "/sys/devices/platform/nct6775.656/hwmon/hwmon2");
    auto base = "/sys/class/hwmon/hwmon2";
    char *mon, *pwm = nullptr;
    asprintf(&mon, "%s/%s", base, "fan2");
    asprintf(&pwm, "%s/%s", base, "pwm2");
    fan1 = new Fan(mon, pwm);

    udev_device_unref(dev);

    FanTest fanTest;

    fan1->setManual(true);
    signal(SIGINT, stopTest);
    FanCurve *curve = fanTest.techCurve(fan1);
    fan1->setManual(false);

    fstream save("curve_cpu.conf", ios::out);
    curve->save(save);
    save.close();



    //FanCurve *curve = new FanCurve();
    fstream conf("curve_cpu.conf", ios::in);
    curve->load(conf);
    conf.close();

    fan1->setManual(true);
    CurveTestRecord *results = fanTest.testCurve(fan1, curve);
    fan1->setManual(false);

    fstream csv("test_cpu.csv", ios::out);
    for (int i = 0; i <= 100; i++) {
        csv << results[i].rpm << "," << results[i].targetRPM << endl;
    }
    csv.close();


    udev_unref(udev);
    return 0;
}