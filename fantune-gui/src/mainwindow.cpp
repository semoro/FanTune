#include <qcustomplot.h>
#include <FanSelector.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fanpreview.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Fan Tune GNU");
    using namespace boost::interprocess;
    FanSelector fanSelector;
    std::vector<Fan *> oFans = fanSelector.detectFans();
    sharedMemoryObject->truncate(oFans.size() * sizeof(Fan));
    size_t size = 0;
    sharedMemoryObject->get_size((offset_t &) size);

    region = new mapped_region(*sharedMemoryObject, boost::interprocess::read_write, 0, size);

    int i = 0;
    for (Fan *fan: oFans) {
        fans.append((Fan *) memcpy(region->get_address() + (i++) * sizeof(Fan), fan, sizeof(Fan)));
        delete fan;
    }

    QVBoxLayout *wL = (QVBoxLayout *)
            ui->scrollAreaWidgetContents->layout();
    //ui->scrollAreaWidgetContents->setWidth();
    for (int i = 0; i < fans.size(); ++i) {
        FanPreview *fanPreview = new FanPreview(fans[i], ui->scrollAreaWidgetContents);
        wL->addWidget(fanPreview);
        connect(this, &MainWindow::updateFanInfo, fanPreview, &FanPreview::updateFanInfo);
    }


    fanUpdate = new QTimer(this);
    connect(fanUpdate, SIGNAL(timeout()), this, SLOT(updateFans()));
    fanUpdate->start(1000);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    QApplication::quit();
}

void MainWindow::updateFans() {
    emit updateFanInfo();
}




