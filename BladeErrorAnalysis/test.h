#ifndef _TEST_H_
#define _TEST_H_

#include"Header.h"

class test
{
public:
	static void testGnuplot();
	static void testPathConvert();
	static void testDataPreProcess();
	static void testSVD();
	static void testMatrixManipulation();
	static void testMatrixAppendVector();
	static void testRandom();
	static void testSwopMatrixColumn();
	static void testSVDResultsSort();
	static void testVector2Matrix(const std::vector<Vector> VectorArray);
	static void testMain();
	static void testIGESFileProcess(std::string fileAddress);
	static void Map2D();
	static void testMap();
	static void testVector2Diag();
};

#endif