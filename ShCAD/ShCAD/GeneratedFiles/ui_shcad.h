/********************************************************************************
** Form generated from reading UI file 'shcad.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHCAD_H
#define UI_SHCAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShCADClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ShCADClass)
    {
        if (ShCADClass->objectName().isEmpty())
            ShCADClass->setObjectName(QStringLiteral("ShCADClass"));
        ShCADClass->resize(600, 400);
        menuBar = new QMenuBar(ShCADClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ShCADClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ShCADClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ShCADClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ShCADClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ShCADClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ShCADClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ShCADClass->setStatusBar(statusBar);

        retranslateUi(ShCADClass);

        QMetaObject::connectSlotsByName(ShCADClass);
    } // setupUi

    void retranslateUi(QMainWindow *ShCADClass)
    {
        ShCADClass->setWindowTitle(QApplication::translate("ShCADClass", "ShCAD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShCADClass: public Ui_ShCADClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHCAD_H
