/********************************************************************************
** Form generated from reading UI file 'cutvideoserivce.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTVIDEOSERIVCE_H
#define UI_CUTVIDEOSERIVCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cutvideoserivceClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cutvideoserivceClass)
    {
        if (cutvideoserivceClass->objectName().isEmpty())
            cutvideoserivceClass->setObjectName(QStringLiteral("cutvideoserivceClass"));
        cutvideoserivceClass->resize(600, 400);
        menuBar = new QMenuBar(cutvideoserivceClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        cutvideoserivceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cutvideoserivceClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        cutvideoserivceClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(cutvideoserivceClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        cutvideoserivceClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(cutvideoserivceClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        cutvideoserivceClass->setStatusBar(statusBar);

        retranslateUi(cutvideoserivceClass);

        QMetaObject::connectSlotsByName(cutvideoserivceClass);
    } // setupUi

    void retranslateUi(QMainWindow *cutvideoserivceClass)
    {
        cutvideoserivceClass->setWindowTitle(QApplication::translate("cutvideoserivceClass", "cutvideoserivce", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class cutvideoserivceClass: public Ui_cutvideoserivceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTVIDEOSERIVCE_H
