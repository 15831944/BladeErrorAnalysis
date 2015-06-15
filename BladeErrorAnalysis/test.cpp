#include"test.h"
void test::testGnuplot()
{
	double Array[] = { 1, 0, 1, 1, 0, 1, 0, 1, -1 };
	Matrix MSD(3, 3, Array);
	MSD.show();
	Visualization::plot(MSD, 3);
}
void test::testPathConvert()
{
	// convert string to char*
	std::string path("./gnuplot");
	int StringLength = path.length() + 1;
	char* index = new char[StringLength];
	for (int i = 0; i < StringLength; i++)
	{
		*(index + i) = path[i];
	}
	*(index + StringLength) = '\0';
	// convert char* to TCHAR
	DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, index, -1, NULL, 0);
	wchar_t *pwText = new wchar_t[dwNum];
	if (!pwText)
	{
		delete[]pwText;
	}
	MultiByteToWideChar(CP_ACP, 0, index, -1, pwText, dwNum);
	LPCTSTR lpFileName(pwText);
	// convert RP to AP
	TCHAR  buffer[_MAX_PATH] = TEXT("");
	GetFullPathName(lpFileName, _MAX_PATH, buffer, NULL);
	//change TCHAR to string
	DWORD n = WideCharToMultiByte(CP_ACP, NULL, buffer, -1, NULL, 0, NULL, FALSE);
	char *name = new char[n];
	WideCharToMultiByte(CP_OEMCP, NULL, buffer, -1, name, n, NULL, FALSE);
	std::string temp = name;
	//std::cout << temp << std::endl;
	delete[]pwText;
	delete[]name;
}
void test::testDataPreProcess()
{
	double a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix A(3, 3, a);
	A.show();
	PreProcessResults tempResults = DataManipulation::DataPreProcess(A);
	Vector MeanVector = std::get<0>(tempResults);
	Matrix ErrorMatrix = std::get<1>(tempResults);
	std::cout << "The MeanVector is:" << std::endl;
	MeanVector.show();
	std::cout << "The ErrorMatrix is:" << std::endl;
	ErrorMatrix.show();
}
void test::testSVD()
{
	double Array[] = { 1, 2, 3, 4, 5, 6};
	Matrix MSD(3, 2, Array);
	MSD.show();
	SVDResults GETBACK = DataManipulation::SVD(MSD);
	Vector S = std::get<0>(GETBACK);
	Matrix U = std::get<1>(GETBACK);
	Matrix V = std::get<2>(GETBACK);
}
void test::testMatrixManipulation()
{
	
}
void test::testMatrixAppendVector()
{
	double a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double b[] = { 1, 2, 3 };
	Matrix A(3, 3, a);
	Vector B(3, b);
	Matrix C = ArrayManipulation::AppendVector(A, B);
	C.show();
}
void test::testRandom()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; i++)
	{
		std::cout << (((0.2 * rand()) / double(RAND_MAX)) - 0.1) << std::endl;
	}
}
void test::testSwopMatrixColumn()
{
	double Array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix MSD(3, 3, Array);
	ArrayManipulation::SwopColumn(0, 2, MSD);
	std::cout << "The result of swop column is:" << std::endl;
	MSD.show();
}
void test::testSVDResultsSort()
{
	double Array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Vector S(3, Array);
	Matrix U(3, 3, Array);
	Matrix V(3, 3, Array);
	SVDResults tempSVDResults(S, U, V);
	tempSVDResults = DataManipulation::SVDResultsSort(tempSVDResults);
	S = std::get<0>(tempSVDResults);
	U = std::get<1>(tempSVDResults);
	V = std::get<2>(tempSVDResults);
	S.show();
	U.show();
	V.show();
}
void test::testVector2Matrix(const std::vector<Vector> VectorArray)
{
	Matrix tempMatrix = ArrayManipulation::Vector2Matrix(VectorArray);
	tempMatrix.show();
}
void test::testMain()
{
	short num = 2000;
	short streamlinenum = 5;
	int bladeNum = 12;
	char buffer[10];
	std::string fileAddress = "C:/BA/Data/Streamline";
	//std::string fileAddress = "C:/Users/Stark/OneDrive/个人发展战略计划/上海交通大学/科研/叶片加工/模型/采样点集/ew1312051-1/流线模型/GRIP得到的数据/Streamline";
	std::string tempFileAddress;
	std::string fileName;
	std::vector<Vector>* streamlinegroups = new std::vector<Vector>[5];
	for (int i = 0; i < streamlinenum; i++)
	{
		std::vector<Vector> streamlines = std::vector<Vector>(0);
		sprintf_s(buffer, "%d", i + 1);
		tempFileAddress = fileAddress + buffer + "/blade";
		for (int j = 0; j < bladeNum; j++)
		{
			sprintf_s(buffer, "%d", j + 1);
			fileName = tempFileAddress + buffer + ".txt";
			streamlines.push_back(DataManipulation::ImportFile(num, fileName));
		}
		streamlinegroups[i] = streamlines;
	}
	fileAddress = "C:/BA/ProcessData/Streamline";
	//fileAddress = "C:/Users/Stark/OneDrive/个人发展战略计划/上海交通大学/科研/叶片加工/实验/6.9实验/Streamline";
	for (int i = 0; i < streamlinenum; i++)
	{
		sprintf_s(buffer, "%d", i + 1);
		tempFileAddress = fileAddress + buffer + "/";
		Matrix BladeMatrix = ArrayManipulation::Vector2Matrix(streamlinegroups[i]);
		fileName = tempFileAddress + "Streamline" + buffer + "Matrix.txt";
		DataManipulation::ExportFile(BladeMatrix, fileName);
		PCAResults pcaResults = DataManipulation::PCA(BladeMatrix);
		Vector S = std::get<0>(pcaResults);
		Matrix U = std::get<1>(pcaResults);
		//std::cout << "the row of U is " << ArrayManipulation::getRowNum(U) << ", and the column of U is " << ArrayManipulation::getColumnNum(U) << std::endl;
		Matrix V = std::get<2>(pcaResults);
		//std::cout << "the row of V is " << ArrayManipulation::getRowNum(V) << ", and the column of V is " << ArrayManipulation::getColumnNum(V) << std::endl;
		Vector MeanBlade = std::get<3>(pcaResults);
		Matrix ErrorMatrix = std::get<4>(pcaResults);
		Matrix ErrorModeMatrix = std::get<5>(pcaResults);
		// 取前12阶模态
		/*std::vector<Vector> getMode = std::vector<Vector>(0);
		for (int i = 0; i < bladeNum; i++)
		{
			getMode.push_back(ArrayManipulation::getColumn(i, V));
		}
		V = ArrayManipulation::Vector2Matrix(getMode);*/
		fileName = tempFileAddress + "AverageStreamline" + buffer + ".txt";
		DataManipulation::XYZExportFile(MeanBlade, fileName);
		fileName = tempFileAddress + "Streamline" + buffer + "ErrorMatrix.txt";
		DataManipulation::ExportFile(ErrorMatrix, fileName);
		fileName = tempFileAddress + "Streamline" + buffer + "ErorrMode";
		DataManipulation::XYZExportFile(ErrorModeMatrix, fileName);
		BladeMatrix = ErrorModeMatrix + ArrayManipulation::Vector2Matrix(ArrayManipulation::getColumnNum(ErrorModeMatrix), MeanBlade);
		fileName = tempFileAddress + "Streamline" + buffer + "Mode";
		DataManipulation::XYZExportFile(BladeMatrix, fileName);
		BladeMatrix = ErrorModeMatrix * 5 + ArrayManipulation::Vector2Matrix(ArrayManipulation::getColumnNum(ErrorModeMatrix), MeanBlade);
		fileName = tempFileAddress + "AmplifyingStreamline" + buffer + "Mode";
		DataManipulation::XYZExportFile(BladeMatrix, fileName);
		fileName = tempFileAddress + "Streamline" + buffer + "CumulativeProportion.txt";
		DataManipulation::ExportFile(DataManipulation::CalculateValue(S*S), fileName);
	}
}
void test::testIGESFileProcess(std::string fileAddress)
{
	for (short i = 2; i <= 2; i++)
	{
		char buffer[10];
		sprintf_s(buffer, "%d", i);
		const std::string fileName = fileAddress + buffer + "-";
		for (short j = 1; j <= 12; j++)
		{
			sprintf_s(buffer, "%d", j);
			DataManipulation::IGESFileProcess(fileName + buffer + ".igs");
		}
	}
}
void test::testMap()
{
	short num = 2000;
	int bladeNum = 12;
	std::string iFileAddress = "C:/Users/Stark/OneDrive/个人发展战略计划/上海交通大学/科研/叶片加工/实验/6.9实验/Streamline1/";
	std::string oFileAddress = "C:/Users/Stark/OneDrive/个人发展战略计划/上海交通大学/科研/叶片加工/实验/6.9实验/流线1/";
	std::string iFileName, oFileName;
	std::vector<Matrix> BladeVectorArray = std::vector<Matrix>(0);
	iFileName = iFileAddress + "AverageStreamline1.txt";
	oFileName = oFileAddress + "流线1平均.txt";
	DataManipulation::ExportFile(DataManipulation::Map2D(DataManipulation::XYZImportFile(num, iFileName)), oFileName);
	for (int i = 0; i < bladeNum; i++)
	{
		char buffer[10];
		sprintf_s(buffer, "%d", i + 1);
		iFileName = iFileAddress + "Streamline1Mode" + buffer + ".txt";
		oFileName = oFileAddress + "流线1模态" + buffer + ".txt";
		DataManipulation::ExportFile(DataManipulation::Map2D(DataManipulation::XYZImportFile(num, iFileName)), oFileName);
	}
}
void test::Map2D()
{
	short num = 3;
	std::string iFileName="C:/Users/Stark/Desktop/test.txt";
	std::string oFileName = "C:/Users/Stark/OneDrive/个人发展战略计划/上海交通大学/科研/叶片加工/实验/6.7实验/test.txt";
	DataManipulation::ExportFile(DataManipulation::Map2D(DataManipulation::XYZImportFile(num, iFileName)), oFileName);
}
void test::testVector2Diag()
{
	double a[] = { 1, 2, 3, 4, 5 };
	Vector Av(5, a);
	Matrix Am = ArrayManipulation::Vector2Diag(Av);
	Am.show();
}