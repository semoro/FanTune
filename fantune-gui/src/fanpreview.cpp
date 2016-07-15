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

    connect(ui->pushButton, &QPushButton::clicked, this, &FanPreview::openSettings);
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





