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


void initMatrix(struct matrix* mat,uint32 numRows,uint32 numColumns);

void destroyMatrix(struct matrix* mat);

void printMatrix(struct matrix* mat);



#endif /* UTILITIES_MATRIX_H_ */
