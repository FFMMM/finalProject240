#include <QtGui/QApplication>
#include <iostream>
#include "PlotDTW.h"
#include "Signal.h"
#include "DTW.h"

using namespace std;

int main(int argc, char *argv[])
{

    Signal querySig(argv[1]);
    Signal refSig(argv[2]);

//  Step 2) Construct DTW
    //DTW aDTW(*querySigPtr, *refSigPtr);
    DTW aDTW(querySig, refSig);
    cout << "Testing DTW construction: " << endl;
    cout << "aDTW.getSecond().getData().at(54) = " <<
		aDTW.getSecond().getData().at(54) << endl;

//  Step 3) Tell the DTW to compare signals
    //aDTW.compare();
    cout << "Testing the DTW comparison: " << endl;
    cout << "aDTW.getComparison().at(54).x = ";// << 
		//aDTW.getComparison().at(54).x << endl;

//  Step 4) Construct a PlotDTW
    QApplication a(argc, argv);
    cout << "We made a QApplication" << endl;
    PlotDTW w;
    cout << "We constructed the PlotDTW" << endl;
//  Step 5) Pass the DTW to it
    w.setDTW(aDTW);

//  Step 6) Draw the display  
    w.show();

 /*  delete querySigPtr;
    delete refSigPtr; */

    return a.exec();
}
