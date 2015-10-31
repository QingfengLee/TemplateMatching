/*
 * matrix.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "matrix.h"

// Initialises the given matrix with given number of rows,columns
// And allocates memory for the size of the matrix
void initMatrix(struct matrix* mat,uint32 numRows,uint32 numColumns)
{
	mat->numberOfRows = numRows;
	mat->numberOfColumns = numColumns;

	mat->values = malloc(numRows*numColumns*sizeof(float));
}

// Destroys the matrix and free the allocated spaces
void destroyMatrix(struct matrix* mat)
{
	mat->numberOfRows = 0;
	mat->numberOfColumns = 0;

	free(mat->values);
}

// Prints the matrix
void printMatrix(struct matrix* mat)
{
	uint32 i;
	uint32 j;
	printf("\n --------------------------------------- \n");
	for (i = 0; i < mat->numberOfRows; ++i) {
			for (j = 0; j < mat->numberOfColumns; ++j) {
				printf("%10.3f " ,MAT(mat,i,j));
			}
			printf("\n");
	}

}


