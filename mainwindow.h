#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
// 引入你的 SDK
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
    void on_btnPlay_clicked();
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

    // 内部处理 SDK 回调 (Qt 线程安全处理)
    void HandleSDKCallback(int type, const void* data);

private:
    Ui::MainWindow *ui;
    ECCS_HANDLE m_hSystem = nullptr;

    // 模拟音频采集 (实际需要 QtMultimedia)
    QTimer m_micSimTimer;
};
#endif // MAINWINDOW_H
