#ifndef _DATAMANAGEMENT_H_
#define _DATAMANAGEMENT_H_

#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>
#include<vector>
#include<tuple>
#include<stdlib.h>
#include<stdarg.h>
#include<Windows.h>
#include "mkl.h"
#define PI 3.14159265358979323846

class Matrix;
class Vector;

class Array
{
protected:
	double *mData;
	int mRow, mColumn, mSize, mLD;
public:
	friend class ArrayManipulation;
	Array();
	void show();
	virtual ~Array();
	int getRow();
	int getColumn();
	int getSize();
};
class Matrix:public Array
{
public:
	Matrix();
	Matrix(int expRow, int expColumn);
	Matrix(int expRow, int expColumn, double *tempData);
	Matrix(const Matrix &tempMatrix);
	Matrix& operator=(const Matrix& tempMatrix);
	Matrix operator+(const Matrix& tempMatrix)const;
	Matrix operator-(const Matrix& tempMatrix)const;
	Matrix operator*(const double& tempdouble)const;
	Matrix operator*(const Matrix& tempMatrix)const;
	Matrix operator^(const int& tempInt)const;
	Matrix operator+=(const Matrix& tempMatrix)const;
	~Matrix();
};
class Vector:public Array
{
public:
	Vector();
	Vector(int tempRow);
	Vector(int tempRow, double* tempData);
	Vector(const Vector & tempVector);
	Vector& operator=(const Vector& tempMatrix);
	Vector operator+(const Vector& tempVector)const;
	Vector operator-(const Vector& tempMatrix)const;
	Vector operator*(const double& tempdouble)const;
	Vector operator*(const Vector& tempVector)const;
	Matrix operator*(const Matrix& tempMatrix)const;
	Vector operator+=(const Vector& tempVector)const;
	~Vector();
};
class ArrayManipulation
{
public:
	static int getRowNum(const Matrix& tempMatrix);
	static int getRowNum(const Vector& tempVector);
	static int getColumnNum(const Matrix& tempMatrix);
	static int getColumnNum(const Vector& tempVector);
	static int getSize(const Matrix& tempMatrix);
	static int getSize(const Vector& tempVector);
	static int getLD(const Matrix& tempMatrix);
	static int getLD(const Vector& tempVector);
	static void resize(Matrix& tempMatrix, int rRow, int rColumn);
	static double* getData(const Matrix& tempMatrix);
	static double* getData(const Vector& tempMatrix);
	static Vector getColumn(int& tempColumn, const Matrix& tempMatrix);
	static Matrix transpose(const Matrix& tempMatrix);
	static Matrix transpose(const Vector& tempVector);
	static void inverse(Matrix& tempMatrix);
	static Matrix Vector2Matrix(const Vector* VectorArray);
	static Matrix Vector2Matrix(const std::vector<Vector> VectorArray);
	static Matrix Vector2Matrix(const int& columnNum, const Vector& tempVector);
	static Matrix Vector2Matrix(Vector& tempVector1, ...);
	static Matrix Vector2Diag(Vector& tempVector);
	static Matrix AppendVector(const Matrix& tempMatrix, const Vector& tempVector);
	static Matrix SwopColumn(int firstColumn, int secondColumn, const Matrix& tempMatrix);
	static Vector SwopRow(int firstRow, int secondRow, const Vector& tempVector);
};
typedef std::tuple<Vector, Matrix> PreProcessResults;
typedef std::tuple<Vector, Matrix, Matrix> SVDResults;
typedef std::tuple<Vector, Matrix, Matrix, Vector, Matrix, Matrix> PCAResults;
class DataManipulation
{
public:
	static Vector ImportFile(short& rowNum, std::string fileAddress);
	static Matrix XYZImportFile(short& rowNum, std::string fileAddress);
	static void ExportFile(Matrix& tempMatrix, const std::string fileAddress);
	static void ExportFile(Vector& tempVector, const std::string fileAddress);
	static void XYZExportFile(Matrix& tempMatrix, const std::string fileAddress);
	static void XYZExportFile(Vector& tempVector, const std::string fileAddress);
	static void XYZExportFile(std::vector<double>& tempVector, const std::string fileAddress);
	static void ExportMatlabFile(const Matrix& tempMatrix, const std::string fileAddress);
	static void IGESFileProcess(const std::string sourceFileAddress);
	static void IGESFileProcess(const std::string sourceFileAddress, const std::string destinationFileAddress);
	static PreProcessResults DataPreProcess(const Matrix& dataMatrix);
	static Vector CreatErrorCopy(const Vector& SouceData);
	static Matrix CreatBladeMatrix(const int& bladeNum, const Vector& nominalBlade);
	static SVDResults SVD(const Matrix& tempMatrix);
	static SVDResults SVDResultsSort(SVDResults& tempSVDResults);
	static PCAResults PCA(Matrix& tempMatrix);
	static Matrix CalculateValue(Vector& tempVector);
	static Matrix Map2D(Matrix& tempMatrix);
};

#endif