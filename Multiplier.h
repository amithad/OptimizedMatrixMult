/*
 * Multiplier.h
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

#ifndef MULTIPLIER_H_
#define MULTIPLIER_H_

#include "SqMatrix.h"

class Multiplier {
public:
	Multiplier();
	virtual ~Multiplier();
	static void multiplyMatrixSeq(SqMatrix* mat1, SqMatrix* mat2, SqMatrix* matOut);
	static void multiplyMatrixParallel(SqMatrix* mat1, SqMatrix* mat2, SqMatrix* matOut);
	static void multiplyMatrixParallelOptimized(SqMatrix* mat1, SqMatrix* mat2, SqMatrix* matOut);
	static void matrixTranspose(SqMatrix* source, SqMatrix* destination, int size);

	//compiler invokes AVX fused multiply and add implicitly after reading inline keyword.
	static double inline dotProduct(double* vect1, double* vect2, int matsize);
};

#endif /* MULTIPLIER_H_ */
