//============================================================================
// Name        : MatrixMultiplyParallel
// Authors     : Amitha Dissanayake
// Version     : 0.1
// Copyright   : Amitha Dissanayake
// Created on  : Oct 7th, 2016
// Description : Optimized Parallel Matrix Multiplication in C++
//============================================================================

/*
 *
 * To compile the code: g++ -fmessage-length=0 -fopenmp -O3 -march=native -mtune=native -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose=1  -ffast-math -fassociative-math *.cpp -o OptimizedParallel
 * Run the binary: ./OptimizedParallel
 *
 */

#include <iostream>
#include "SqMatrix.h"
#include <sys/time.h>
#include "Multiplier.h"
#include <stdlib.h>

using namespace std;

double* seqMatOps(int matrixSize);
void printData(bool printheader, int type, int size, int iterations); //type: 0 - seqential, 1 - parallel, 2 - parallel optimized
void crossAnalyze();
double matOps(int type, int matrixSize);

int main() {

	crossAnalyze(); //comparative representation - shown speed up is lower than the actual
	return 0;
}

double* seqMatOps(int matrixSize) {

	//create matrices
	SqMatrix* mat1 = new SqMatrix(matrixSize, true);
	SqMatrix* mat2 = new SqMatrix(matrixSize, true);
	SqMatrix* mat3 = new SqMatrix(matrixSize, false); //if set false not populated with a random value

	//time
	struct timespec start, end;
	double* microsecs = new double[3];

	//sequential
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	Multiplier::multiplyMatrixSeq(mat1, mat2, mat3);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	microsecs[0] = (double) ((end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows

	//parallel
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	Multiplier::multiplyMatrixParallel(mat1, mat2, mat3);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	microsecs[1] = (double) ((end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows

	//optimized
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	Multiplier::multiplyMatrixParallelOptimized(mat1, mat2, mat3);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	microsecs[2] = (double) ((end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows

	//handle memory leaks
	delete mat1;
	delete mat2;
	delete mat3;

	return microsecs;
}

double matOps(int type, int matrixSize) { //duplicate of seqMatOps

	//create matrices
	SqMatrix* mat1 = new SqMatrix(matrixSize, true);
	SqMatrix* mat2 = new SqMatrix(matrixSize, true);
	SqMatrix* mat3 = new SqMatrix(matrixSize, false); //if set false not populated with a random value

	struct timespec start, end;

	double microsecs = 0.0;

	switch (type) {

	case 0:
		//sequential
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		Multiplier::multiplyMatrixSeq(mat1, mat2, mat3);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		microsecs = (double) ((end.tv_sec - start.tv_sec) * 1000000
				+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows
		break;

	case 1:
		//parallel
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		Multiplier::multiplyMatrixParallel(mat1, mat2, mat3);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		microsecs = (double) ((end.tv_sec - start.tv_sec) * 1000000
				+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows
		break;

	case 2:
		//optimized
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		Multiplier::multiplyMatrixParallelOptimized(mat1, mat2, mat3);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		microsecs = (double) ((end.tv_sec - start.tv_sec) * 1000000
				+ (end.tv_nsec - start.tv_nsec) / 1000); //both sec and nsec are considered to address memory overflows
		break;
	}

	//handle memory leaks
	delete mat1;
	delete mat2;
	delete mat3;

	return microsecs;

}

void printData(bool printHeader, int type, int size, int iterations) {

	if (printHeader) {
		cout << "n," << "time(millisecs)" << endl;

	}
	for (int i = 0; i < iterations; i++) {
		double time = matOps(type, size);
		cout << size << "," << time / 1000 << endl;
	}

}

void crossAnalyze() {

	cout
			<< "|   n\t|seq-time(milliseconds)\t|par-time(milliseconds)\t|opt-par-time(milliseconds)\t| speedup - old\t| speedup - new\t| speedup gain |"
			<< endl << endl;

	for (int i = 100; i < 1001; i = i + 100) {
		double* time = seqMatOps(i);
		cout << i;
		cout << "\t\t" << time[0] / 1000;
		cout << "\t\t\t" << time[1] / 1000;
		cout << "\t\t\t" << time[2] / 1000;
		cout << "\t\t\t" << time[0] / time[1];
		cout << "\t\t" << time[0] / time[2];
		cout << "\t\t" << time[0] / time[2] - time[0] / time[1] << endl;
		delete time; //memory leak handler
	}
	cout << endl
			<< "==================================================================="
			<< endl;
	cout << "\tAbove time values are obtained after compiler parameters"
			<< endl;
	cout << "\tare optimized. Therefore actual speed up is" << endl;
	cout << "\tdrastically higher the value actually shown here." << endl;
	cout << "\tApprox. multiplication factor to obtain true speed-up: 1.7" << endl;
	cout
			<< "==================================================================="
			<< endl;
}
