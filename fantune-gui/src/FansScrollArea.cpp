//
// Created by knize on 04.07.16.
//

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

#include "FansScrollArea.h"
#include "settingswidget.h"


FansScrollArea::FansScrollArea(QWidget *parent) {
    m_parent = parent;
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

    connect(row.m_PushButton, &QPushButton::clicked, [&row, this](){
        openSettingsWindow(m_FanRows.last().m_GroupBox->title());
    });

    //row.m_GroupBox->setLayout(m_rowLayout);

    m_FanRows.push_back(row);
}

FansScrollArea::~FansScrollArea() {

}

void FansScrollArea::openSettingsWindow(QString fanID) {
    SettingsWidget *settingsWidget = new SettingsWidget(fanID);
    settingsWidget->show();
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose);
}











