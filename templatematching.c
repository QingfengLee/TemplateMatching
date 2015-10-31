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

#define MAT(a, i, j) ((a)->values[j + (i * (a)->numberOfColumns)])

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

	applyFilter(&image,&filter,&filteredImage,CORRELATION_OPERATION,MODE_SYMMETRIC);

	return 0;
}

void applyFilter(struct matrix* image,struct matrix* filter,struct matrix* filteredImage,uint8 operation,uint8 mode){

	float tempResult ;
	float tempPixelValue = 0.0;
#ifdef DEBUG
	struct matrix tempMatrix;
	initMatrix(&tempMatrix,filter->numberOfRows,filter->numberOfColumns);
#endif
	for (uint16 i = 0; i < image->numberOfRows; ++i) {
		for (uint16 j = 0; j < image->numberOfColumns; ++j) {
				tempResult = 0.0;
				for (int l = 0; l < filter->numberOfRows; ++l) {
					for (int m = 0; m < filter->numberOfColumns; ++m) {
						tempPixelValue = getPixelValue(image,i,j,l-(filter->numberOfRows/2),m-(filter->numberOfColumns/2),mode);
#ifdef DEBUG
						MAT(&tempMatrix,l,m) = tempPixelValue;
#endif
						if(operation == CONVOLUTION_OPERATION)
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,(filter->numberOfRows-1-l),(filter->numberOfColumns-1-m)));
						}
						else
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,l,m));
						}
					}
				}
#ifdef DEBUG
				printMatrix(&tempMatrix);
#endif
				MAT(filteredImage,i,j) = tempResult;

		}
	}

	printMatrix(filteredImage);
}

float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,
		uint32 filterPosX,uint32 filterPosY,uint8 mode)
{
	float pixelValue = 0.0;

	sint32 imgCurrentPosX = imgPosX+filterPosX;
	sint32 imgCurrentPosY = imgPosY+filterPosY;
	if((imgCurrentPosX < 0) ||
		(imgCurrentPosX > (image->numberOfRows-1)) ||
		(imgCurrentPosY < 0) ||
		(imgCurrentPosY > (image->numberOfColumns-1)))
	{
			if(mode == MODE_REPLICATE)
			{
				imgCurrentPosX = ((imgCurrentPosX < 0) ? 0 : (imgCurrentPosX > image-> numberOfRows-1) ? (image-> numberOfRows-1) : imgCurrentPosX);
				imgCurrentPosY = ((imgCurrentPosY < 0) ? 0 : (imgCurrentPosY > image-> numberOfColumns-1) ? (image-> numberOfColumns-1) : imgCurrentPosY);

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
			else if(mode == MODE_SYMMETRIC)
			{
				if(imgCurrentPosX < 0 || imgCurrentPosX > image->numberOfRows-1)
				{
					imgCurrentPosX = (image->numberOfRows -1) - (mod(imgCurrentPosX,image->numberOfRows));
				}
				if(imgCurrentPosY < 0 || imgCurrentPosY > image->numberOfColumns-1)
				{
					imgCurrentPosY = (image->numberOfColumns -1) - (mod(imgCurrentPosY,image->numberOfColumns));
				}

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
	}
	else
	{
		pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
	}

	return pixelValue;

}

void initMatrix(struct matrix* mat,uint32 numRows,uint32 numColumns)
{
	mat->numberOfRows = numRows;
	mat->numberOfColumns = numColumns;

	mat->values = malloc(numRows*numColumns*sizeof(float));
}

void destroyMatrix(struct matrix* mat)
{
	mat->numberOfRows = 0;
	mat->numberOfColumns = 0;

	free(mat->values);
}

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

uint32 mod (sint32 a, sint32 b)
{
	sint32 ret = 0;
   if(a >= 0)
   {
	   ret =  a % b;
   }
   else
   {
	   ret = a;
	   while(ret < 0)
	        ret+=b;
   }

   return (uint32)ret;
}


