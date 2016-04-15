/********************************************************************************
** Form generated from reading UI file 'RenderWindowUISingleInheritance.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERWINDOWUISINGLEINHERITANCE_H
#define UI_RENDERWINDOWUISINGLEINHERITANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_RenderWindowUISingleInheritance
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QVTKWidget *qvtkWidget;
    QPushButton *pushButton;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QMainWindow *RenderWindowUISingleInheritance)
    {
        if (RenderWindowUISingleInheritance->objectName().isEmpty())
            RenderWindowUISingleInheritance->setObjectName(QStringLiteral("RenderWindowUISingleInheritance"));
        RenderWindowUISingleInheritance->resize(800, 580);
        actionOpenFile = new QAction(RenderWindowUISingleInheritance);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        actionExit = new QAction(RenderWindowUISingleInheritance);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionPrint = new QAction(RenderWindowUISingleInheritance);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionHelp = new QAction(RenderWindowUISingleInheritance);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionSave = new QAction(RenderWindowUISingleInheritance);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralwidget = new QWidget(RenderWindowUISingleInheritance);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(10, 30, 511, 541));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 115, 32));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(620, 30, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(620, 80, 160, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(620, 130, 160, 22));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(600, 30, 16, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(600, 80, 16, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(600, 130, 16, 16));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(690, 50, 47, 24));
        spinBox_2 = new QSpinBox(centralwidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(690, 100, 47, 24));
        spinBox_3 = new QSpinBox(centralwidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(690, 150, 47, 24));
        spinBox_4 = new QSpinBox(centralwidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(630, 190, 47, 24));
        spinBox_5 = new QSpinBox(centralwidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setGeometry(QRect(630, 220, 47, 24));
        spinBox_6 = new QSpinBox(centralwidget);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setGeometry(QRect(630, 250, 47, 24));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(600, 190, 21, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(600, 220, 21, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(600, 250, 21, 20));
        RenderWindowUISingleInheritance->setCentralWidget(centralwidget);

        retranslateUi(RenderWindowUISingleInheritance);
        QObject::connect(pushButton, SIGNAL(clicked()), pushButton, SLOT(showMenu()));

        QMetaObject::connectSlotsByName(RenderWindowUISingleInheritance);
    } // setupUi

    void retranslateUi(QMainWindow *RenderWindowUISingleInheritance)
    {
        RenderWindowUISingleInheritance->setWindowTitle(QApplication::translate("RenderWindowUISingleInheritance", "RenderWindowUISingleInheritance", 0));
        actionOpenFile->setText(QApplication::translate("RenderWindowUISingleInheritance", "Open File...", 0));
        actionExit->setText(QApplication::translate("RenderWindowUISingleInheritance", "Exit", 0));
        actionPrint->setText(QApplication::translate("RenderWindowUISingleInheritance", "Print", 0));
        actionHelp->setText(QApplication::translate("RenderWindowUISingleInheritance", "Help", 0));
        actionSave->setText(QApplication::translate("RenderWindowUISingleInheritance", "Save", 0));
        pushButton->setText(QApplication::translate("RenderWindowUISingleInheritance", "Open File", 0));
        label->setText(QApplication::translate("RenderWindowUISingleInheritance", "a", 0));
        label_2->setText(QApplication::translate("RenderWindowUISingleInheritance", "b", 0));
        label_3->setText(QApplication::translate("RenderWindowUISingleInheritance", "c", 0));
        label_4->setText(QApplication::translate("RenderWindowUISingleInheritance", "x", 0));
        label_5->setText(QApplication::translate("RenderWindowUISingleInheritance", "y", 0));
        label_6->setText(QApplication::translate("RenderWindowUISingleInheritance", "z", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderWindowUISingleInheritance: public Ui_RenderWindowUISingleInheritance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERWINDOWUISINGLEINHERITANCE_H
