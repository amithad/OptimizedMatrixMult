/*
 * SqMatrix.cpp
 *
  *============================================================================
 * Name        : MatrixMultiplyParallel
 * Authors     : Amitha Dissanayake
 * Version     : 0.1
 * Copyright   : Amitha Dissanayake
 * Created on  : Oct 7th, 2016
 * Description : Optimized Parallel Matrix Multiplication in C++
 *============================================================================
 *
 */

#include "SqMatrix.h"
#include <stdlib.h>
#include <iostream>

#define MAX_VAL 999999 //delimiter for the random value generator

using namespace std;

SqMatrix::SqMatrix(int size, bool populate) { //populate random or zero at creation
	n = size;
	matrix = new double*[n]; //row count
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n]; //column count
		if (populate) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = randomDouble(); //assign random
			}
		}
	}

}

void SqMatrix::printMatrix() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

double SqMatrix::randomDouble() { //generate random double value
	double generator = (double) rand() / RAND_MAX;
	return -MAX_VAL + generator * 2 * MAX_VAL;
}

int SqMatrix::getDim(){ //return matrix dimension
	return n;
}

SqMatrix::~SqMatrix() {
	for (int i = 0; i < n; i++) { //delete and free memory
		delete[] matrix[i];
	}
	delete[] matrix;
}

