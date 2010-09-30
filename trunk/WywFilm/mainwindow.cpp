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

    timer = new QTimer(this);
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

}

//void MainWindow::stopCountDown()
//{
 //   timer->stop();
//}

void MainWindow::displayTime()
{
    int czas = 60;
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if ((time.second() % 2) == 0)
        text[5] = '  ';
    ui->lcdNumber_wywolanie->display(text);


}
