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

    //audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    //metaInformationResolver = new Phonon::MediaObject(this);

    getTimes();

    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_wyw);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_wywolanie->display(text);

    czas_disp = czas_disp.addSecs(-czas_wyw + czas_przer);
    text = czas_disp.toString("mm:ss");
    ui->lcdNumber_przerywanie->display(text);

    czas_disp = czas_disp.addSecs(-czas_przer + czas_utrw);
    text = czas_disp.toString("mm:ss");
    ui->lcdNumber_utrwalanie->display(text);

    czas_disp = czas_disp.addSecs(-czas_utrw + czas_pluk);
    text = czas_disp.toString("mm:ss");
    ui->lcdNumber_plukanie->display(text);

    setTextHowto();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete time_wyw;
    delete time_miedzy;
    delete time_pluk;
    delete time_przer;
    delete time_utrw;

    delete ui;
}


void MainWindow::startCountDown()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(startDisplay()));

    if (!timer->isActive())
    {
        timer->start(1000);
    }
    *time_wyw = QTime::currentTime();
    int temp_czas = 0;
    if (czas_wyw > 0 && czas_przer > 0 && czas_utrw > 0 && czas_pluk > 0)
    {
        temp_czas =  czas_wyw + czas_przer + czas_utrw + czas_pluk;
    }
    else if (czas_wyw <= 0 && czas_przer > 0 && czas_utrw > 0 && czas_pluk > 0)
    {
        temp_czas =  czas_przer + czas_utrw + czas_pluk;;
    }
    else if (czas_wyw <= 0 && czas_przer <= 0 && czas_utrw > 0 && czas_pluk > 0)
    {
        temp_czas =  czas_utrw + czas_pluk;;
    }
    else if (czas_wyw <= 0 && czas_przer <= 0 && czas_utrw <= 0 && czas_pluk > 0)
    {
        temp_czas =  czas_pluk;
    }

    *time_wyw = time_wyw->addSecs(temp_czas);

    startDisplay();

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
   ui->pushButtonWywUp->setDisabled(false);
   ui->pushButtonWywDown->setDisabled(false);
   ui->pushButtonPrzerUp->setDisabled(false);
   ui->pushButtonPrzerDown->setDisabled(false);
   ui->pushButtonUtrwUp->setDisabled(false);
   ui->pushButtonUtrwDown->setDisabled(false);
   ui->pushButtonPlukUp->setDisabled(false);
   ui->pushButtonPlukDown->setDisabled(false);
}

void MainWindow::resetCountDown()
{

        getTimes();

        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_wyw);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_wywolanie->display(text);

        czas_disp = czas_disp.addSecs(-czas_wyw + czas_przer);
        text = czas_disp.toString("mm:ss");
        ui->lcdNumber_przerywanie->display(text);

        czas_disp = czas_disp.addSecs(-czas_przer + czas_utrw);
        text = czas_disp.toString("mm:ss");
        ui->lcdNumber_utrwalanie->display(text);

        czas_disp = czas_disp.addSecs(-czas_utrw + czas_pluk);
        text = czas_disp.toString("mm:ss");
        ui->lcdNumber_plukanie->display(text);

}

void MainWindow::displayTime()
{
    if ( czas_wyw > 0 && czas_przer > 0 && czas_utrw > 0 && czas_pluk > 0 )
    {
        czas_wyw--;
        QTime time_disp = QTime(0,0,0,0);
        time_disp = time_disp.addSecs(czas_wyw);
        QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
        ui->lcdNumber_wywolanie->display(text);
        ui->pushButtonWywUp->setDisabled(true);
        ui->pushButtonWywDown->setDisabled(true);

    }
    else if ( czas_wyw <= 0 && czas_przer > 0 && czas_utrw > 0 && czas_pluk > 0 )
    {
        czas_przer--;
        QTime time_disp = QTime(0,0,0,0);
        time_disp = time_disp.addSecs(czas_przer);
        QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
        ui->lcdNumber_przerywanie->display(text);
        ui->pushButtonPrzerUp->setDisabled(true);
        ui->pushButtonPrzerDown->setDisabled(true);

    }
    else if ( czas_wyw <= 0 && czas_przer <= 0 && czas_utrw > 0 && czas_pluk > 0 )
    {
        czas_utrw--;
        QTime time_disp = QTime(0,0,0,0);
        time_disp = time_disp.addSecs(czas_utrw);
        QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
        ui->lcdNumber_utrwalanie->display(text);
        ui->pushButtonUtrwUp->setDisabled(true);
        ui->pushButtonUtrwDown->setDisabled(true);

    }
    else if ( czas_wyw <= 0 && czas_przer <= 0 && czas_utrw <= 0 && czas_pluk > 0 )
    {
        czas_pluk--;
        QTime time_disp = QTime(0,0,0,0);
        time_disp = time_disp.addSecs(czas_pluk);
        QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
        ui->lcdNumber_plukanie->display(text);
        ui->pushButtonPlukUp->setDisabled(true);
        ui->pushButtonPlukDown->setDisabled(true);

    }
    else
    {
        timer->stop();
        ui->startButton->setDisabled(false);
        ui->stopButton->setDisabled(true);
        ui->resetButton->setDisabled(false);
        ui->pushButtonWywUp->setDisabled(false);
        ui->pushButtonWywDown->setDisabled(false);
        ui->pushButtonPrzerUp->setDisabled(false);
        ui->pushButtonPrzerDown->setDisabled(false);
        ui->pushButtonUtrwUp->setDisabled(false);
        ui->pushButtonUtrwDown->setDisabled(false);
        ui->pushButtonPlukUp->setDisabled(false);
        ui->pushButtonPlukDown->setDisabled(false);
    }

}


void MainWindow::startDisplay()
{
    displayTime();

}

void MainWindow::getTimes()
{
    czas_wyw = 1*60;
    czas_przer = 30;
    czas_utrw = 30;
    czas_pluk = 20;
    czas_miedzy = 10;
}

void MainWindow::wywTimeUp()
{
    if ( czas_wyw < 3595 )
    {
        czas_wyw += 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_wyw);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_wywolanie->display(text);
    }
}

void MainWindow::wywTimeDown()
{
    if ( czas_wyw >= 5 )
    {
        czas_wyw -= 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_wyw);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_wywolanie->display(text);
    }
}

void MainWindow::przerTimeUp()
{
    if ( czas_przer < 3595 )
    {
        czas_przer += 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_przer);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_przerywanie->display(text);
    }
}

void MainWindow::przerTimeDown()
{
    if ( czas_przer >= 5 )
    {
        czas_przer -= 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_przer);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_przerywanie->display(text);
    }
}
void MainWindow::utrwTimeUp()
{
    if ( czas_utrw < 3595 )
    {
        czas_utrw += 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_utrw);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_utrwalanie->display(text);
    }
}

void MainWindow::utrwTimeDown()
{
    if ( czas_utrw >= 5 )
    {
        czas_utrw -= 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_utrw);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_utrwalanie->display(text);
    }
}
void MainWindow::plukTimeUp()
{
    if ( czas_pluk < 3595 )
    {
        czas_pluk += 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_pluk);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_plukanie->display(text);
    }
}

void MainWindow::plukTimeDown()
{
    if ( czas_pluk >= 5 )
    {
        czas_pluk -= 5;
        QTime czas_disp = QTime(0,0,0,0);
        czas_disp = czas_disp.addSecs(czas_pluk);
        QString text = czas_disp.toString("mm:ss");
        ui->lcdNumber_plukanie->display(text);
    }
}

void MainWindow::setTextHowto()
{
    QString text;
    text = trUtf8("1. Wlej wywoływacz<br>2. Włącz czas<br>3. Uderz dnem o coś twardego, tak aby powietrze zgromadzone wokół filmu oderwało się<br>4. Pilnując czasu wykonaj 10 obrotów koreksem co minutę<br>5. 10 sekund przed końcem czasu zacznij wylewać wywoływacz<br>6. Jeżeli wywoływacz jest wielokrotnego użytku odlej go do pojemnika w którym go przechowujesz");
    ui->textBrowser_wyw->setText(text);

    text = trUtf8("1. Wlewaj wodę do koreksu przez około 5 minut<br>2. Niech się spokojnie przelewa<br>3. Woda powinna też mieć około 20 stopni, po prostu letnia z kranu");
    ui->textBrowser_przer->setText(text);

    text = trUtf8("1. Wlej utrwalacz, może być „pod korek”<br>2. Uderz dnem koreksu o coś twardego<br>3. Wykonaj 10 przewrotów koreksem<br>4. Pod koniec znowu zrób 10 przewrotów koreksem<br>5. Jeżeli utrwalacz jest stosunkowo nowy w zupełności wystarczy 10 minut<br>6. Wylej utrwalacz<br>7. Teraz możesz odkręcić koreks");
    ui->textBrowser_utrw->setText(text);

    text = trUtf8("1. Płucz przez około 20 minut bieżącą letnią wodą<br>2. Na koniec do pełnego wody koreksu dodaj odrobinę płynu do mycia naczyń<br>3. Zakręć kilka razy spiralą");
    ui->textBrowser_pluk->setText(text);
}
