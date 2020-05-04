#pragma once
#include "plplot\plstream.h"

class RealTimePlot {

public:
	RealTimePlot();
	void plot(int n,int value, float red, float green, float blue);
	~RealTimePlot();




public:
	PLINT           id1 , n, autoy, acc, nsteps ;
	PLFLT           y1, y2, y3, y4, ymin, ymax, xlab, ylab = 0;
	PLFLT           t, tmin, tmax, tjump, dt, noise = 0;
	PLINT           colbox, collab, colline[4], styline[4];
	PLCHAR_VECTOR   legline[4];



};