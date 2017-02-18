/*
 * Multiplier.cpp
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

#include "Multiplier.h"
#include <omp.h>
#include <stdlib.h>
#include <stdint-gcc.h>

using namespace std;

Multiplier::Multiplier() {

}

void Multiplier::multiplyMatrixSeq(SqMatrix* mat1, SqMatrix* mat2,
		SqMatrix* matOut) {

	int n = mat1->getDim();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matOut->matrix[i][j] = 0; //set initial value to zero
			for (int k = 0; k < n; k++) {
				matOut->matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j]; // matrix multiplication formula
			}
		}
	}
}

void Multiplier::multiplyMatrixParallel(SqMatrix* mat1, SqMatrix* mat2,
		SqMatrix* matOut) {

	int n = mat1->getDim();
#pragma omp parallel for //parallel
	for (int i = 0; i < n; i++) {
#pragma omp parallel for //parallel
		for (int j = 0; j < n; j++) {
			matOut->matrix[i][j] = 0; //set initial value to zero
			for (int k = 0; k < n; k++) {
				matOut->matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
			}
		}
	}
}

void Multiplier::multiplyMatrixParallelOptimized(SqMatrix* mat1, SqMatrix* mat2,
		SqMatrix* matOut) {

	//NOTE: All the loop counters are 16 bit fast int. Fasten by memory advantage

	int n = mat1->getDim();
	SqMatrix temp = SqMatrix(n, false);
	matrixTranspose(mat2, &temp, n); //take the transpose to avoid cache misses

#pragma omp parallel for //parallel
	for (int_fast16_t i = 0; i < n; i++) {
		//NOTE: previously implemented parallelism here is removed to obtain thread creation overhead advantage
		for (int_fast16_t j = 0; j < n; j++) {
			matOut->matrix[i][j] = dotProduct(mat1->matrix[i], temp.matrix[j],
					n); // multiplication loop is unrolled. Compiler optimizes and add AVX fused multiply and add here.
		}
	}
}

void Multiplier::matrixTranspose(SqMatrix* source, SqMatrix* destination,
		int size) { //get the transpose matrix

#pragma omp parallel for
	for (int_fast16_t i = 0; i < size; i++) {
		for (int_fast16_t j = 0; j < size; j++) {
			destination->matrix[j][i] = source->matrix[i][j];
		}
	}
}

double Multiplier::dotProduct(double* vect1, double* vect2, int matsize) { // dot product
	double temp = 0.0;
	for (int_fast16_t i = 0; i < matsize; i++) {
		temp += vect1[i] * vect2[i];
	}
	return temp;
}

Multiplier::~Multiplier() {

}

