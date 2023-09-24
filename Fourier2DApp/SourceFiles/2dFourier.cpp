#include "2dFourier.h"

void Fourier::initialize()
{
	D = (dataset*)malloc(sizeof(dataset));
	S = (dataset**)calloc(sizeof(dataset*), 3);
	for (int i = 0; i < NumOfSeries; i++) {
		S[i] = (dataset*)malloc(sizeof(dataset));
		S[i]->N = DefaultDepth;
	}
}

void Fourier::CreateDataSet(const char* filename)
{
	string FileLocation = InputDataFilesFolder + (string)filename + ".dat";
	FILE* file = fopen(FileLocation.c_str(), "r");
	int i = 0;
	float s;
	while (fscanf(file, "%f %f\n",&s,&s) != EOF)i++;

	D->N = i;
	D->X = (double*)malloc(i * sizeof(double));
	D->Y = (double*)malloc(i * sizeof(double));

	fseek(file, 0, 0);
	for (int j = 0; j < i; j++)fscanf(file, "%lf %lf\n", &(D->X[j]), &(D->Y[j]));

	return;
}

void Fourier::PrintDataSet()
{
	for (int i = 0; i < D->N; i++)
		printf("\n( %.3F , %.3F )", D->X[i], D->Y[i]);
	return;
}

void Fourier::SetDepth(int d)
{
	for (int i = 0; i < NumOfSeries; i++) {
		S[i]->N = d;
	}
	return;
}

void Fourier::GenerateDataFile(const char* filename, int n)
{
	string FileLocation = OutputDataFilesFolder + (string)filename + ".dat";
	FILE* file = fopen(FileLocation.c_str(), "w");
	double X, Y;
	for (int i = 0; i < n; i++) {
		X = EvalX(2 * i * Pi / n);
		Y = EvalY(2 * i * Pi / n);
		fprintf(file, "%.6F %.6F\n", X, Y);
	}
	fclose(file);
	return;
}

double Fourier::EvalX(double t)
{
	double x = S[0]->X[0];
	for (int i = 1; i < S[0]->N; i++) {
		x += S[0]->X[i] * sin(i * t) + S[0]->X[i + S[0]->N] * cos(i * t);
	}
	return x;
}

double Fourier::EvalY(double t)
{
	double y = S[0]->Y[0];
	for (int i = 1; i < S[0]->N; i++) {
		y += S[0]->Y[i] * sin(i * t) + S[0]->Y[i + S[0]->N] * cos(i * t);
	}
	return y;
}

void Fourier::GenerateS0()
{	
	S[0]->X = (double*)calloc(S[0]->N * sizeof(double), 2);
	S[0]->Y = (double*)calloc(S[0]->N * sizeof(double), 2);
	for (int n = 0; n < S[0]->N; n++) {
		for (int i = 0; i < D->N; i++) {
			if (n == 0) {
				S[0]->X[n] += 1. / D->N * D->X[i];
				S[0]->Y[n] += 1. / D->N * D->Y[i];
			}
			else {
				S[0]->X[n] += 2. / D->N * D->X[i] * sin(2 * Pi * i * n / D->N);
				S[0]->X[n + S[0]->N] += 2. / D->N * D->X[i] * cos(2 * Pi * i * n / D->N);
				S[0]->Y[n] += 2. / D->N * D->Y[i] * sin(2 * Pi * i * n / D->N);
				S[0]->Y[n + S[0]->N] += 2. / D->N * D->Y[i] * cos(2 * Pi * i * n / D->N);
			}
		}
	}
}

void Fourier::GenerateS1()
{
	dataset* PolarData = (dataset*)calloc(sizeof(dataset), 1);
	PolarData->X = (double*)calloc(sizeof(double*), D->N);
	PolarData->Y = (double*)calloc(sizeof(double*), D->N);
	for (int i = 0; i < D->N; i++) {
		PolarData->X[i] = atan(D->Y[i] / D->X[i]);
		if (D->Y[i] < 0)PolarData->X[i] += Pi;
		PolarData->Y[i] = sqrt(D->X[i] * D->X[i] + D->Y[i] * D->Y[i]);
	}

	S[1]->X = (double*)calloc(S[1]->N * sizeof(double), 1);
	S[1]->Y = (double*)calloc(S[1]->N * sizeof(double), 1);

	for (int n = 0; n < S[0]->N; n++) {
		for (int i = 0; i < D->N; i++) {
			if (n == 0) {
				S[1]->X[n] += 1. / D->N * D->X[i];
				S[0]->Y[n] += 1. / D->N * D->Y[i];
			}
			else {
				S[0]->X[n] += 2. / D->N * D->X[i] * sin(2 * Pi * i * n / D->N);
				S[0]->X[n + S[0]->N] += 2. / D->N * D->X[i] * cos(2 * Pi * i * n / D->N);
				S[0]->Y[n] += 2. / D->N * D->Y[i] * sin(2 * Pi * i * n / D->N);
				S[0]->Y[n + S[0]->N] += 2. / D->N * D->Y[i] * cos(2 * Pi * i * n / D->N);
			}
		}
	}
}

void Fourier::GenerateS2()
{
}

void Fourier::CreateGnuplotFile(const char* filename) {
	char FileName[] = GnuplotFileLocation;
	string FileLocation = GnuplotFileLocation + (string)filename + ".plt";

	FILE* file = fopen(FileLocation.c_str(), "w");

	fprintf(file, "set xrange [%.15f:%.15f]\n", -5., 5.);
	fprintf(file, "set yrange [%.15f:%.15f]\n", -5., 5.);
	fprintf(file, "set mouse format \"%s\"\n", "%.3F");

	fprintf(file, "plot \\\n");
	fprintf(file, "\"C:/Users/MIquel Nasarre/Desktop/Fourier painting/project1/DataFiles/Output/%s.dat\" pt 0 lc rgb \"#000000\" notitle, \\\n", filename);
	fprintf(file, "\"C:/Users/MIquel Nasarre/Desktop/Fourier painting/project1/DataFiles/Input/%s.dat\" pt 2 lc rgb \"#FF0000\" notitle", filename);

	fclose(file);
}

void Fourier::CreateDataSet(Objects Obj)
{
	D->N = Obj.NumOfCircles;
	D->X = (double*)calloc(sizeof(double), D->N);
	D->Y = (double*)calloc(sizeof(double), D->N);

	for (int i = 0; i < Obj.NumOfCircles; i++) {
		Vector2f Pos = Obj.GetCirclePos(i);
		D->X[i] = (double)Pos.x;
		D->Y[i] = (double)Pos.y;
	}
}

dataset Fourier::FourierS0DataSet(int N)
{
	dataset Graph;
	Graph.N = N;
	Graph.X = (double*)calloc(sizeof(double), N);
	Graph.Y = (double*)calloc(sizeof(double), N);
	for (int i = 0; i < N; i++) {
		Graph.X[i] = EvalX(2 * i * Pi / (N - 1));
		Graph.Y[i] = EvalY(2 * i * Pi / (N - 1));
	}
	return Graph;
}

void Fourier::FullProcessS0(const char* filename)
{
	CreateDataSet(filename);
	GenerateS0();
	GenerateDataFile(filename, 1000);
	CreateGnuplotFile(filename);
}

Fourier* Pointer()
{
	Fourier* F = (Fourier*)malloc(sizeof(Fourier));
	F->initialize();
	return F;
}
