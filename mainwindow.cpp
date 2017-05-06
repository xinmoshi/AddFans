#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("增粉提示器");

    auto network_manager = new QNetworkAccessManager();
    QNetworkRequest network_request;

    //设置头信息
    network_request.setHeader(QNetworkRequest::ContentLengthHeader,"application/x-www-from-urlencoded");
    //设置url
    network_request.setUrl(QUrl("http://www.baidu.com"));

    connect(network_manager, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);

    network_manager->get(network_request);

    _timer = new QTimer();
    _timer->setInterval(3000);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));


    //QString musicPath = "/Users/chenyehongfy/Desktop/Productions/Level001.mp3";
    _musicPlayer = new QMediaPlayer();
    _musicPlayer->setVolume(80);

    connect(ui->ClearAppId, SIGNAL(clicked(bool)), this, SLOT(OnClearAppId()));
    connect(ui->ClearAppSecret, SIGNAL(clicked(bool)), this, SLOT(OnClearAppSecret()));
    connect(ui->ChangeReduceURL, SIGNAL(clicked(bool)), this, SLOT(OnChangeReduceURL()));
    connect(ui->ChangeAddURL, SIGNAL(clicked(bool)), this, SLOT(OnChangeAddURL()));
    connect(ui->Start, SIGNAL(clicked(bool)), this, SLOT(OnStart()));
    connect(ui->Stop, SIGNAL(clicked(bool)), this, SLOT(OnStop()));
    connect(ui->StopMusic, SIGNAL(clicked(bool)), this, SLOT(OnStopMusic()));

    connect(ui->ReduceFans, SIGNAL(clicked(bool)), this, SLOT(OnReduceFans()));
    connect(ui->AddFans, SIGNAL(clicked(bool)), this, SLOT(OnAddFans()));

    ui->AppIdText->setPlaceholderText("请输入微信公众号AppID");
    ui->AppSecretText->setPlaceholderText("请输入微信公众号应用密钥");
    ui->ReduceMusicURL->setText("/Users/chenyehongfy/Desktop/Productions/Level001.mp3");
    ui->AddMusicURL->setText("/Users/chenyehongfy/Desktop/Productions/Level004.mp3");

    _fansTotal = 100;
    _localTotal = _fansTotal;

    ui->ReduceCheck->setChecked(true);
    ui->AddCheck->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    //获取响应的信息，状态码为200表示正常
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << "status === " << status_code;

    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //获取字节
        QString result(bytes);  //转化为字符串
        //qDebug()<<result;
    }
    else
    {
        //处理错误
    }

    //收到响应，因此需要处理
    delete reply;
}

void MainWindow::onTimerOut()
{
    QString AppIdText = ui->AppIdText->text();
    QString AppSecretText = ui->AppSecretText->text();

    //qDebug()<< "AppId=" << AppIdText << "  AppSecret=" << AppSecretText;


    _time ++;
    //大于本地 增粉
    if(_localTotal<_fansTotal && ui->AddCheck->checkState()==Qt::Checked)
    {
        _musicPlayer->stop();
        _musicPlayer->setMedia(QUrl::fromLocalFile(_addMusicURL));
        _musicPlayer->play();
    }
    //掉粉了
    else if(_localTotal>_fansTotal && ui->ReduceCheck->checkState() == Qt::Checked){
        _musicPlayer->stop();
        _musicPlayer->setMedia(QUrl::fromLocalFile(_reduceMusicURL));
        _musicPlayer->play();
    }

    _localTotal = _fansTotal;
}

void MainWindow::OnClearAppId()
{
    ui->AppIdText->setText("");
}

void MainWindow::OnClearAppSecret()
{
    ui->AppSecretText->setText("");
}

void MainWindow::OnChangeReduceURL()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("Save File"),
                                "/Users/chenyehongfy/Desktop/untitled.png",
                                tr("Names (*.mp3)"));
    if(file_path.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << file_path << endl;
        _reduceMusicURL = file_path;
        ui->ReduceMusicURL->setText(_reduceMusicURL);
    }
}

void MainWindow::OnChangeAddURL()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("Save File"),
                                "/Users/chenyehongfy/Desktop/untitled.png",
                                tr("Names (*.mp3)"));
    if(file_path.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << file_path << endl;
        _addMusicURL = file_path;
        ui->AddMusicURL->setText(_addMusicURL);
    }
}

void MainWindow::OnStart()
{
    ui->AppIdText->setEnabled(false);
    ui->AppSecretText->setEnabled(false);
    ui->ReduceMusicURL->setEnabled(false);
    ui->AddMusicURL->setEnabled(false);

    _timer->start();

    if(ui->AppIdText->text()=="" || )
    {
        ui->MessageTip->text() = "AppID不能为空";
    }
    else if(ui->AppSecretText->text()=="")
    {

    }
}

void MainWindow::OnStop()
{
    ui->AppIdText->setEnabled(true);
    ui->AppSecretText->setEnabled(true);
    ui->ReduceMusicURL->setEnabled(true);
    ui->AddMusicURL->setEnabled(true);

    _timer->stop();
    _musicPlayer->stop();
}

void MainWindow::OnStopMusic()
{
    _musicPlayer->stop();
}

void MainWindow::OnReduceFans()
{
    _fansTotal --;
}

void MainWindow::OnAddFans()
{
    _fansTotal ++;
}
