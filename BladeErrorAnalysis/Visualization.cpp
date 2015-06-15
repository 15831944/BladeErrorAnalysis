#include"Visualization.h"
#include<Windows.h>
Visualization::Visualization()
{
}
Visualization::~Visualization()
{
}
void Visualization::plot(Matrix tempMatrix, int n)
{
	if (ArrayManipulation::getRowNum(tempMatrix) % 3)
	{
		std::cout << "Length of the std::vectors differs" << std::endl;
	}
	else
	{
		std::vector<double> x(ArrayManipulation::getRowNum(tempMatrix) / 3), y(ArrayManipulation::getRowNum(tempMatrix) / 3), z(ArrayManipulation::getRowNum(tempMatrix) / 3);
		for (int i = 0; i < min(ArrayManipulation::getColumnNum(tempMatrix), n); i++)
		{
			for (int j = 0; j <  ArrayManipulation::getRowNum(tempMatrix); j += 3)
			{
				int index = (j / 3);
				x[index] = *(ArrayManipulation::getData(tempMatrix) + j*ArrayManipulation::getRowNum(tempMatrix) + i);
				y[index] = *(ArrayManipulation::getData(tempMatrix) + (j + 1) * ArrayManipulation::getRowNum(tempMatrix) + i);
				z[index] = *(ArrayManipulation::getData(tempMatrix) + (j + 2) * ArrayManipulation::getRowNum(tempMatrix) + i);
			}
			/*std::ostringstream cmdstr;
			cmdstr << "pointtype 7 pointsize 3\n";
			hGnuplot.cmd(cmdstr.str());
			cmdstr << "replot\n";
			hGnuplot.cmd(cmdstr.str());*/
		}
		Gnuplot hGnuplot("points");
		hGnuplot.set_pointsize(3.0);
		std::string xLabel("x"), yLabel("y"), zLabel("z"), title("mode");
		hGnuplot.set_xlabel(xLabel).set_ylabel(yLabel).set_zlabel(zLabel);
		hGnuplot.plot_xyz(x, y, z, title);
		wait_for_key();
	}
}
void Visualization::wait_for_key()
{
	// every keypress registered, also arrow keys
	std::cout << std::endl << "Press any key to continue..." << std::endl;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	_getch();
	return;
}