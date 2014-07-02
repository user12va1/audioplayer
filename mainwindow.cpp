#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       //Меню
       QObject::connect(ui->Flchoose, SIGNAL(triggered()), this, SLOT(FileEvent()));
       QObject::connect(ui->Plchoose, SIGNAL(triggered()), this, SLOT(PlaylistEvent()));
       //Кнопки 1 ур
       QObject::connect(ui->Playb, SIGNAL(clicked()), this, SLOT(PlayEvent()));
       QObject::connect(ui->Pauseb, SIGNAL(clicked()), this, SLOT(PauseEvent()));
       QObject::connect(ui->Stopb, SIGNAL(clicked()), this, SLOT(StopEvent()));
       //Кнопки 2 ур
       QObject::connect(ui->Prevb, SIGNAL(clicked()), this, SLOT(PrevEvent()));
       QObject::connect(ui->Nextb, SIGNAL(clicked()), this, SLOT(NextEvent()));
       //Кнопки 3 ур
       QObject::connect(ui->Slowb, SIGNAL(clicked()), this, SLOT(SlowEvent()));
       //Регуляторы
       QObject::connect(ui->Volumes, SIGNAL(valueChanged(int)),this, SLOT(VolumeEvent(int)));
       QObject::connect(ui->Fers, SIGNAL(valueChanged(int)),this, SLOT(FerEvent(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMediaPlayer *player = new QMediaPlayer;
QMediaPlaylist *playlist = new QMediaPlaylist;

void MainWindow::FileEvent()
{
    QString  filepath = QFileDialog::getOpenFileName(this, tr("Open AudioFile"),"C:/Users/Admine/Music/Probe",tr("(*.mp3 *.wav *.ogg)"));
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }
    player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(filepath)));
    player->setVolume(50);
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::PlayEvent()
{
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::PauseEvent()
{
    player->pause();
}

void MainWindow::StopEvent()
{
    player->stop();
}

void MainWindow::VolumeEvent(int v)
{
    ui->Volumen->display(v);
    player->setVolume(v);
}

void MainWindow::PlaylistEvent()
{
    QString  filepath = QFileDialog::getOpenFileName(this, tr("Add file to Playlist"),"C:/Users/Admine/Music/Probe",tr("(*.mp3 *.wav *.ogg)"));
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(filepath)));
        playlist->setCurrentIndex(1);
        player->setPlaylist(playlist);
        playlist->CurrentItemInLoop;
       ui->listWidget->addItem(filepath);
       ui->listWidget->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
}

void MainWindow::PrevEvent()
{
    playlist->previous();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::NextEvent()
{
    playlist->next();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

/*void MainWindow::ChangeCNEvent()
{
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}*/

void MainWindow::SlowEvent()
{
    player->setPlaybackRate(0.5);
}

void MainWindow::FerEvent(int f)
{
    ui->Fern->display(f);
    player->setPlaybackRate(f);
}
