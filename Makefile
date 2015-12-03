# David Brakman, Alexandru Pana, Nasheya Rahman

# makefile
# use to compile and test the DTW class and plot generator
# and its various components

DTWSIM: main.o Signal.o DTW.o PlotDTW.o
	g++ -o DTWSIM main.o Signal.o DTW.o PlotDTW.o
	
PlotDTW.o: Signal.h DTW.h PlotDTW.h

DTW.o: Signal.h DTW.h

Signal.o: Signal.h

clean:
	/bin/rm -f DTWSIM *.o core
