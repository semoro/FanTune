#include <QApplication>
#include <qcustomplot.h>
#include "mainwindow.h"
#include "main.h"

boost::interprocess::shared_memory_object *sharedMemoryObject;

void sudoPart() {
    using namespace boost::interprocess;
    if (getuid() == 0) {
        sharedMemoryObject = new shared_memory_object(open_only, "shared_memory", read_write);
        printf("I'am root now!");

        exit(0);
    } else {
        int pid = fork();
        if (pid == 0) {
            char buf[4096];
            ssize_t r = readlink("/proc/self/exe", buf, 4096);
            buf[r] = '\0';
            char *res = (char *) malloc(4096);
            asprintf(&res, "pkexec \"%s\"", buf);
            printf("%s\n", res);
            system(res);
            exit(0);
        }
        sharedMemoryObject = new shared_memory_object(open_or_create, "shared_memory", read_write);
    }
}

int main(int argc, char *argv[]) {

    sudoPart();
    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}