/*
 * matrix.h
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#ifndef UTILITIES_MATRIX_H_
#define UTILITIES_MATRIX_H_

#include "misc.h"

#define MAT(a, i, j) ((a)->values[j + (i * (a)->numberOfColumns)])

struct matrix{
	uint32 numberOfRows;
	uint32 numberOfColumns;
	float* values;
};

struct matrix* createMatrix(uint32 numberOfRows,uint32 numberOfColumns);

void destroyMatrix(struct matrix* mat);

void printMatrix(struct matrix* mat);

struct matrix* subtractMatrices(struct matrix* mat1,struct matrix* mat2);

void initMatrix(struct matrix* mat, void* values);

uint32 convertMatrixToBuffer(struct matrix* input, uint8* outputBuffer);

#endif /* UTILITIES_MATRIX_H_ */
