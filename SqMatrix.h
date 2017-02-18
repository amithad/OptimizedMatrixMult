/*
 * SqMatrix.h
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

#ifndef SQMATRIX_H_
#define SQMATRIX_H_

class SqMatrix {
public:
	SqMatrix(int size, bool populate); //creates matrix and populate random values
	virtual ~SqMatrix();

	double** getSqMatrix();
	void printMatrix();
	int getDim();

	double** matrix;

private:
	double randomDouble();
	int n;

};



#endif /* SQMATRIX_H_ */
