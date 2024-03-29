#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QResource>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setLayout(ui->gridLayout);
    ui->stopButton->setDisabled(true);

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);
    autoRepeatInt=100;

    ui->pushButtonWywUp->setAutoRepeat(true);
    ui->pushButtonWywUp->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonWywDown->setAutoRepeat(true);
    ui->pushButtonWywDown->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonPrzerUp->setAutoRepeat(true);
    ui->pushButtonPrzerUp->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonPrzerDown->setAutoRepeat(true);
    ui->pushButtonPrzerDown->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonUtrwUp->setAutoRepeat(true);
    ui->pushButtonUtrwUp->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonUtrwDown->setAutoRepeat(true);
    ui->pushButtonUtrwDown->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonPlukUp->setAutoRepeat(true);
    ui->pushButtonPlukUp->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->pushButtonPlukDown->setAutoRepeat(true);
    ui->pushButtonPlukDown->setToolTip(trUtf8("Przytrzymaj aby szybciej przewijać czas"));
    ui->startButton->setToolTip(trUtf8("Start"));
    ui->stopButton->setToolTip(trUtf8("Stop"));
    ui->resetButton->setToolTip(trUtf8("Reset czasów"));

    mediaObject->setTickInterval(1000);

    Phonon::createPath(mediaObject, audioOutput);

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

    addVoiceFiles();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addVoiceFiles()
{
    QStringList files;
    files.append( "./voice/wywrozp_0001.mp3");
    files.append( "./voice/wywkoniec_0001.mp3");
    files.append( "./voice/przerroz_0001.mp3");
    files.append( "./voice/przerkon_0001.mp3");
    files.append( "./voice/utrroz_0001.mp3");
    files.append( "./voice/utrzak_0001.mp3");
    files.append( "./voice/plukroz_0001.mp3");
    files.append( "./voice/plukzak_0001.mp3");
    files.append( "./voice/koreks_0001.mp3");
    files.append( "./voice/pik.mp3");

    foreach (QString string, files )
    {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
}



void MainWindow::startCountDown()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(startDisplay()));

    if (!timer->isActive())
    {
        timer->start(1000);
    }
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
        if ( czas_start == 2 )
        {
            czas_start--;
            mediaObject->setCurrentSource(sources[0]);
            mediaObject->play();
        }
        else
        {
            czas_wyw--;
            if ( czas_wyw % 60 == 0 && czas_wyw != 0  )
            {
                mediaObject->setCurrentSource(sources[8]);
                mediaObject->play();
            }
            if ( czas_wyw == 10 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }

            if ( czas_wyw == 3 )
            {
                mediaObject->setCurrentSource(sources[1]);
                mediaObject->play();
            }


            QTime time_disp = QTime(0,0,0,0);
            time_disp = time_disp.addSecs(czas_wyw);
            QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
            ui->lcdNumber_wywolanie->display(text);
            ui->pushButtonWywUp->setDisabled(true);
            ui->pushButtonWywDown->setDisabled(true);
        }

    }
    else if ( czas_wyw <= 0 && czas_przer > 0 && czas_utrw > 0 && czas_pluk > 0 )
    {
        if ( czas_miedzy1 > 0 )
        {
            if ( czas_miedzy1 > 1 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }
            czas_miedzy1--;
            if ( czas_miedzy1 == 1 )
            {
                mediaObject->setCurrentSource(sources[2]);
                mediaObject->play();
            }

        }
        else
        {
            czas_przer--;
            if ( czas_przer == 10 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }

            if ( czas_przer == 2 )
            {
                mediaObject->setCurrentSource(sources[3]);
                mediaObject->play();
            }
            QTime time_disp = QTime(0,0,0,0);
            time_disp = time_disp.addSecs(czas_przer);
            QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
            ui->lcdNumber_przerywanie->display(text);
            ui->pushButtonPrzerUp->setDisabled(true);
            ui->pushButtonPrzerDown->setDisabled(true);

        }
    }
    else if ( czas_wyw <= 0 && czas_przer <= 0 && czas_utrw > 0 && czas_pluk > 0 )
    {
        if ( czas_miedzy2 > 0 )
        {
            if ( czas_miedzy2 > 1 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }
            czas_miedzy2--;
            if ( czas_miedzy2 == 1 )
            {
                mediaObject->setCurrentSource(sources[4]);
                mediaObject->play();
            }

        }
        else
        {
            czas_utrw--;
            if ( czas_utrw == 30 )
            {
                mediaObject->setCurrentSource(sources[8]);
                mediaObject->play();
            }
            if ( czas_utrw == 10 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }

            if ( czas_utrw == 2 )
            {
                mediaObject->setCurrentSource(sources[5]);
                mediaObject->play();
            }
            QTime time_disp = QTime(0,0,0,0);
            time_disp = time_disp.addSecs(czas_utrw);
            QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
            ui->lcdNumber_utrwalanie->display(text);
            ui->pushButtonUtrwUp->setDisabled(true);
            ui->pushButtonUtrwDown->setDisabled(true);
        }

    }
    else if ( czas_wyw <= 0 && czas_przer <= 0 && czas_utrw <= 0 && czas_pluk > 0 )
    {
        if ( czas_miedzy3 > 0 )
        {
            if ( czas_miedzy3 > 1 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }
            czas_miedzy3--;
            if ( czas_miedzy3 == 1 )
            {
                mediaObject->setCurrentSource(sources[6]);
                mediaObject->play();
            }

        }
        else
        {
            czas_pluk--;
            if ( czas_pluk == 10 )
            {
                mediaObject->setCurrentSource(sources[9]);
                mediaObject->play();
            }

            if ( czas_pluk == 2 )
            {
                mediaObject->setCurrentSource(sources[7]);
                mediaObject->play();
            }
            QTime time_disp = QTime(0,0,0,0);
            time_disp = time_disp.addSecs(czas_pluk);
            QString text = time_disp.toString("mm:ss");
            if ((time_disp.second() % 2) != 0)
                text[2] = '  ';
            ui->lcdNumber_plukanie->display(text);
            ui->pushButtonPlukUp->setDisabled(true);
            ui->pushButtonPlukDown->setDisabled(true);
        }
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
    czas_wyw = 7*60;
    czas_przer = 5*60;
    czas_utrw = 8*60;
    czas_pluk = 20*60;
    czas_start = 2;
    czas_miedzy1 = czas_miedzy2 = czas_miedzy3 = 10;
}

void MainWindow::wywTimeUp()
{
    if ( czas_wyw > 3600 )
    {
        czas_wyw = 0;
    }
    czas_wyw += 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_wyw);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_wywolanie->display(text);
    if(ui->pushButtonWywUp->autoRepeatInterval() > 1 )
        ui->pushButtonWywUp->setAutoRepeatInterval(ui->pushButtonWywUp->autoRepeatInterval()-1);

}

void MainWindow::wywTimeUpRelease()
{
    if(!ui->pushButtonWywUp->isDown())
    {
        ui->pushButtonWywUp->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::wywTimeDown()
{
    if ( czas_wyw < 0 )
    {
        czas_wyw = 3600;
    }
    czas_wyw -= 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_wyw);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_wywolanie->display(text);
    if(ui->pushButtonWywDown->autoRepeatInterval() > 1 )
        ui->pushButtonWywDown->setAutoRepeatInterval(ui->pushButtonWywDown->autoRepeatInterval()-1);
}
void MainWindow::wywTimeDownRelease()
{
    if(!ui->pushButtonWywDown->isDown())
    {
        ui->pushButtonWywDown->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::przerTimeUp()
{
    if ( czas_przer > 3600 )
    {
        czas_przer = 0;
    }
    czas_przer += 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_przer);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_przerywanie->display(text);
    if(ui->pushButtonPrzerUp->autoRepeatInterval() > 1 )
        ui->pushButtonPrzerUp->setAutoRepeatInterval(ui->pushButtonPrzerUp->autoRepeatInterval()-1);
}

void MainWindow::przerTimeUpRelease()
{
    if(!ui->pushButtonPrzerUp->isDown())
    {
        ui->pushButtonPrzerUp->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::przerTimeDown()
{
    if ( czas_przer < 0 )
    {
        czas_przer = 3600;
    }
    czas_przer -= 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_przer);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_przerywanie->display(text);
    if(ui->pushButtonPrzerDown->autoRepeatInterval() > 1 )
        ui->pushButtonPrzerDown->setAutoRepeatInterval(ui->pushButtonPrzerDown->autoRepeatInterval()-1);
}

void MainWindow::przerTimeDownRelease()
{
    if(!ui->pushButtonPrzerDown->isDown())
    {
        ui->pushButtonPrzerDown->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::utrwTimeUp()
{
    if ( czas_utrw > 3600 )
    {
        czas_utrw = 0;
    }
    czas_utrw += 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_utrw);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_utrwalanie->display(text);
    if(ui->pushButtonUtrwUp->autoRepeatInterval() > 1 )
        ui->pushButtonUtrwUp->setAutoRepeatInterval(ui->pushButtonUtrwUp->autoRepeatInterval()-1);
}

void MainWindow::utrwTimeUpRelease()
{
    if(!ui->pushButtonUtrwUp->isDown())
    {
        ui->pushButtonUtrwUp->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::utrwTimeDown()
{
    if ( czas_utrw < 0 )
    {
        czas_utrw = 3600;
    }
    czas_utrw -= 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_utrw);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_utrwalanie->display(text);
    if(ui->pushButtonUtrwDown->autoRepeatInterval() > 1 )
        ui->pushButtonUtrwDown->setAutoRepeatInterval(ui->pushButtonUtrwDown->autoRepeatInterval()-1);
}

void MainWindow::utrwTimeDownRelease()
{
    if(!ui->pushButtonUtrwDown->isDown())
    {
        ui->pushButtonUtrwDown->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::plukTimeUp()
{
    if ( czas_pluk > 3600 )
    {
        czas_pluk = 0;
    }
    czas_pluk += 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_pluk);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_plukanie->display(text);
    if(ui->pushButtonPlukUp->autoRepeatInterval() > 1 )
        ui->pushButtonPlukUp->setAutoRepeatInterval(ui->pushButtonPlukUp->autoRepeatInterval()-1);
}

void MainWindow::plukTimeUpRelease()
{
    if(!ui->pushButtonPlukUp->isDown())
    {
        ui->pushButtonPlukUp->setAutoRepeatInterval(autoRepeatInt);
    }
}

void MainWindow::plukTimeDown()
{
    if ( czas_pluk < 0 )
    {
        czas_pluk = 3600;
    }
    czas_pluk -= 1;
    QTime czas_disp = QTime(0,0,0,0);
    czas_disp = czas_disp.addSecs(czas_pluk);
    QString text = czas_disp.toString("mm:ss");
    ui->lcdNumber_plukanie->display(text);
    if(ui->pushButtonPlukDown->autoRepeatInterval() > 1 )
        ui->pushButtonPlukDown->setAutoRepeatInterval(ui->pushButtonPlukDown->autoRepeatInterval()-1);
}

void MainWindow::plukTimeDownRelease()
{
    if(!ui->pushButtonPlukDown->isDown())
    {
        ui->pushButtonPlukDown->setAutoRepeatInterval(autoRepeatInt);
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


