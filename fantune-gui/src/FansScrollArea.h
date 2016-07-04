//
// Created by knize on 04.07.16.
//

#ifndef FANTUNE_FANSSCROLLAREA_H
#define FANTUNE_FANSSCROLLAREA_H


#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include "FanRow.h"

class FansScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit FansScrollArea(QWidget *parent = 0);
    ~FansScrollArea();

    void addRow(QString FanID, int progressBarValue, QWidget* parent); //Use own parameters

private:
    QVBoxLayout *mainLayout;

    QVector<FanRow> m_FanRows;
};


#endif //FANTUNE_FANSSCROLLAREA_H
