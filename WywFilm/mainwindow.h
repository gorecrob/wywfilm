#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int czas_wyw, czas_przer, czas_utrw, czas_pluk, czas_miedzy;
    QTime *time_wyw, *time_przer, *time_utrw, *time_pluk, *time_miedzy;

private:
    Ui::MainWindow *ui;
    QTimer *timer;
   // QTime *time;

    int czas;


    void displayTime();


private slots:
    void startCountDown();
    void stopCountDown();
    void resetCountDown();
    void startDisplay();
};

#endif // MAINWINDOW_H
