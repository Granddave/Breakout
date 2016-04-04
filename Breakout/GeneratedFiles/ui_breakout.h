/********************************************************************************
** Form generated from reading UI file 'breakout.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BREAKOUT_H
#define UI_BREAKOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BreakoutClass
{
public:
    QWidget *centralWidget;
    QPushButton *startButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BreakoutClass)
    {
        if (BreakoutClass->objectName().isEmpty())
            BreakoutClass->setObjectName(QStringLiteral("BreakoutClass"));
        BreakoutClass->resize(600, 400);
        centralWidget = new QWidget(BreakoutClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(490, 30, 75, 23));
        BreakoutClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BreakoutClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        BreakoutClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BreakoutClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BreakoutClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BreakoutClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BreakoutClass->setStatusBar(statusBar);

        retranslateUi(BreakoutClass);

        QMetaObject::connectSlotsByName(BreakoutClass);
    } // setupUi

    void retranslateUi(QMainWindow *BreakoutClass)
    {
        BreakoutClass->setWindowTitle(QApplication::translate("BreakoutClass", "Breakout", 0));
        startButton->setText(QApplication::translate("BreakoutClass", "Start", 0));
    } // retranslateUi

};

namespace Ui {
    class BreakoutClass: public Ui_BreakoutClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BREAKOUT_H
