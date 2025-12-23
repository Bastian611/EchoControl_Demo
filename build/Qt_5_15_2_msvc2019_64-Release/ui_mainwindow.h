/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frameVideo;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblVideoPlaceholder;
    QFrame *frameControl;
    QVBoxLayout *verticalLayout;
    QPushButton *btnOneKey;
    QGroupBox *grpLight;
    QGridLayout *gridLayout;
    QPushButton *btnLightSwitch;
    QPushButton *btnStrobe;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *sliderLightLevel;
    QGroupBox *grpSound;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnPlay;
    QPushButton *btnStop;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSlider *sliderVolume;
    QWidget *widgetMic;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnMic;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *grpPTZ;
    QGridLayout *gridLayout_2;
    QPushButton *btnPtzUp;
    QPushButton *btnPtzLeft;
    QPushButton *btnPtzReset;
    QPushButton *btnPtzRight;
    QPushButton *btnPtzDown;
    QSlider *sliderSpeed;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frameVideo = new QFrame(centralwidget);
        frameVideo->setObjectName(QString::fromUtf8("frameVideo"));
        frameVideo->setStyleSheet(QString::fromUtf8("background-color: #000000;"));
        frameVideo->setFrameShape(QFrame::NoFrame);
        frameVideo->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameVideo);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lblVideoPlaceholder = new QLabel(frameVideo);
        lblVideoPlaceholder->setObjectName(QString::fromUtf8("lblVideoPlaceholder"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(14);
        lblVideoPlaceholder->setFont(font);
        lblVideoPlaceholder->setStyleSheet(QString::fromUtf8("color: #555;"));
        lblVideoPlaceholder->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblVideoPlaceholder);


        horizontalLayout->addWidget(frameVideo);

        frameControl = new QFrame(centralwidget);
        frameControl->setObjectName(QString::fromUtf8("frameControl"));
        frameControl->setStyleSheet(QString::fromUtf8("background-color: #2D2D30;"));
        frameControl->setFrameShape(QFrame::NoFrame);
        verticalLayout = new QVBoxLayout(frameControl);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        btnOneKey = new QPushButton(frameControl);
        btnOneKey->setObjectName(QString::fromUtf8("btnOneKey"));
        btnOneKey->setMinimumSize(QSize(0, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        btnOneKey->setFont(font1);
        btnOneKey->setCheckable(true);

        verticalLayout->addWidget(btnOneKey);

        grpLight = new QGroupBox(frameControl);
        grpLight->setObjectName(QString::fromUtf8("grpLight"));
        gridLayout = new QGridLayout(grpLight);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnLightSwitch = new QPushButton(grpLight);
        btnLightSwitch->setObjectName(QString::fromUtf8("btnLightSwitch"));
        btnLightSwitch->setCheckable(true);

        gridLayout->addWidget(btnLightSwitch, 0, 0, 1, 1);

        btnStrobe = new QPushButton(grpLight);
        btnStrobe->setObjectName(QString::fromUtf8("btnStrobe"));
        btnStrobe->setCheckable(true);

        gridLayout->addWidget(btnStrobe, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(grpLight);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        sliderLightLevel = new QSlider(grpLight);
        sliderLightLevel->setObjectName(QString::fromUtf8("sliderLightLevel"));
        sliderLightLevel->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sliderLightLevel);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);


        verticalLayout->addWidget(grpLight);

        grpSound = new QGroupBox(frameControl);
        grpSound->setObjectName(QString::fromUtf8("grpSound"));
        verticalLayout_3 = new QVBoxLayout(grpSound);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnPlay = new QPushButton(grpSound);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));

        horizontalLayout_3->addWidget(btnPlay);

        btnStop = new QPushButton(grpSound);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        horizontalLayout_3->addWidget(btnStop);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(grpSound);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        sliderVolume = new QSlider(grpSound);
        sliderVolume->setObjectName(QString::fromUtf8("sliderVolume"));
        sliderVolume->setValue(50);
        sliderVolume->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(sliderVolume);


        verticalLayout_3->addLayout(horizontalLayout_4);

        widgetMic = new QWidget(grpSound);
        widgetMic->setObjectName(QString::fromUtf8("widgetMic"));
        horizontalLayout_5 = new QHBoxLayout(widgetMic);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btnMic = new QPushButton(widgetMic);
        btnMic->setObjectName(QString::fromUtf8("btnMic"));
        btnMic->setMinimumSize(QSize(80, 80));
        btnMic->setMaximumSize(QSize(80, 80));

        horizontalLayout_5->addWidget(btnMic);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(widgetMic);


        verticalLayout->addWidget(grpSound);

        grpPTZ = new QGroupBox(frameControl);
        grpPTZ->setObjectName(QString::fromUtf8("grpPTZ"));
        gridLayout_2 = new QGridLayout(grpPTZ);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnPtzUp = new QPushButton(grpPTZ);
        btnPtzUp->setObjectName(QString::fromUtf8("btnPtzUp"));

        gridLayout_2->addWidget(btnPtzUp, 0, 1, 1, 1);

        btnPtzLeft = new QPushButton(grpPTZ);
        btnPtzLeft->setObjectName(QString::fromUtf8("btnPtzLeft"));

        gridLayout_2->addWidget(btnPtzLeft, 1, 0, 1, 1);

        btnPtzReset = new QPushButton(grpPTZ);
        btnPtzReset->setObjectName(QString::fromUtf8("btnPtzReset"));

        gridLayout_2->addWidget(btnPtzReset, 1, 1, 1, 1);

        btnPtzRight = new QPushButton(grpPTZ);
        btnPtzRight->setObjectName(QString::fromUtf8("btnPtzRight"));

        gridLayout_2->addWidget(btnPtzRight, 1, 2, 1, 1);

        btnPtzDown = new QPushButton(grpPTZ);
        btnPtzDown->setObjectName(QString::fromUtf8("btnPtzDown"));

        gridLayout_2->addWidget(btnPtzDown, 2, 1, 1, 1);

        sliderSpeed = new QSlider(grpPTZ);
        sliderSpeed->setObjectName(QString::fromUtf8("sliderSpeed"));
        sliderSpeed->setMaximum(64);
        sliderSpeed->setValue(32);
        sliderSpeed->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderSpeed, 3, 0, 1, 3);


        verticalLayout->addWidget(grpPTZ);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(frameControl);

        horizontalLayout->setStretch(0, 7);
        horizontalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EchoControl System - \346\210\230\346\234\257\346\216\247\345\210\266\347\273\210\347\253\257", nullptr));
        lblVideoPlaceholder->setText(QCoreApplication::translate("MainWindow", "\346\227\240\350\247\206\351\242\221\344\277\241\345\217\267", nullptr));
        btnOneKey->setText(QCoreApplication::translate("MainWindow", "\360\237\224\264 \344\270\200\351\224\256\346\213\222\346\255\242\345\220\257\345\212\250", nullptr));
        grpLight->setTitle(QCoreApplication::translate("MainWindow", "\345\274\272\345\205\211\346\216\247\345\210\266 (Light)", nullptr));
        btnLightSwitch->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\205\263", nullptr));
        btnStrobe->setText(QCoreApplication::translate("MainWindow", "\351\242\221\351\227\252", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\272\256\345\272\246:", nullptr));
        grpSound->setTitle(QCoreApplication::translate("MainWindow", "\345\274\272\345\243\260\346\216\247\345\210\266 (Sound)", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindow", "\342\226\266 \346\222\255\346\224\276", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "\342\226\240 \345\201\234\346\255\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217:", nullptr));
        btnMic->setText(QCoreApplication::translate("MainWindow", "\346\214\211\344\275\217\n"
"\345\226\212\350\257\235", nullptr));
        grpPTZ->setTitle(QCoreApplication::translate("MainWindow", "\344\272\221\345\217\260\346\216\247\345\210\266 (PTZ)", nullptr));
        btnPtzUp->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        btnPtzLeft->setText(QCoreApplication::translate("MainWindow", "\342\227\200", nullptr));
        btnPtzReset->setText(QCoreApplication::translate("MainWindow", "\342\227\217", nullptr));
        btnPtzRight->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        btnPtzDown->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
