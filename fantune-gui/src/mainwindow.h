#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "Fan.h"
#include "FansScrollArea.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
QVector<Fan> fans;



public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;

public slots:

};

#endif // MAINWINDOW_H
