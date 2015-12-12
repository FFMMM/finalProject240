#ifndef PlotDTW_H
#define PlotDTW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QString>
#include <vector>

#include "DTW.h"

namespace Ui {
    class PlotDTW;
}

class PlotDTW : public QMainWindow //Plot extends a Window
{
    Q_OBJECT

    public:
        explicit PlotDTW(QWidget *parent = 0);
	~PlotDTW();
        void setDTW(DTW aDTW);

    private:
        Ui::PlotDTW *ui;
	    DTW myDTW;

        const static int TICKNUM = 5;
        const static int TICKNUMX = 6;
        double labelQuery[TICKNUM];
        double labelReference[TICKNUM];

        void findTickValues();

    protected:
        void paintEvent(QPaintEvent* e);

};

#endif // PlotDTW_H
