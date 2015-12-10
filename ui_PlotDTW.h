/********************************************************************************
** Form generated from reading UI file 'PlotDTW.ui'
**
** Created: Thu Dec 10 00:50:24 2015
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDTW_H
#define UI_PLOTDTW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotDTW
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PlotDTW)
    {
        if (PlotDTW->objectName().isEmpty())
            PlotDTW->setObjectName(QString::fromUtf8("PlotDTW"));
        PlotDTW->resize(753, 681);
        centralWidget = new QWidget(PlotDTW);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PlotDTW->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlotDTW);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 753, 22));
        PlotDTW->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlotDTW);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PlotDTW->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PlotDTW);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PlotDTW->setStatusBar(statusBar);

        retranslateUi(PlotDTW);

        QMetaObject::connectSlotsByName(PlotDTW);
    } // setupUi

    void retranslateUi(QMainWindow *PlotDTW)
    {
        PlotDTW->setWindowTitle(QApplication::translate("PlotDTW", "PlotDTW", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotDTW: public Ui_PlotDTW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDTW_H
