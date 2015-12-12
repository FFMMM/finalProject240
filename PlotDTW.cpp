#include "PlotDTW.h"
#include "ui_PlotDTW.h"

#include <math.h> //for rounding

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

void PlotDTW::setDTW(DTW aDTW)
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
		
	//1d) Write the labels
	QString referenceString = QString::fromStdString("Reference Index");
	QString queryString = QString::fromStdString("Query Index");
	QString title = QString::fromStdString("Timeseries Alignment");
	
	painter.save();
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(16);
	painter.setFont(font);
	painter.drawText(330, 50, title);
	painter.restore();
	
	painter.save();
 	painter.rotate(-90);
	painter.drawText(-350, 40, referenceString);
	painter.restore();
	
	painter.drawText(390, 690, queryString);

//	2) Draw Ticks
	//	2a) Draw refSig ticks
	findTickValues();

	int refSigStartY = 500;
	int refSigEndY = 100;
	int y1, y2;
	y1 = refSigEndY; //End is above start
	y2 = refSigStartY;
	int x= refSigPlotAreaStart.rx();
	int spacing = ((y2 - y1)/(TICKNUM-1));

	int i=0;

	for(int y = y1; y <= y2; y+=spacing)
	{
 		painter.drawLine(x,y,x-10,y);
 		painter.save();
 		painter.rotate(-90);
 		QString num = QString::number(labelReference[TICKNUM-i-1]);
		painter.drawText(-(y+num.length()*5), x-15, num);
 		painter.restore();
 		i++;
	}
	
	int refSigStartX = 85;
	int refSigEndX = 195;
	int widthRef=refSigEndX-refSigStartX;
	int offset1=5;
	int spacingX=(widthRef-offset1*2)/(TICKNUMX-1);
	int yRef= refSigPlotAreaStart.ry();
	
	i=0;
	double numX=1.0;
	
	for(int k=refSigStartX+offset1; k<=refSigEndX; k+=spacingX){
		painter.drawLine(k,yRef,k,yRef-5);
		
		if(i%2==0){
			QString num = QString::number(numX-i*0.2);
			painter.drawText(k-num.length()*3, yRef-10, num);
		}
		
		i++;
	} 
	

	//	2b) Draw querySig ticks
	int querySigStartX = 230;
	int querySigEndX = 630;
	int x1, x2;
	x1 = querySigStartX;
	x2 = querySigEndX;
	spacing = (x2 - x1)/(TICKNUM-1);
	int y = querySigPlotAreaEnd.ry();

	i=0;	

	for(int x = x1; x <= x2; x+= spacing)
	{
		painter.drawLine(x,y,x,y+10);
		QString num = QString::number(labelQuery[i]);
		painter.drawText(x-num.length()*5, y+25, num);
		i++;
	}
	
	int querySigStartY = 528;
	int querySigEndY = 640;
	int heightQuery=querySigEndY-querySigStartY;
	int spacingY=(heightQuery-offset1*2)/(TICKNUMX-1);
	int xRef= querySigPlotAreaStart.rx();
	
	i=0;
	double numY=1;
	
	for(int k=querySigStartY+offset1; k<=querySigEndY; k+=spacingY){
		painter.drawLine(xRef,k,xRef-5,k);
		
		if((i-1)%2==0){
			painter.save();
	 		painter.rotate(-90);
	 		QString num = QString::number(numY-i*0.2);
			painter.drawText(-(k+num.length()*3), xRef-10, num);
	 		painter.restore();
		}
		
		i++;
	} 



//	3) Draw querySig
	std::vector<double> sigVector = myDTW.getFirst().getData();
	// pick 500 points from querySig: start - end/400
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
	sigVector = myDTW.getSecond().getData();
	//pick 400 points from refSig: (start - end)/400
	spacing = sigVector.size()/(refSigStartY - refSigEndY);
	int hscale = refSigPlotAreaEnd.rx() - refSigPlotAreaStart.rx();
	x1 = refSigPlotAreaEnd.rx() - hscale*sigVector[0];
	y1 = refSigStartY;
	for(int i = 1; i<= (refSigStartY - refSigEndY); i++){
		y2 = y1 - 1;
		x2 = refSigPlotAreaEnd.rx() - hscale*sigVector[i*spacing];
		painter.drawLine(x1,y1,x2,y2);
		y1 = y2;
		x1 = x2;
	}

//	5) Draw timeSeries Alignment
	sigVector = myDTW.getComparison();
	//no "spacing" term here; hopefully drawline (x1,y1,x1,y1) does nothing
	double hscaleDBL = (querySigEndX - querySigStartX)/((double) myDTW.getFirst().getData().size());
	double vscaleDBL = (refSigStartY - refSigEndY)/((double) myDTW.getSecond().getData().size());
	 
	for(int i = sigVector.size()
	painter.drawLine(querySigStartX,refSigStartY,querySigEndX,refSigEndY);

}


void PlotDTW::findTickValues()
{
	Signal query = myDTW.getFirst();
	Signal reference = myDTW.getSecond();

	std::vector<double> queryVec = query.getData();
	std::vector<double> referenceVec = reference.getData();

	for(int i=0; i<TICKNUM; i++){
		labelQuery[i] = ((double)queryVec.size()/(TICKNUM-1))*i;
		labelReference[i] = ((double)referenceVec.size()/(TICKNUM-1))*i;
	}
}
