#include "PlotDTW.h"
#include "ui_PlotDTW.h"

PlotDTW::PlotDTW(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PlotDTW)
{
	ui->setupUi(this);
	//*.ui assumed to set Width = 1024; Height = 576
	//default constructor for dummyDTW required
}

PlotDTW::~PlotDTW()
{
    delete ui;
}

void PlotDTW::setDTW(DummyDTW aDTW)
{
	myDTW = aDTW;
}

void PlotDTW::paintEvent(QPaintEvent *e)
{
//	1) Draw Rectangles around Plot Areas
	QPainter painter(this);	
	QPen linePen(Qt::black);
	linePen.setWidth(2);
	painter.setPen(linePen);

//		1a) Draw the Reference Signal Plot's boundary
	QPoint refSigPlotAreaStart, refSigPlotAreaEnd;
//	^^The upper-left and lower-right coordinates of the Reference Signal plot
	QPoint* p1 = &refSigPlotAreaStart;
	QPoint* p2 = &refSigPlotAreaEnd;
	p1->setX(85);
	p1->setY(80);
	p2->setX(195);
	p2->setY(522);
	painter.drawRect(QRect(*p1,*p2));

	//	1b) Draw the Reference Signal Plot's boundary
	QPoint querySigPlotAreaStart, querySigPlotAreaEnd;
	p1 = &querySigPlotAreaStart;
	p2 = &querySigPlotAreaEnd;
	p1->setX(202);
	p1->setY(528);
	p2->setX(668);
	p2->setY(640);
	painter.drawRect(QRect(*p1,*p2));

	//	1c) Draw the TimeSeries Alignment Plot's boundary
	QPoint TSAPlotAreaStart, TSAPlotAreaEnd;
	p1 = &TSAPlotAreaStart;
	p2 = &TSAPlotAreaEnd;
	p1->setX(refSigPlotAreaEnd.rx() + 7);
	p1->setY(refSigPlotAreaStart.ry());
	p2->setX(querySigPlotAreaEnd.rx());
	p2->setY(refSigPlotAreaEnd.ry());
	painter.drawRect(QRect(*p1,*p2));
		

//	2) Draw Ticks
	//	2a) Draw refSig ticks
	int refSigStartY = 500;
	int refSigEndY = 100;
	int y1, y2;
	y1 = refSigEndY; //b/c signal ends above its starting position
	y2 = refSigStartY;
	int x= refSigPlotAreaStart.rx();
	int numTicks = 4;
	int spacing = ((y2 - y1)/numTicks);
	for(int y = y1; y <= y2; y+=spacing)
	{
 		painter.drawLine(x,y,x-10,y);
	}

	//	2b) Draw querySig ticks
	int querySigStartX = 230;
	int querySigEndX = 630;
	int x1, x2;
	x1 = querySigStartX;
	x2 = querySigEndX;
	spacing = (x2 - x1)/numTicks;
	int y = querySigPlotAreaEnd.ry();	
	for(int x = x1; x <= x2; x+= spacing)
	{
		painter.drawLine(x,y,x,y+10);
	}

//	3) Draw querySig
	std::vector<double> sigVector = myDTW.getFirst().getData();
	// pick 500 points from querySig: start - end/500
	spacing = sigVector.size()/(querySigEndX - querySigStartX);
	// height = qsigstarty-endy * val of selection
	int vscale = querySigPlotAreaStart.ry() - querySigPlotAreaEnd.ry();
	x1 = querySigStartX;
	y1 = querySigPlotAreaEnd.ry() + vscale*sigVector[0];
	for(int i = 1; i<=querySigEndX-querySigStartX; i++)
	{
		y2 = querySigPlotAreaEnd.ry() + vscale*sigVector[i*spacing];
		x2 = x1+1;
		painter.drawLine(x1,y1,x2,y2);
		y1 = y2;
		x1 = x2;
	}

//	4) Draw refSig
	std::vector<double> refVector = myDTW.getSecond().getData();
	//pick 500 points from refSig: (start - end)/500
	spacing = refVector.size()/(refSigEndY - refSigStartY);
	int hscale = refSigPlotAreaStart.rx() - refSigPlotAreaEnd.rx();
	x1 = refSigPlotAreaEnd.rx() - hscale*refVector[0];
	y1 = refSigStartY;
	std::cout<< (refSigStartY - refSigEndY) << std::endl;
	for(int i = 1; i<= (refSigStartY - refSigEndY); i++){
		y2 = y1 - 1;
		x2 = refSigPlotAreaEnd.rx() - hscale*refVector[i*spacing];
		painter.drawLine(x1,y1,x2,y2);
		y1 = y2;
		x1 = x2;
	}
}
