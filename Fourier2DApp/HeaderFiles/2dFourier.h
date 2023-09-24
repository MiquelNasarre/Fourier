#pragma once

#include "Header.h"
#include "Objects.h"

#pragma region Definitions

using namespace std;

#define DefaultDepth 10
#define Pi 3.14159265358979
#define NumOfSeries 3
#define InputDataFilesFolder "DataFiles/Input/"
#define OutputDataFilesFolder "DataFiles/Output/"
#define GnuplotFileLocation "DataFiles/Output/Gnuplot/"

#pragma endregion

struct dataset {
	int N;
	double* X;
	double* Y;

	dataset(int n, double* x, double* y) {
		N = n;
		X = x;
		Y = y;
	}
	dataset() {}
};

class Fourier {
  public:
	dataset* D;
	dataset** S;

	void initialize();
	void PrintDataSet();
	void SetDepth(int d);

	void GenerateS0();
	void GenerateS1();
	void GenerateS2();

	//GNUpolt
	void CreateDataSet(const char* filename);
	void GenerateDataFile(const char* filename, int n);
	void CreateGnuplotFile(const char* filename);

	//SFML
	void CreateDataSet(Objects Obj);
	dataset FourierS0DataSet(int N);


	double EvalX(double t);
	double EvalY(double t);

	void FullProcessS0(const char* filename);
};

Fourier* Pointer();