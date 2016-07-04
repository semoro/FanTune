//
// Created by knize on 04.07.16.
//

#ifndef FANTUNE_FANROW_H
#define FANTUNE_FANROW_H


#include <QtWidgets/QProgressBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>

struct FanRow{
    FanRow(QGroupBox *groupBox, QLabel *label, QProgressBar *progressBar, QPushButton *pushButton)
            : m_GroupBox(groupBox),
              m_Label(label),
              m_ProgressBar(progressBar),
              m_PushButton(pushButton)
    {}

    FanRow(void)
            : m_GroupBox(nullptr),
              m_Label(nullptr),
              m_ProgressBar(nullptr),
              m_PushButton(nullptr)
    {}

    QGroupBox *m_GroupBox;
    QLabel *m_Label;
    QProgressBar *m_ProgressBar;
    QPushButton *m_PushButton;
};


#endif //FANTUNE_FANROW_H
