#include "fanpreview.h"
#include "ui_fanpreview.h"
#include "settingswidget.h"

FanPreview::~FanPreview() {
    delete ui;
}

FanPreview::FanPreview(Fan *fan, QWidget *parent) :
        QWidget(parent), fan(fan),
        ui(new Ui::FanPreview) {
    ui->setupUi(this);
    ui->groupBox->setTitle(fan->monitorPath);
    setStyles();

    connect(ui->pushButton, &QPushButton::clicked, this, &FanPreview::openSettings);
    connect(ui->horizontalSlider, &QSlider::sliderPressed, this, &FanPreview::toggleSwitch);
}

void FanPreview::updateFanInfo() {
    fan->update();
    ui->currRPM->setText(QString::number(fan->rpm));
    this->repaint();
}

void FanPreview::openSettings() {
    SettingsWidget *settingsWidget = new SettingsWidget(fan);
    settingsWidget->show();
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose);
}

void FanPreview::toggleSwitch() {

    if(ui->horizontalSlider->value() == 0) {
        ui->horizontalSlider->setValue(1);
        ui->horizontalSlider->setProperty("toggle", "true");

    }
    else {
        ui->horizontalSlider->setValue(0);
        ui->horizontalSlider->setProperty("toggle", "false");
    }
    ui->horizontalSlider->style()->unpolish(ui->horizontalSlider);
    ui->horizontalSlider->style()->polish(ui->horizontalSlider);
    ui->horizontalSlider->update();
}

void FanPreview::setStyles() {
    setStyleSheet("QSlider::groove:horizontal[toggle = \"true\"]{  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2a6e29, stop:1 #0a4e08);} "
                  "QSlider[toggle = \"false\"]{ background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);}");
}









