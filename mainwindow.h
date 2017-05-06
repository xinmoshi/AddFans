#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply* reply);
    void onTimerOut();
    void OnClearAppId();
    void OnClearAppSecret();
    void OnChangeReduceURL();
    void OnChangeAddURL();
    void OnStart();
    void OnStop();
    void OnStopMusic();

    void OnReduceFans();
    void OnAddFans();

    signals:
     void SendMessage(QString AppIdStr, QString AppSecretStr);

private:
    Ui::MainWindow *ui;
    //计时器
    QTimer *_timer;
    //音乐播放地址
    QString _reduceMusicURL;
    QString _addMusicURL;
    QMediaPlayer *_musicPlayer;
    int _fansTotal;
    int _localTotal;
    int _time = 0;
};

#endif // MAINWINDOW_H
