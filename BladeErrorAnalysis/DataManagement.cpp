#include"DataManagement.h"

Array::Array()
{
	
}
void Array::show()
{
	for (int i = 0; i < mRow; i++)
	{
		for (int j = 0; j < mColumn; j++)
		{
			std::cout << std::setw(20) << std::setprecision(15) << std::setiosflags(std::ios::left) << *(mData + i*mColumn + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
int Array::getRow()
{
	return mRow;
}
int Array::getColumn()
{
	return mColumn;
}
int Array::getSize()
{
	return mSize;
}
Array::~Array()
{

}

Matrix::Matrix()
{
	mRow = 0;
	mColumn = 0;
	mLD = 0;
	mSize = mRow * mColumn;
	mData = nullptr;
}
Matrix::Matrix(int tempRow, int tempColumn)
{
	mRow = tempRow;
	mColumn = tempColumn;
	mLD = tempColumn;
	mSize = mRow * mColumn;
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		*(mData + i) = 0;
	}
}
Matrix::Matrix(int tempRow, int tempColumn, double *tempMatrix)
{
	mRow = tempRow;
	mColumn = tempColumn;
	mLD = tempColumn;
	mSize = mRow*mColumn;
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		*(mData + i) = *(tempMatrix + i);
	}
}
Matrix::Matrix(const Matrix & tempMatrix)
{
	mRow = tempMatrix.mRow;
	mColumn = tempMatrix.mColumn;
	mLD = tempMatrix.mLD;
	mSize = tempMatrix.mSize;
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		*(mData + i) = *(tempMatrix.mData + i);
	}
}
Matrix& Matrix::operator=(const Matrix& tempMatrix)
{
	if (tempMatrix.mRow != mRow || tempMatrix.mColumn != mColumn)
	{
		mRow = tempMatrix.mRow;
		mColumn = tempMatrix.mColumn;
		mLD = tempMatrix.mColumn;
		mSize = mRow*mColumn;
		delete[] mData;
		mData = new double[mSize];
	}
	for (int i = 0; i < mSize; i++)
	{
		*(mData + i) = *(tempMatrix.mData + i);
	}
	return *this;
}
Matrix Matrix::operator+(const Matrix& tempMatrix)const
{
	if (tempMatrix.mRow == mRow && tempMatrix.mColumn == mColumn)
	{
		Matrix tempResultMatrix(mRow, mColumn);
		for (int i = 0; i < mSize; i++)
		{
			*(tempResultMatrix.mData + i) = *(mData + i) + *(tempMatrix.mData + i);
		}
		return tempResultMatrix;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Matrix Matrix::operator-(const Matrix& tempMatrix)const
{
	if (tempMatrix.mRow == mRow && tempMatrix.mColumn == mColumn)
	{
		Matrix tempResultMatrix(mRow, mColumn);
		for (int i = 0; i < mSize; i++)
		{
			*(tempResultMatrix.mData + i) = *(mData + i) - *(tempMatrix.mData + i);
		}
		return tempResultMatrix;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Matrix Matrix::operator*(const double& tempdouble)const
{
	Matrix tempMatrix(mRow, mColumn);
	for (int i = 0; i < mSize; i++)
	{
		*(tempMatrix.mData + i) = *(mData + i) * tempdouble;
	}
	return tempMatrix;
}
Matrix Matrix::operator*(const Matrix& tempMatrix)const
{
	if (mColumn == tempMatrix.mRow)
	{
		Matrix ResultMatrix(mRow, tempMatrix.mColumn);
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mRow, tempMatrix.mColumn, mColumn, 1.0, mData, mColumn, tempMatrix.mData, tempMatrix.mLD, 0, ResultMatrix.mData, ResultMatrix.mLD);
		return ResultMatrix;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Matrix Matrix::operator^(const int& tempInt)const
{
	if (mRow != mColumn || mRow == 0)
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		if (tempInt == 0)
		{
			for (int i = 0; i < mRow; i++)
			{
				for (int j = 0; j < mRow; j++)
				{
					if (i == j)
					{
						*(mData + i*mRow + j) = 1;
					}
					else
					{
						*(mData + i*mRow + j) = 0;
					}
				}
			}
			return *this;
		}
		else
		{
			Matrix tempMatrix(*this);
			for (int i = 1; i < tempInt; i++)
			{
				tempMatrix = tempMatrix*(*this);
			}
			if (tempInt < 0)
			{
				ArrayManipulation::inverse(tempMatrix);
			}
			return tempMatrix;
		}
	}
}
Matrix Matrix::operator+=(const Matrix& tempMatrix)const
{
	if (tempMatrix.mRow == mRow && tempMatrix.mColumn == mColumn)
	{
		for (int i = 0; i < mSize; i++)
		{
			*(mData + i) += *(tempMatrix.mData + i);
		}
		return *this;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Matrix::~Matrix()
{
	delete[] mData;
	mData = nullptr;
}


Vector::Vector()
{
	mRow = 0;
	mColumn = 1;
	mLD = 1;
	mData = nullptr;
}
Vector::Vector(int tempRow)
{
	mRow = tempRow;
	mColumn = 1;
	mLD = 1;
	mSize = mRow;
	mData = new double[tempRow];
	for (int i = 0; i < tempRow; i++)
	{
		*(mData + i) = 0;
	}
}
Vector::Vector(int tempRow, double* tempVector)
{
	mRow = tempRow;
	mColumn = 1;
	mLD = 1;
	mSize = mRow;
	mData = new double[tempRow];
	for (int i = 0; i < tempRow; i++)
	{
		*(mData + i) = *(tempVector + i);
	}
}
Vector::Vector(const Vector & tempVector)
{
	mRow = tempVector.mRow;
	mColumn = tempVector.mColumn;
	mLD = tempVector.mLD;
	mSize = tempVector.mSize;
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		*(mData + i) = *(tempVector.mData + i);
	}
}
Vector& Vector::operator=(const Vector& tempVect)
{
	if (tempVect.mRow != mRow)
	{
		mRow = tempVect.mRow;
		delete[] mData;
		mData = new double[mRow];
	}
	for (int i = 0; i < mRow; i++)
	{
		*(mData + i) = *(tempVect.mData + i);
	}
	return *this;
}
Vector Vector::operator+(const Vector& tempVector)const
{
	if (tempVector.mRow == mRow)
	{
		Vector tempResultVector(mRow);
		for (int i = 0; i < mRow; i++)
		{
			*(tempResultVector.mData + i) = *(mData + i) + *(tempVector.mData + i);
		}
		return tempResultVector;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Vector Vector::operator-(const Vector& tempVector)const
{
	if (tempVector.mRow == mRow)
	{
		Vector tempResultVector(mRow);
		for (int i = 0; i < mRow; i++)
		{
			*(tempResultVector.mData + i) = *(mData + i) - *(tempVector.mData + i);
		}
		return tempResultVector;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Vector Vector::operator*(const double& tempdouble)const
{
	Vector tempVector(mRow);
	for (int i = 0; i < mRow; i++)
	{
		*(tempVector.mData + i) = *(mData + i) * tempdouble;
	}
	return tempVector;
}
Vector Vector::operator*(const Vector& tempVector)const
{
	if (mRow == tempVector.mRow)
	{
		Vector ResultVector(mRow);
		for (int i = 0; i < mRow; i++)
		{
			ResultVector.mData[i] = mData[i] * tempVector.mData[i];
		}
		return ResultVector;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Vector Vector::operator+=(const Vector& tempVector)const
{
	if (tempVector.mRow == mRow)
	{
		for (int i = 0; i < mRow; i++)
		{
			*(mData + i) += *(tempVector.mData + i);
		}
		return *this;
	}
	else
	{
		std::cerr << "Error: The size is unmatchable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Vector::~Vector()
{
	delete[] mData;
	mData = nullptr;
}

int ArrayManipulation::getRowNum(const Matrix& tempMatrix)
{
	return tempMatrix.mRow;
}
int ArrayManipulation::getRowNum(const Vector& tempVector)
{
	return tempVector.mRow;
}
int ArrayManipulation::getColumnNum(const Matrix& tempMatrix)
{
	return tempMatrix.mColumn;
}
int ArrayManipulation::getColumnNum(const Vector& tempVector)
{
	return tempVector.mColumn;
}
int ArrayManipulation::getSize(const Matrix& tempMatrix)
{
	return tempMatrix.mSize;
}
int ArrayManipulation::getSize(const Vector& tempVector)
{
	return tempVector.mSize;
}
int ArrayManipulation::getLD(const Matrix& tempMatrix)
{
	return tempMatrix.mLD;
}
int ArrayManipulation::getLD(const Vector& tempVector)
{
	return tempVector.mLD;
}
void ArrayManipulation::resize(Matrix& tempMatrix, int rRow, int rColumn)
{
	tempMatrix.mRow = rRow;
	tempMatrix.mColumn = rColumn;
	tempMatrix.mSize = rRow*rColumn;
	tempMatrix.mLD = rRow;
}
double* ArrayManipulation::getData(const Matrix& tempMatrix)
{
	return tempMatrix.mData;
}
double* ArrayManipulation::getData(const Vector& tempMatrix)
{
	return tempMatrix.mData;
}
Vector ArrayManipulation::getColumn(int& tempColumn, const Matrix& tempMatrix)
{
	Vector tempVector(ArrayManipulation::getRowNum(tempMatrix));
	double* tempIndex = ArrayManipulation::getData(tempVector);
	for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
	{
		*(tempIndex + i) = *(ArrayManipulation::getData(tempMatrix) + i*ArrayManipulation::getColumnNum(tempMatrix) + tempColumn);
	}
	return tempVector;
}
Matrix ArrayManipulation::transpose(const Matrix& tempMatrix)
{
	Matrix ResultMatrix(tempMatrix.mColumn, tempMatrix.mRow);
	for (int i = 0; i < tempMatrix.mRow; i++)
	{
		for (int j = 0; j < tempMatrix.mColumn; j++)
		{
			ResultMatrix.mData[j*ResultMatrix.mColumn + i] = tempMatrix.mData[i*tempMatrix.mColumn + j];
		}
	}
	return ResultMatrix;
}
Matrix ArrayManipulation::transpose(const Vector& tempVector)
{
	Matrix tempMatrix(1, tempVector.mRow, tempVector.mData);
	return tempMatrix;
}
void ArrayManipulation::inverse(Matrix& tempMatrix)
{

}
Matrix ArrayManipulation::Vector2Matrix(const Vector* VectorArray)
{
	short columnNum = sizeof(VectorArray) / sizeof(VectorArray[0]);
	std::cout << columnNum << std::endl;
	Matrix tempMatrix(VectorArray[0].mRow,columnNum);
	for (short i = 0; i < VectorArray[0].mRow; i++)
	{
		for (short j = 0; j < columnNum; j++)
		{
			tempMatrix.mData[i*columnNum + j] = VectorArray[j].mData[i];
		}
	}
	return tempMatrix;
}
Matrix ArrayManipulation::Vector2Matrix(const std::vector<Vector> VectorArray)
{
	Matrix tempMatrix(VectorArray[0].mRow, VectorArray.size());
	for (short i = 0; i < VectorArray[0].mRow; i++)
	{
		for (short j = 0; j < VectorArray.size(); j++)
		{
			tempMatrix.mData[i*VectorArray.size() + j] = VectorArray[j].mData[i];
		}
	}
	return tempMatrix;
}
Matrix ArrayManipulation::Vector2Matrix(const int& columnNum, const Vector& tempVector)
{
	Matrix tempMatrix(tempVector.mRow, columnNum);
	for (int i = 0; i < tempVector.mRow; i++)
	{
		for (int j = 0; j < columnNum; j++)
		{
			*(tempMatrix.mData + i*columnNum + j) = *(tempVector.mData + i);
		}
	}
	return tempMatrix;
}
Matrix ArrayManipulation::Vector2Matrix(Vector& tempVector1, ...)
{
	Matrix tempMatrix;
	return tempMatrix;
}
Matrix ArrayManipulation::Vector2Diag(Vector& tempVector)
{
	Matrix tempMatrix(tempVector.mRow, tempVector.mRow);
	for (int i = 0; i < tempVector.mRow; i++)
	{
		tempMatrix.mData[i*tempVector.mRow + i] = tempVector.mData[i];
	}
	//tempMatrix.show();
	return tempMatrix;
}
Matrix ArrayManipulation::AppendVector(const Matrix& tempMatrix, const Vector& tempVector)
{
	Matrix newMatrix(tempMatrix.mRow, tempMatrix.mColumn + 1);
	if (tempMatrix.mRow != tempVector.mRow)
	{
		std::cout << "Sorry, the columns don't match" << std::endl;
	}
	else
	{
		for (int i = 0; i < newMatrix.mSize; i++)
		{
			if ((i + 1) % newMatrix.mColumn == 0)
			{
				newMatrix.mData[i] = tempVector.mData[i / newMatrix.mColumn];
			}
			else
			{
				newMatrix.mData[i] = tempMatrix.mData[tempMatrix.mColumn*(i / newMatrix.mColumn) + i % newMatrix.mColumn];
			}
		}
	}
	return newMatrix;
}
Matrix ArrayManipulation::SwopColumn(int firstColumn, int secondColumn, const Matrix& tempMatrix)
{
	Vector tempVector = ArrayManipulation::getColumn(firstColumn, tempMatrix);
	for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
	{
		ArrayManipulation::getData(tempMatrix)[i*ArrayManipulation::getColumnNum(tempMatrix) + firstColumn] = ArrayManipulation::getData(tempMatrix)[i*ArrayManipulation::getColumnNum(tempMatrix) + secondColumn];
		ArrayManipulation::getData(tempMatrix)[i*ArrayManipulation::getColumnNum(tempMatrix) + secondColumn] = ArrayManipulation::getData(tempVector)[i];
	}
	return tempMatrix;
}
Vector ArrayManipulation::SwopRow(int firstRow, int secondRow, const Vector& tempVector)
{
	double temp = ArrayManipulation::getData(tempVector)[firstRow];
	ArrayManipulation::getData(tempVector)[firstRow] = ArrayManipulation::getData(tempVector)[secondRow];
	ArrayManipulation::getData(tempVector)[secondRow] = temp;
	return tempVector;
}

Vector DataManipulation::ImportFile(short& rowNum, std::string fileAddress)
{
	std::ifstream in(fileAddress);
	char line[256];
	double* data = new double[3 * rowNum];
	short count(0);
	if (!in.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
		in.close();
		delete data;
		return errno;
	}
	else
	{
		for (count = 0; count < rowNum; count++)
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
				p = strtok_s(line, " ", &pNext);
				*(data + 3 * count) = atof(p);
				p = strtok_s(NULL, " ", &pNext);
				*(data + 3 * count + 1) = atof(p);
				p = strtok_s(NULL, " ", &pNext);
				*(data + 3 * count + 2) = atof(p);
			}
		}
		in.close();
		Vector vData(3 * rowNum, data);
		delete data;
		return vData;
	}
}
Matrix DataManipulation::XYZImportFile(short& rowNum, std::string fileAddress)
{
	std::ifstream in(fileAddress);
	char line[80];
	double* data = new double[3 * rowNum];
	short count(0);
	if (!in.is_open())
	{
		std::cout << "Sorry, the input file is not exist." << std::endl;
		in.close();
		delete data;
		return Matrix();
	}
	else
	{
		for (count = 0; count < rowNum; count++)
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
				*(data + 3 * count) = atof(p);
				p = strtok_s(NULL, "\t", &pNext);
				*(data + 3 * count + 1) = atof(p);
				*(data + 3 * count + 2) = atof(pNext);
			}
		}
		in.close();
		Matrix mData(rowNum, 3, data);
		delete data;
		return mData;
	}
}
void DataManipulation::ExportFile(Matrix& tempMatrix, const std::string fileAddress)
{
	std::ofstream out(fileAddress);
	if (!out.is_open())
	{
		std::cout << "Sorry, the output file is not exist." << std::endl;
		out.close();
	}
	else
	{
		for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
		{
			for (int j = 0; j < ArrayManipulation::getColumnNum(tempMatrix); j++)
			{
				out.width(20);
				out.precision(15);
				out << std::left << ArrayManipulation::getData(tempMatrix)[i*ArrayManipulation::getColumnNum(tempMatrix) + j] << '\t';
			}
			out << std::endl;
		}
		out.close();
	}
}
void DataManipulation::ExportFile(Vector& tempVector, const std::string fileAddress)
{
	std::ofstream out(fileAddress);
	if(!out.is_open())
	{
		std::cout << "Sorry, the output file is not exist." << std::endl;
		out.close();
	}
	else
	{
		for (int i = 0; i < ArrayManipulation::getRowNum(tempVector); i++)
		{
			out << ArrayManipulation::getData(tempVector)[i] << std::endl;
		}
		out.close();
	}
}
void DataManipulation::XYZExportFile(Matrix& tempMatrix, const std::string fileAddress)
{
	for (int i = 0; i < ArrayManipulation::getColumnNum(tempMatrix); i++)
	{
		char buffer[10];
		sprintf_s(buffer, "%d", i + 1);
		std::string fileName = fileAddress + buffer + ".txt";
		std::ofstream out(fileName);
		if (!out.is_open())
		{
			std::cout << "Sorry, the file is not exist." << std::endl;
			out.close();
		}
		else
		{
			Vector tempVector = ArrayManipulation::getColumn(i,tempMatrix);
			for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
			{
				out.width(20);
				out.precision(15);
				out << std::left << ArrayManipulation::getData(tempVector)[i] << '\t';
				if ((i + 1) % 3 == 0)
				{
					out << std::endl;
				}
			}
			out.close();
		}
	}
}
void DataManipulation::XYZExportFile(Vector& tempVector, const std::string fileAddress)
{
	std::ofstream out(fileAddress);
	if (!out.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
		out.close();
	}
	else
	{
		for (int i = 0; i < ArrayManipulation::getRowNum(tempVector); i++)
		{
			out.width(20);
			out.precision(15);
			out << std::left << ArrayManipulation::getData(tempVector)[i] << '\t';
			if ((i + 1) % 3 == 0)
			{
				out << std::endl;
			}
		}
		out.close();
	}
}
void DataManipulation::XYZExportFile(std::vector<double>& tempVector, const std::string fileAddress)
{
	std::ofstream out(fileAddress);
	if (!out.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
		out.close();
	}
	else
	{
		for (int i = 0; i < tempVector.size(); i++)
		{
			out.width(20);
			out.precision(15);
			out << std::left << tempVector[i] << '\t';
			if ((i + 1) % 3 == 0)
			{
				out << std::endl;
			}
		}
		out.close();
	}
}
void DataManipulation::ExportMatlabFile(const Matrix& tempMatrix, const std::string fileAddress)
{
	std::ofstream out(fileAddress);
	if (!out.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
	}
	else
	{
		for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
		{
			for (int j = 0; j < ArrayManipulation::getColumnNum(tempMatrix); j++)
			{
				//out.width(20);
				out.precision(15);
				out << std::left << ArrayManipulation::getData(tempMatrix)[i*ArrayManipulation::getColumnNum(tempMatrix) + j] << ",";
			}
			out << ";";
		}
		out.close();
	}
}
void DataManipulation::IGESFileProcess(const std::string sourceFileAddress)
{
	std::ifstream in(sourceFileAddress);
	char line[128];
	if (!in.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
		in.close();
	}
	else
	{
		std::vector<double> PointsXYZValue = std::vector<double>(0);
		while (!in.eof())
		{
			char* pNext(nullptr);
			char* p(nullptr);
			std::string entityFlag;
			in.getline(line, sizeof(line));
			if (line[72] == 'P')
			{
				entityFlag = strtok_s(line, ",", &pNext);
				if (entityFlag == "116")
				{
					char* pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
					pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
					pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
				}
			}
		}
		in.close();
		std::string destinationFileAddress = sourceFileAddress;
		destinationFileAddress.resize(destinationFileAddress.find('.'));
		destinationFileAddress += "Result.txt";
		DataManipulation::XYZExportFile(PointsXYZValue, destinationFileAddress);
	}
}
void DataManipulation::IGESFileProcess(const std::string sourceFileAddress, const std::string destinationFileAddress)
{
	std::ifstream in(sourceFileAddress);
	char line[128];
	if (!in.is_open())
	{
		std::cout << "Sorry, the file is not exist." << std::endl;
		in.close();
	}
	else
	{
		std::vector<double> PointsXYZValue = std::vector<double>(0);
		while (!in.eof())
		{
			char* pNext(nullptr);
			char* p(nullptr);
			std::string entityFlag;
			in.getline(line, sizeof(line));
			if (line[73] == 'P')
			{
				entityFlag = strtok_s(line, ",", &pNext);
				if (entityFlag == "116")
				{
					char* pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
					pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
					pointValue = strtok_s(NULL, ",", &pNext);
					PointsXYZValue.push_back(atof(pointValue));
				}
			}
		}
		in.close();
		DataManipulation::XYZExportFile(PointsXYZValue, destinationFileAddress);
	}
}
PreProcessResults DataManipulation::DataPreProcess(const Matrix& dataMatrix)
{
	Vector MeanVector(ArrayManipulation::getRowNum(dataMatrix));
	for (int i = 0; i < ArrayManipulation::getColumnNum(dataMatrix); i++)
	{
		MeanVector += ArrayManipulation::getColumn(i,dataMatrix);
	}
	MeanVector = MeanVector * (1.0 / double(ArrayManipulation::getColumnNum(dataMatrix)));
	Matrix tempMatrix = ArrayManipulation::Vector2Matrix(ArrayManipulation::getColumnNum(dataMatrix), MeanVector);
	tempMatrix = ArrayManipulation::transpose(dataMatrix - tempMatrix);
	return PreProcessResults(MeanVector, tempMatrix);
}
Vector DataManipulation::CreatErrorCopy(const Vector& tempVector)
{
	double* ErrorCopy = new double[ArrayManipulation::getRowNum(tempVector)];
	srand((unsigned)time(NULL));
	for (int i = 0; i < ArrayManipulation::getRowNum(tempVector); i++)
	{
		//ErrorCopy[i] = ArrayManipulation::getData(tempVector)[i] + (((0.2 * rand()) / double(RAND_MAX)) - 0.1);
		ErrorCopy[i] = (((0.2 * rand()) / double(RAND_MAX)) - 0.1);
	}
	Vector vErrorCopy(ArrayManipulation::getRowNum(tempVector), ErrorCopy);
	delete ErrorCopy;
	return vErrorCopy;
}
Matrix DataManipulation::CreatBladeMatrix(const int& bladeNum, const Vector& nominalBlade)
{
	std::cout << "生成第" << 1 << "个叶片\t";
	Matrix BladeMatrix = ArrayManipulation::Vector2Matrix(1, DataManipulation::CreatErrorCopy(nominalBlade));
	std::cout << "OK!" << std::endl;
	for (int i = 1; i < bladeNum; i++)
	{
		std::cout << "生成第" << i + 1 << "个叶片\t";
		_sleep(1500);
		BladeMatrix = ArrayManipulation::AppendVector(BladeMatrix, DataManipulation::CreatErrorCopy(nominalBlade));
		std::cout << "OK!" << std::endl;
	}
	return BladeMatrix;
}
SVDResults DataManipulation::SVD(const Matrix& tempMatrix)
{
	int tempRow = ArrayManipulation::getRowNum(tempMatrix);
	int tempColumn = ArrayManipulation::getColumnNum(tempMatrix);
	int tempSize = ArrayManipulation::getSize(tempMatrix);
	int tempLD = ArrayManipulation::getLD(tempMatrix);
	int k = min(tempRow, tempColumn);
	int info;
	Matrix uMatrix(tempMatrix);
	Vector D(k);
	double *E = new double[k - 1];
	double *tauq = new double[k];
	double *taup = new double[k];
	double C[3];
	char uplo;
	if (tempRow >= tempColumn)
	{
		uplo = 'U';
	}
	else
	{
		uplo = 'L';
	}
	info = LAPACKE_dgebrd(LAPACK_ROW_MAJOR, tempRow, tempColumn, ArrayManipulation::getData(uMatrix), tempLD, ArrayManipulation::getData(D), E, tauq, taup);
	Matrix vMatrix(uMatrix);
	info = LAPACKE_dorgbr(LAPACK_ROW_MAJOR, 'Q', tempRow, k, tempColumn, ArrayManipulation::getData(uMatrix), k, tauq);
	info = LAPACKE_dorgbr(LAPACK_ROW_MAJOR, 'P', k, tempColumn, tempRow, ArrayManipulation::getData(vMatrix), tempColumn, taup);
	info = LAPACKE_dbdsqr(LAPACK_ROW_MAJOR, uplo, k, tempColumn, tempRow, 0, ArrayManipulation::getData(D), E, ArrayManipulation::getData(vMatrix), tempColumn, ArrayManipulation::getData(uMatrix), k, C, 0);
	/*if (uplo == 'U')
	{
		ArrayManipulation::resize(vMatrix, tempColumn, tempColumn);
	}
	else if (uplo == 'L')
	{
		ArrayManipulation::resize(uMatrix, tempRow, tempRow);
	}*/
	SVDResults tempResults(D, uMatrix, vMatrix);
	delete[] taup;
	delete[] tauq;
	delete[] E;

	return tempResults;
}
SVDResults DataManipulation::SVDResultsSort(SVDResults& tempSVDResults)
{
	Vector S = std::get<0>(tempSVDResults);
	Matrix U = std::get<1>(tempSVDResults);
	Matrix V = std::get<2>(tempSVDResults);
	for (int i = ArrayManipulation::getRowNum(S); i > 0; i--)
	{
		double Min = ArrayManipulation::getData(S)[0];
		short countRow(0);
		for (int j = 0; j < i; j++)
		{
			if (ArrayManipulation::getData(S)[j] < Min)
			{
				countRow = j;
				Min = ArrayManipulation::getData(S)[j];
			}
		}
		ArrayManipulation::SwopRow(countRow, i - 1, S);
		ArrayManipulation::SwopColumn(countRow, i - 1, U);
		ArrayManipulation::SwopColumn(countRow, i - 1, V);
	}
	SVDResults tempResults(S, U, V);
	return tempResults;
}
PCAResults DataManipulation::PCA(Matrix& tempMatrix)
{
	PreProcessResults ProcessResults = DataManipulation::DataPreProcess(tempMatrix);
	Vector MeanBlade = std::get<0>(ProcessResults);
	Matrix ErrorMatrix = std::get<1>(ProcessResults);
	SVDResults tempResult = DataManipulation::SVD(ErrorMatrix);
	Vector S = std::get<0>(tempResult)*sqrt(1 / (double)(ArrayManipulation::getColumnNum(tempMatrix) - 1));
	//S.show();
	Matrix U = std::get<1>(tempResult);
	//U.show();
	Matrix V = std::get<2>(tempResult);
	//V.show();
	Matrix ErrorModeMatrix = ArrayManipulation::transpose(V)*ArrayManipulation::Vector2Diag(S);
	//ErrorMatrix.show();
	PCAResults tempPCAResults(S, U, V, MeanBlade, ArrayManipulation::transpose(ErrorMatrix), ErrorModeMatrix);
	return tempPCAResults;
}
Matrix DataManipulation::CalculateValue(Vector& tempVector)
{
	double totleValue(0);
	for (int i = 0; i < ArrayManipulation::getRowNum(tempVector); i++)
	{
		totleValue += ArrayManipulation::getData(tempVector)[i];
	}
	Matrix valueMatrix(ArrayManipulation::getRowNum(tempVector), 3);
	double aggregateValue = 0;
	for (int i = 0; i < ArrayManipulation::getRowNum(tempVector); i++)
	{
		ArrayManipulation::getData(valueMatrix)[i * 3] = i + 1;
		ArrayManipulation::getData(valueMatrix)[i * 3 + 1] = ArrayManipulation::getData(tempVector)[i] / totleValue;
		aggregateValue += ArrayManipulation::getData(valueMatrix)[i * 3 + 1];
		ArrayManipulation::getData(valueMatrix)[i * 3 + 2] = aggregateValue;
	}
	return valueMatrix;
}
Matrix DataManipulation::Map2D(Matrix& tempMatrix)
{
	if (ArrayManipulation::getColumnNum(tempMatrix) != 3)
	{
		std::cout << "What are you 弄啥勒！" << std::endl;
		return Matrix();
	}
	else
	{
		Matrix MappedMatrix(ArrayManipulation::getRowNum(tempMatrix), 2);
		double* r = new double[ArrayManipulation::getRowNum(tempMatrix)];
		double* o = new double[ArrayManipulation::getRowNum(tempMatrix)];
		double* z = new double[ArrayManipulation::getRowNum(tempMatrix)];
		double* m = new double[ArrayManipulation::getRowNum(tempMatrix)];
		short sng(1);
		double length(0.0),maxz(0.0);
		for (int i = 0; i < ArrayManipulation::getRowNum(tempMatrix); i++)
		{
			r[i] = sqrt(ArrayManipulation::getData(tempMatrix)[i * 3 + 0] * ArrayManipulation::getData(tempMatrix)[i * 3 + 0] + ArrayManipulation::getData(tempMatrix)[i * 3 + 1] * ArrayManipulation::getData(tempMatrix)[i * 3 + 1]);
			//std::cout << "r[" << i << "]=" << r[i] << std::endl;
			o[i] = atan(ArrayManipulation::getData(tempMatrix)[i * 3 + 1] / ArrayManipulation::getData(tempMatrix)[i * 3 + 0]) / PI * 180.0;
			/*if (o[i] < 0)
			{
				o[i] += 180;
			}*/
			//std::cout << "o[" << i << "]=" << o[i] << std::endl;
			z[i] = ArrayManipulation::getData(tempMatrix)[i * 3 + 2];
			if (maxz<z[i])
			{
				maxz = z[i];
				sng = 1;
			}
			else
			{
				sng = -1;
			}
			//std::cout << "z[" << i << "]=" << z[i] << std::endl;
			if (i > 0)
			{
				length += sng*sqrt((r[i] - r[i - 1]) * (r[i] - r[i - 1]) + (z[i] - z[i - 1]) * (z[i] - z[i - 1]));
			}
			m[i] = length;
			ArrayManipulation::getData(MappedMatrix)[i * 2 + 1] = r[i] * o[i];
			//std::cout << "r[" << i << "]*o[" << i << "]=" << r[i] * o[i] << std::endl;
			ArrayManipulation::getData(MappedMatrix)[i * 2 + 0] = m[i];
			//std::cout << "m[" << i << "]=" << m[i] << std::endl;
		}
		return MappedMatrix;
	}
}