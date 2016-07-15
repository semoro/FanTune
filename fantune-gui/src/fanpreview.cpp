#include "fanpreview.h"
#include "ui_fanpreview.h"

FanPreview::~FanPreview() {
    delete ui;
}

FanPreview::FanPreview(Fan *fan, QWidget *parent) :
        QWidget(parent), fan(fan),
        ui(new Ui::FanPreview) {
    ui->setupUi(this);
    ui->groupBox->setTitle(fan->monitorPath);

}

void FanPreview::updateFanInfo() {
    fan->update();
    ui->currRPM->setText(QString::number(fan->rpm));
    this->repaint();
}



