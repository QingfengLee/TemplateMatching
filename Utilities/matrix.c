/*
 * matrix.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "matrix.h"

// Initialises the given matrix with given number of rows,columns
// And allocates memory for the size of the matrix
struct matrix* createMatrix(uint32 numberOfRows, uint32 numberOfColumns) {
	struct matrix* mat;

	mat = malloc(sizeof(struct matrix));

	mat->numberOfRows = numberOfRows;
	mat->numberOfColumns = numberOfColumns;

	mat->values = malloc(numberOfRows * numberOfColumns * sizeof(float));

	return mat;
}

// Destroys the matrix and free the allocated spaces
void destroyMatrix(struct matrix* mat) {
	mat->numberOfRows = 0;
	mat->numberOfColumns = 0;

	free(mat->values);
	free(mat);
}

// Prints the matrix
void printMatrix(struct matrix* mat) {
	uint32 i;
	uint32 j;
	printf("\n --------------------------------------- \n");
	for (i = 0; i < mat->numberOfRows; ++i) {
		for (j = 0; j < mat->numberOfColumns; ++j) {
			printf("%10.3f ", MAT(mat, i, j));
		}
		printf("\n");
	}

}

// utility for subtracting 2 matrices
struct matrix* subtractMatrices(struct matrix* mat1, struct matrix* mat2) {
	assert(mat1->numberOfRows == mat2->numberOfRows);
	assert(mat1->numberOfColumns == mat2->numberOfColumns);

	struct matrix* output = createMatrix(mat1->numberOfRows,
			mat1->numberOfColumns);

	for (int i = 0; i < mat1->numberOfRows; ++i) {
		for (int j = 0; j < mat1->numberOfColumns; ++j) {
			MAT(output,i,j) = MAT(mat1,i,j) - MAT(mat2, i, j);
		}

	}

	return output;
}

void initMatrix(struct matrix* mat, void* values) {
	for (int i = 0; i < mat->numberOfRows; ++i) {
		for (int j = 0; j < mat->numberOfColumns; ++j) {
			MAT(mat,i,j) =
					((float*) values)[j + (i * mat->numberOfColumns)];
		}
	}
}

// Convert the grayscale to buffer for writing the image in the output file
uint32 convertMatrixToBuffer(struct matrix* input, uint8* outputBuffer) {
	uint32 bufferSize = 0;
	for (int i = 0; i < input->numberOfRows; ++i) {
		for (int j = 0; j < input->numberOfColumns; ++j) {
			outputBuffer[bufferSize] = (uint8) MAT(input, i, j);
			outputBuffer[bufferSize+1] = (uint8) MAT(input, i, j);
			outputBuffer[bufferSize+2] = (uint8) MAT(input, i, j);
			bufferSize+=3;
		}
	}
	return bufferSize;
}

