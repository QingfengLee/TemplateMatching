/*
 * templatematching.c
 *
 *  Created on: 29-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "templatematching.h"

uint8 imageData[TEMPLATEMATCHING_IMAGE_LENGTH];

int main(int argc, char* argv[])
{
	/*char inputFileName[100];
	FILE* input_file = NULL;

	uint32 file_Length;

	if(argc >= 1) {
		strcpy(inputFileName, argv[1]);
	}

	input_file = fopen(inputFileName, "rb");

	if (input_file != NULL) {
		fseek(input_file, 0, SEEK_END);
		file_Length = ftell(input_file);
		fseek(input_file, 0, SEEK_SET);

		uint32 numBytesRead = fread(imageData, 1, file_Length, input_file);

		printf("%d",file_Length);

		fclose(input_file);

	}*/

	// For testing conversion of RGB to grayscale
	uint8 imageBuf[12] = {255,255,255,
						  255,255,0,
						  255,0,255,
						  0,255,255};

	struct matrix* gray = convertRGBToGrayScale(imageBuf,12,2,2);

	printMatrix(gray);

	// Declare matrices for image,filter and the output
	struct matrix* image;
	struct matrix* filter;
	struct matrix* filteredImage;

	//Intialise matrices
	image = createMatrix(7,7);
	filter = createMatrix(5,5);

	float value = 1.0;

	// For testing purpose - Initialised a 7x7 matrix as image
	for (uint8 i = 0; i < image->numberOfRows; ++i) {
		for (uint8 j = 0; j < image->numberOfColumns; ++j) {
			MAT(image, i, j) = value;
			value++;
		}
	}

#ifdef DEBUG
	printMatrix(image);
#endif

	// For testing purpose - Initialised a 5x5 matrix as filter mask
	float filterValues[5][5] = {{1.0, -1.0, 3.0, 3.0, 3.0},
								{-1.0, 5.0, -1.0 , -1.0, -1.0},
								{0.0,  -1.0 , 0.0 ,0.0 ,0.0 },
								{0.0, -1.0, 0.0, 0.0, 0.0},
								{0.0, -1.0,  0.0 , 0.0, 0.0}};

	initMatrix(filter, (void*)filterValues);

	// Apply filter
	// operation - Convolution/Correlation
	// Mode - by which mode the values outside the array bound is computed
	// Mode - Zero padding/Symmetric/Circular/Replicate
	filteredImage = imfilter(image,filter,CORRELATION_OPERATION,MODE_CIRCULAR);

	destroyMatrix(filteredImage);

	filteredImage = imsharpen(image);

	printMatrix(filteredImage);

	destroyMatrix(image);
	destroyMatrix(filter);
	destroyMatrix(filteredImage);

	return 0;
}







