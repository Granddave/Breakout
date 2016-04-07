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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BreakoutClass
{
public:
    QAction *actionNew;
    QAction *actionExit;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuGame;

    void setupUi(QMainWindow *BreakoutClass)
    {
        if (BreakoutClass->objectName().isEmpty())
            BreakoutClass->setObjectName(QStringLiteral("BreakoutClass"));
        BreakoutClass->resize(600, 400);
        actionNew = new QAction(BreakoutClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionExit = new QAction(BreakoutClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(BreakoutClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BreakoutClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BreakoutClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BreakoutClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(BreakoutClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        BreakoutClass->setMenuBar(menuBar);

        menuBar->addAction(menuGame->menuAction());
        menuGame->addAction(actionNew);
        menuGame->addAction(actionExit);

        retranslateUi(BreakoutClass);

        QMetaObject::connectSlotsByName(BreakoutClass);
    } // setupUi

    void retranslateUi(QMainWindow *BreakoutClass)
    {
        BreakoutClass->setWindowTitle(QApplication::translate("BreakoutClass", "Breakout", 0));
        actionNew->setText(QApplication::translate("BreakoutClass", "New Game", 0));
        actionExit->setText(QApplication::translate("BreakoutClass", "Exit", 0));
        menuGame->setTitle(QApplication::translate("BreakoutClass", "Game", 0));
    } // retranslateUi

};

namespace Ui {
    class BreakoutClass: public Ui_BreakoutClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BREAKOUT_H
