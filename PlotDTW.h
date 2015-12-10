#ifndef PlotDTW_H
#define PlotDTW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

#include "DummyDTW.h"

namespace Ui {
    class PlotDTW;
}

class PlotDTW : public QMainWindow //Plot extends a Window
{
    Q_OBJECT

    public:
        explicit PlotDTW(QWidget *parent = 0);
	~PlotDTW();
        void setDTW(DummyDTW aDTW);

    private:
        Ui::PlotDTW *ui;
	DummyDTW myDTW;

    protected:
        void paintEvent(QPaintEvent* e);
};

#endif // PlotDTW_H
