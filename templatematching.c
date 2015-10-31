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

	struct matrix image;
	struct matrix filter;
	struct matrix filteredImage;

	initMatrix(&image,7,7);
	initMatrix(&filter,5,5);
	initMatrix(&filteredImage,7,7);

	float value = 1.0;

	for (uint8 i = 0; i < image.numberOfRows; ++i) {
		for (uint8 j = 0; j < image.numberOfColumns; ++j) {
			MAT(&image, i, j) = value;
			value++;
		}
	}

#ifdef DEBUG
	printMatrix(&image);
#endif

	MAT(&filter,0,0) = 1.0;
	MAT(&filter,0,1) = -1.0;
	MAT(&filter,0,2) = 3.0;
	MAT(&filter,0,3) = 3.0;
	MAT(&filter,0,4) = 3.0;
	MAT(&filter,1,0) = -1.0;
	MAT(&filter,1,1) = 5.0;
	MAT(&filter,1,2) = -1.0;
	MAT(&filter,1,3) = -1.0;
	MAT(&filter,1,4) = -1.0;
	MAT(&filter,2,0) = 0.0;
	MAT(&filter,2,1) = -1.0;
	MAT(&filter,2,2) = 0.0;
	MAT(&filter,2,3) = 0.0;
	MAT(&filter,2,4) = 0.0;
	MAT(&filter,3,0) = 0.0;
	MAT(&filter,3,1) = -1.0;
	MAT(&filter,3,2) = 0.0;
	MAT(&filter,3,3) = 0.0;
	MAT(&filter,3,4) = 0.0;
	MAT(&filter,4,0) = 0.0;
	MAT(&filter,4,1) = -1.0;
	MAT(&filter,4,2) = 0.0;
	MAT(&filter,4,3) = 0.0;
	MAT(&filter,4,4) = 0.0;

	imfilter(&image,&filter,&filteredImage,CORRELATION_OPERATION,MODE_CIRCULAR);

	return 0;
}







