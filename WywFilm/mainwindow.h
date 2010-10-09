#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QSound>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int czas_wyw, czas_przer, czas_utrw, czas_pluk, czas_miedzy1, czas_miedzy2, czas_miedzy3, czas_start;
    //QTime *time_wyw, *time_przer, *time_utrw, *time_pluk, *time_miedzy;


private:
    Ui::MainWindow *ui;
    QTimer *timer;
   // QTime *time;

    int czas;

    void setTextHowto();
    void displayTime();
    void getTimes();
    void addVoiceFiles();

    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    QList<Phonon::MediaSource> sources;



private slots:
    void startCountDown();
    void stopCountDown();
    void resetCountDown();
    void startDisplay();

    void wywTimeUp();
    void wywTimeDown();
    void przerTimeUp();
    void przerTimeDown();
    void utrwTimeUp();
    void utrwTimeDown();
    void plukTimeUp();
    void plukTimeDown();

};

#endif // MAINWINDOW_H
