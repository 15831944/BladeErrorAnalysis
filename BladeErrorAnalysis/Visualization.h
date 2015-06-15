#ifndef _VISUALIZATION_H_
#define _VISUALIZATION_H_

#include<Windows.h>
#include<conio.h>
#include <vector>
#include"DataManagement.h"
#include"Gnuplot.h"

class Visualization
{
public:
	Visualization();
	~Visualization();
	static void plot(Matrix tempMatrix, int n);
	static void wait_for_key();


private:

};



#endif
