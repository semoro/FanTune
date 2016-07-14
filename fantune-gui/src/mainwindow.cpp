#include <qcustomplot.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Fan Tune GNU");
    //TODO get fans to vector
    fans.push_back(Fan{"Fan 001", 1488});
    fans.push_back(Fan{"Fan 002", 228});
    fans.push_back(Fan{"Fan 003", 228});
    fans.push_back(Fan{"Fan 004", 228});
    fans.push_back(Fan{"Fan 005", 228});
    fans.push_back(Fan{"Fan 006", 228});

    FansScrollArea* fansArea = new FansScrollArea(this);
    for (int i = 0; i < fans.size(); ++i) {
        fansArea->addRow(fans[i].fanID, fans[i].RPM, fansArea);
    }


    ui->initVerticalLayout->addWidget(fansArea);


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    QApplication::quit();
}


