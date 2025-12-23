#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// CSS 样式表 (Dark Theme)
const char* QSS_STYLE = R"(
    QMainWindow { background-color: #1e1e1e; color: #f0f0f0; }

    /* 右侧控制区 */
    QFrame#frameControl {
        background-color: #2D2D30;
        border-left: 1px solid #3e3e42;
    }

    /* 分组框 */
    QGroupBox {
        border: 1px solid #454545;
        border-radius: 4px;
        margin-top: 20px;
        font-weight: bold;
        color: #cccccc;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top center;
        padding: 0 5px;
    }

    /* 按钮通用 */
    QPushButton {
        background-color: #3e3e42;
        border: 1px solid #555;
        border-radius: 4px;
        color: white;
        padding: 6px;
    }
    QPushButton:hover { background-color: #505050; }
    QPushButton:pressed { background-color: #007acc; }
    QPushButton:checked { background-color: #007acc; border-color: #0099ff; }

    /* 一键拒止按钮 (红色/绿色) */
    QPushButton#btnOneKey {
        background-color: #c0392b;
        border: 2px solid #e74c3c;
        font-size: 16px;
    }
    QPushButton#btnOneKey:checked {
        background-color: #27ae60;
        border-color: #2ecc71;
    }

    /* 喊话按钮 (圆形) */
    QPushButton#btnMic {
        border-radius: 40px;
        background-color: #d35400;
        border: 2px solid #e67e22;
        font-weight: bold;
    }
    QPushButton#btnMic:pressed {
        background-color: #e67e22;
    }

    /* 滑块 */
    QSlider::groove:horizontal {
        border: 1px solid #333;
        height: 6px;
        background: #202020;
        border-radius: 3px;
    }
    QSlider::handle:horizontal {
        background: #007acc;
        border: 1px solid #007acc;
        width: 14px;
        margin: -5px 0;
        border-radius: 7px;
    }
)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitStyle();
    InitSDK();

    // 绑定云台按住操作
    connect(ui->btnPtzUp, &QPushButton::pressed, this, &MainWindow::onPtzPressed);
    connect(ui->btnPtzDown, &QPushButton::pressed, this, &MainWindow::onPtzPressed);
    connect(ui->btnPtzLeft, &QPushButton::pressed, this, &MainWindow::onPtzPressed);
    connect(ui->btnPtzRight, &QPushButton::pressed, this, &MainWindow::onPtzPressed);

    connect(ui->btnPtzUp, &QPushButton::released, this, &MainWindow::onPtzReleased);
    connect(ui->btnPtzDown, &QPushButton::released, this, &MainWindow::onPtzReleased);
    connect(ui->btnPtzLeft, &QPushButton::released, this, &MainWindow::onPtzReleased);
    connect(ui->btnPtzRight, &QPushButton::released, this, &MainWindow::onPtzReleased);

    // 模拟麦克风采集
    connect(&m_micSimTimer, &QTimer::timeout, [this](){
        if(m_hSystem) {
            char dummy[1024]; // 模拟 PCM
            ECCS_Sound_PushData(m_hSystem, dummy, 1024);
        }
    });
}

MainWindow::~MainWindow()
{
    ECCS_Release();
    delete ui;
}

void MainWindow::InitStyle() {
    this->setStyleSheet(QSS_STYLE);
}

void MainWindow::InitSDK() {
    // 调用 SDK 初始化
    if (ECCS_Init() == ECCS_SUCCESS) {
        m_hSystem = ECCS_GetHandle();

        // 注册回调 (注意 C 回调到 C++ 的转换)
        // 实际使用时建议使用全局静态函数做跳板，或者 event loop
    } else {
        ui->lblVideoPlaceholder->setText("SDK 初始化失败");
    }
}

// === 一键启动 ===
void MainWindow::on_btnOneKey_toggled(bool checked)
{
    if (checked) {
        ui->btnOneKey->setText("⚠️ 停止拒止 (运行中)");
        // 1. 开灯
        ECCS_Light_SetLevel(m_hSystem, 100);
        ECCS_Light_SetStrobe(m_hSystem, 1);
        ECCS_Light_SetSwitch(m_hSystem, 1);
        // 2. 云台动作 (假设预置位1是攻击位)
        ECCS_PTZ_Preset(m_hSystem, 2, 1);
        // 3. 播放警报
        ECCS_Sound_SetVolume(m_hSystem, 100);
        ECCS_Sound_Play(m_hSystem, "alarm.mp3", 1);

        // 同步 UI 状态
        ui->btnLightSwitch->setChecked(true);
        ui->btnStrobe->setChecked(true);
        ui->sliderLightLevel->setValue(100);
        ui->sliderVolume->setValue(100);
    } else {
        ui->btnOneKey->setText("🔴 一键拒止启动");
        // 复位
        ECCS_Light_SetSwitch(m_hSystem, 0);
        ECCS_Sound_Stop(m_hSystem);
        ECCS_PTZ_Move(m_hSystem, 5, 0); // Stop

        ui->btnLightSwitch->setChecked(false);
        ui->btnStrobe->setChecked(false);
    }
}

// === 强光 ===
void MainWindow::on_btnLightSwitch_toggled(bool checked) {
    ECCS_Light_SetSwitch(m_hSystem, checked ? 1 : 0);
}
void MainWindow::on_sliderLightLevel_valueChanged(int value) {
    ECCS_Light_SetLevel(m_hSystem, value);
}
void MainWindow::on_btnStrobe_toggled(bool checked) {
    ECCS_Light_SetStrobe(m_hSystem, checked ? 1 : 0);
}

// === 强声 ===
void MainWindow::on_btnPlay_clicked() {
    ECCS_Sound_Play(m_hSystem, "warning.mp3", 0);
}
void MainWindow::on_btnStop_clicked() {
    ECCS_Sound_Stop(m_hSystem);
}
void MainWindow::on_sliderVolume_valueChanged(int value) {
    ECCS_Sound_SetVolume(m_hSystem, value);
}
void MainWindow::on_btnMic_pressed() {
    ECCS_Sound_SetMic(m_hSystem, 1);
    m_micSimTimer.start(20); // 20ms 一次模拟数据
}
void MainWindow::on_btnMic_released() {
    m_micSimTimer.stop();
    ECCS_Sound_SetMic(m_hSystem, 0);
}

// === 云台 ===
void MainWindow::onPtzPressed() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    int speed = ui->sliderSpeed->value();
    int action = 5; // Stop

    if (btn == ui->btnPtzUp) action = 1;
    else if (btn == ui->btnPtzDown) action = 2;
    else if (btn == ui->btnPtzLeft) action = 3;
    else if (btn == ui->btnPtzRight) action = 4;

    ECCS_PTZ_Move(m_hSystem, action, speed);
}

void MainWindow::onPtzReleased() {
    ECCS_PTZ_Move(m_hSystem, 5, 0); // Stop
}

void MainWindow::on_btnPtzReset_clicked() {
    // 假设预置位 0 为归位
    ECCS_PTZ_Preset(m_hSystem, 2, 0);
}
