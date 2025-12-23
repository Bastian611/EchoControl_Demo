#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// 解决乱码问题：强制源码为 UTF-8
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

const char* QSS_STYLE = R"(
    /* 全局背景：使用带一点蓝调的深灰色，不那么死板 */
    QMainWindow {
        background-color: #383B40;
        color: #E0E0E0;
        font-family: "Microsoft YaHei UI", "Segoe UI";
        font-size: 14px;
    }

    /* 左侧视频区 */
    QFrame#frameVideo {
        background-color: #000000;
        border: 1px solid #555;
        border-right: none;
    }

    /* 右侧控制栏：比背景稍深，形成层级 */
    QFrame#frameControl {
        background-color: #2D2F33;
        border-left: 1px solid #1A1A1A;
    }

    /* 分组框：增加边框线和圆角 */
    QGroupBox {
        border: 1px solid #505257;
        border-radius: 6px;
        margin-top: 22px; /* 留出标题空间 */
        font-weight: bold;
        color: #CCCCCC;
        background-color: #33363B; /* 组内背景微亮 */
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        padding: 0 5px;
        left: 10px;
        color: #00A3E0; /* 标题用亮蓝色 */
    }

    /* 列表框：音频列表 */
    QListWidget {
        background-color: #222;
        border: 1px solid #444;
        border-radius: 4px;
        color: #ddd;
        outline: none;
    }
    QListWidget::item:selected {
        background-color: #005A9E;
        color: white;
    }

    /* 按钮通用：更立体的感觉 */
    QPushButton {
        background-color: #4A4D52;
        border: 1px solid #3A3C40;
        border-radius: 4px;
        color: #FFFFFF;
        padding: 6px 12px;
    }
    QPushButton:hover {
        background-color: #5A5D63;
        border: 1px solid #00A3E0; /* 悬停亮边 */
    }
    QPushButton:pressed {
        background-color: #007ACC;
        border-color: #005A9E;
    }
    QPushButton:checked {
        background-color: #007ACC;
        color: white;
    }

    /* 红色一键启动按钮 */
    QPushButton#btnOneKey {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E74C3C, stop:1 #C0392B);
        border: 1px solid #962D22;
        border-radius: 8px;
        font-size: 18px;
        font-weight: bold;
    }
    QPushButton#btnOneKey:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FF6B6B, stop:1 #D94538);
    }
    QPushButton#btnOneKey:checked {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2ECC71, stop:1 #27AE60);
        border: 1px solid #1E8449;
    }

    /* 圆形喊话按钮 */
    QPushButton#btnMic {
        border-radius: 40px;
        background-color: #E67E22;
        border: 3px solid #D35400;
        font-weight: bold;
        font-size: 14px;
    }
    QPushButton#btnMic:pressed {
        background-color: #D35400;
        border-color: #A04000;
        margin: 2px; /* 按下位移感 */
    }

    /* 滑块美化 */
    QSlider::groove:horizontal {
        border: 1px solid #3A3C40;
        height: 6px;
        background: #202020;
        margin: 2px 0;
        border-radius: 3px;
    }
    QSlider::handle:horizontal {
        background: #00A3E0;
        border: 1px solid #00A3E0;
        width: 14px;
        height: 14px;
        margin: -4px 0;
        border-radius: 7px;
    }
    QSlider::sub-page:horizontal {
        background: #007ACC;
        border-radius: 3px;
    }

    /* 标签文字 */
    QLabel {
        color: #AAAAAA;
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
        ui->lblVideoPlaceholder->setText("无视频信号");
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
