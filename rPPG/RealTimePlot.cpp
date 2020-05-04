#include "RealTimePlot.h"
#include "plplot\plstream.h"
#include <thread>         
#include <chrono>

RealTimePlot::RealTimePlot() {
	ymin = 205;
	ymax = 220;
	tmin = 0.;
	tmax = 10.;
	tjump = 0.3;
	colbox = 1;
	collab = 3;
	styline[0] = colline[0] = 1;        
	styline[1] = colline[1] = 3;
	styline[2] = colline[2] = 4;
	styline[3] = colline[3] = 5;

	legline[0] = "Red signal";   
	legline[1] = "Green signal";  
	legline[2] = "Blue signal";  
	legline[3] = "detrend red signal";

	xlab = 0.; ylab = 0.25;     

	autoy = 1;                 
	acc = 1;                  

// Initialize plplot
	plsdev("wingcc");
	plinit();
	pladv(0);
	plvsta();


	plstripc(&id1, "bcnst", "bcnstv",
		tmin, tmax, tjump, ymin, ymax,
		xlab, ylab,
		autoy, acc,
		colbox, collab,
		colline, styline, legline,
		"Per frame", " Avg of each channel", "RGB values");


	autoy = 0; 
	acc = 1;  


	y1 = y2 = y3 = y4 = 0.0;
	dt = 0.1;


}

void RealTimePlot::plot(int n,int value, float red, float green, float blue) 
{
	 	
		t = (PLFLT)n * dt;
		plstripa(id1, 0, t, red);
		plstripa(id1, 1, t, green);
		plstripa(id1, 2, t, blue);
		plstripa(id1, 3, t, value);

		
		

}
	


RealTimePlot::~RealTimePlot(){

	plstripd(id1);
	plend();
	exit(0);

}