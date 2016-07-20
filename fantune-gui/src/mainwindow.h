#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <boost/interprocess/mapped_region.hpp>
#include "Fan.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
    QVector<Fan *> fans;
    QTimer *fanUpdate;
    boost::interprocess::mapped_region *region;


public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;

public slots:

    void updateFans();

signals:

    void updateFanInfo();
};

#endif // MAINWINDOW_H
