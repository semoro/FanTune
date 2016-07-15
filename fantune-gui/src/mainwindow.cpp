#include <qcustomplot.h>
#include <FanSelector.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fanpreview.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Fan Tune GNU");

    FanSelector fanSelector;

    fans = QVector<Fan *>::fromStdVector(fanSelector.detectFans());
    QVBoxLayout *wL = (QVBoxLayout *) ui->scrollAreaWidgetContents->layout();
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




