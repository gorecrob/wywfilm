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

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(startCountDown()));
    timer->start(1000);
    //startCountDown();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startCountDown()
{
    int czas = 60;
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if ((time.second() % 2) == 0)
        text[5] = '  ';
    ui->lcdNumber_wywolanie->display(text);

}
