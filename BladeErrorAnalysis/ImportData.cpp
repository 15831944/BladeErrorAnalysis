#include<iostream>
#include<fstream>
#include<string>
#include"Header.h"
using namespace std;

double* ImportFile()
{
	ifstream in(FileAdress); 
	char line[80];
	double* data = new double[2700];
	short count(0);
	if (!in.is_open())
	{
		std::cout << "Sorry, the file is not exist." << endl;
	}
	else
	{
		for (count = 0; count < 2700; count += 3)
		{
			char* pNext = NULL;
			char* p(nullptr);
			in.getline(line, sizeof(line));
			if (line == NULL)
			{
				break;
			}
			else
			{
				p = strtok_s(line, "\t", &pNext);
				*(data + count) = atof(p);
				p = strtok_s(NULL, "\t", &pNext);
				*(data + count + 1) = atof(p);
				*(data + count + 2) = atof(pNext);
			}
		}
	}
	return data;
} 