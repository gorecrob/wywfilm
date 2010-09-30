#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setLayout(ui->gridLayout);
    ui->stopButton->setDisabled(true);
    timer = new QTimer(this);
    czas = 300;
    connect(timer, SIGNAL(timeout()), this, SLOT(startCountDown()));

    //startCountDown();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startCountDown()
{
    timer->start(1000);
    displayTime();
    ui->resetButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
    ui->startButton->setDisabled(true);
}

void MainWindow::stopCountDown()
{
   timer->stop();
   ui->resetButton->setDisabled(false);
   ui->stopButton->setDisabled(true);
   ui->startButton->setDisabled(false);
}

void MainWindow::resetCountDown()
{
    if ( !timer->isActive())
        ui->lcdNumber_wywolanie->display("0");

}

void MainWindow::displayTime()
{
    czas = 15000;
    QTime time = QTime::currentTime();
    int test = time.elapsed();
    if (test <= czas )
    {
        QString text = time.toString("hh:mm:ss");
            if ((time.second() % 2) == 0)
                text[5] = '  ';
        ui->lcdNumber_wywolanie->display(text);
        ui->lcdNumber_przerywanie->display(time.elapsed());

    }
    else
    {
        timer->stop();
        ui->startButton->setDisabled(false);
        ui->stopButton->setDisabled(true);
        ui->resetButton->setDisabled(false);
        ui->lcdNumber_przerywanie->display(time.elapsed());
    }
    ui->lcdNumber_przerywanie->display(time.elapsed());

}
