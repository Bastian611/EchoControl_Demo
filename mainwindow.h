#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "EchoControlSDK.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 一键拒止
    void on_btnOneKey_toggled(bool checked);

    // 强光
    void on_btnLightSwitch_toggled(bool checked);
    void on_sliderLightLevel_valueChanged(int value);
    void on_btnStrobe_toggled(bool checked);

    // 强声
    void on_btnPlay_clicked(int index);
    void on_btnStop_clicked();
    void on_sliderVolume_valueChanged(int value);
    void on_btnMic_pressed();
    void on_btnMic_released();

    // 云台 (按下开始转，松开停止)
    void onPtzPressed();
    void onPtzReleased();
    void on_btnPtzReset_clicked();

private:
    void InitStyle();
    void InitSDK();
    void InitVideoUI(); // 初始化视频区域的按钮和播放器
    void StartAutoStream();  // 启动自动拉流

    // 内部处理 SDK 回调 (Qt 线程安全处理)
    void HandleSDKCallback(int type, const void* data);

private:
    Ui::MainWindow *ui;
    ECCS_HANDLE m_hSystem = nullptr;

    // 模拟音频采集 (实际需要 QtMultimedia)
    QTimer m_micSimTimer;

    QMediaPlayer* m_player = nullptr;
    QVideoWidget* m_videoWidget = nullptr;
    QWidget* m_videoOverlay = nullptr; // 浮动工具栏容器
};
#endif // MAINWINDOW_H
