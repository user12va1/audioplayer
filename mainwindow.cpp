#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QStringList>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Меню
       //Открытие файла
       QObject::connect(ui->Flchoose, SIGNAL(triggered()), this, SLOT(FileEvent()));
       //Добавление файла в плейлист
       QObject::connect(ui->Plchoose, SIGNAL(triggered()), this, SLOT(PlaylistEvent()));
    //Кнопки 1 ур
       //Воспроизведение
       QObject::connect(ui->Playb, SIGNAL(clicked()), this, SLOT(PlayEvent()));
       //Пауза
       QObject::connect(ui->Pauseb, SIGNAL(clicked()), this, SLOT(PauseEvent()));
       //Остановка
       QObject::connect(ui->Stopb, SIGNAL(clicked()), this, SLOT(StopEvent()));
    //Кнопки 2 ур
       //Предыдущий трек в плейлисте
       QObject::connect(ui->Prevb, SIGNAL(clicked()), this, SLOT(PrevEvent()));
       //Следующий трек в плейлисте
       QObject::connect(ui->Nextb, SIGNAL(clicked()), this, SLOT(NextEvent()));
    //Кнопки 3 ур
       //Замедление
       QObject::connect(ui->Slowb, SIGNAL(clicked()), this, SLOT(SlowEvent()));
       //Переход в плейлист
       QObject::connect(ui->Jumpb, SIGNAL(clicked()), this, SLOT(JumpEvent()));
    //Регуляторы
       //Громкость
       QObject::connect(ui->Volumes, SIGNAL(valueChanged(int)),this, SLOT(VolumeEvent(int)));
       //Частота
       QObject::connect(ui->Fers, SIGNAL(valueChanged(int)),this, SLOT(FerEvent(int)));
    //Список воспроизведения
       //Выбор трека из плейлиста
       QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(WidgetEvent(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMediaPlayer *player = new QMediaPlayer;
QMediaPlaylist *playlist = new QMediaPlaylist;

void MainWindow::FileEvent()//Открытие файла
{
    QString  filepath = QFileDialog::getOpenFileName(this, tr("Open AudioFile"),"C:/Users/Public/Music/Sample Music",tr("(*.mp3 *.wav *.ogg)"));
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

void MainWindow::PlayEvent()//Воспроизведение
{
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::PauseEvent()//Пауза
{
    player->pause();
}

void MainWindow::StopEvent()//Остановка
{
    player->stop();
}

void MainWindow::VolumeEvent(int v)//Громкость
{
    ui->Volumen->display(v);
    player->setVolume(v);
}

void MainWindow::PlaylistEvent()//Добавление файлов в плейлист
{
    QStringList  filepath = QFileDialog::getOpenFileNames(this, tr("Add files to Playlist"),"C:/Users/Public/Music/Sample Music",tr("(*.mp3 *.wav *.ogg)"));
    for (int i = 0; i < filepath.size(); ++i)
        {
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(filepath.at(i))));
        ui->listWidget->addItem(filepath.at(i));
        ui->listWidget->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
        }
        playlist->setCurrentIndex(1);
        player->setPlaylist(playlist);
        playlist->CurrentItemInLoop;
        player->play();
        ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::PrevEvent()//Предыдущий трек в плейлисте
{
    playlist->previous();
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::NextEvent() //Следующий трек в плейлисте
{
    playlist->next();
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::SlowEvent()//Замедление
{
    player->setPlaybackRate(0.5);
}

void MainWindow::FerEvent(int f)//Частота
{
    ui->Fern->display(f);
    player->setPlaybackRate(f);
}

void MainWindow::JumpEvent()//Переход в плейлист
{
    player->setPlaylist(playlist);
    player->play();
    ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}

void MainWindow::WidgetEvent(QListWidgetItem* g)//Выбор трека из плейлиста
{
 player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(g->text())));
     /* playlist->setCurrentIndex(1);
      for (int i=0;i<playlist->mediaCount();i++)
      {
          if (playlist->currentMedia().canonicalUrl().toString()==g->text())
          {
              break;
          }
          playlist->next();
      }*/
player->play();
      ui->CurrentS->setText(player->currentMedia().canonicalUrl().toString());
}
