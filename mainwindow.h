#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void FileEvent();//Открытие файла
    void PlayEvent();//Воспроизведение
    void PauseEvent();//Пауза
    void StopEvent();//Остановка
    void VolumeEvent(int v);
    void FerEvent(int f);
    void PlaylistEvent();
    void PrevEvent();
    void NextEvent();
    void SlowEvent();
   // void ChangeCNEvent();
};

#endif // MAINWINDOW_H
