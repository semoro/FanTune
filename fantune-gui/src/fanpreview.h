#ifndef FANPREVIEW_H
#define FANPREVIEW_H

#include <QWidget>
#include <Fan.h>

namespace Ui {
    class FanPreview;
}

class FanPreview : public QWidget {
Q_OBJECT

public:
    explicit FanPreview(Fan *fan, QWidget *parent = 0);

    ~FanPreview();

private:
    Fan *fan;
    Ui::FanPreview *ui;

public slots:
    void toggleSwitch();
    void updateFanInfo();
    void setStyles();

    void openSettings();
};

#endif // FANPREVIEW_H
