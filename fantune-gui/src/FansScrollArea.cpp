//
// Created by knize on 04.07.16.
//

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include "FansScrollArea.h"


FansScrollArea::FansScrollArea(QWidget *parent) {
    setWidget(new QWidget);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    mainLayout = new QVBoxLayout(this);
    //m_rowLayout  = new QHBoxLayout();



    widget()->setLayout(mainLayout);

    //mainLayout->addLayout(m_rowLayout);

}

void FansScrollArea::addRow(QString FanID, int progressBarValue, QWidget* parent) {
    QHBoxLayout *rowLayout = new QHBoxLayout();
    QGroupBox *pGroupBox = new QGroupBox(FanID, parent);
    QLabel *pLabel = new QLabel("Current RPM", pGroupBox);
    QProgressBar *pProgressBar = new QProgressBar(pGroupBox);
    QPushButton *pPushButton = new QPushButton("Settings", pGroupBox);
    pProgressBar->setRange(0, 2000);
    pProgressBar->setValue(progressBarValue);
    pProgressBar->setTextVisible(true);

    pGroupBox->setLayout(rowLayout);

    rowLayout->addWidget(pLabel);
    rowLayout->addWidget(pProgressBar);
    rowLayout->addWidget(pPushButton);

    mainLayout->addWidget(pGroupBox);


    FanRow row;

    row.m_GroupBox = pGroupBox;
    row.m_Label = pLabel;
    row.m_ProgressBar = pProgressBar;
    row.m_PushButton = pPushButton;

    //row.m_GroupBox->setLayout(m_rowLayout);

    m_FanRows.push_back(row);
}

FansScrollArea::~FansScrollArea() {

}









