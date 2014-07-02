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
    void SlowEvent();//Замедление (частота)
    void VolumeEvent(int v);//Громкость
    void FerEvent(int f);//Частота
    void PlaylistEvent();//Плейлист
    void PrevEvent();//Предыдущий трек в плейлисте
    void NextEvent();//Следующий трек в плейлисте
};

#endif // MAINWINDOW_H
