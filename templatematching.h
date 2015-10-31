/*
 * templatematching.h
 *
 *  Created on: 29-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#ifndef TEMPLATEMATCHING_H_
#define TEMPLATEMATCHING_H_

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned int uint16;

typedef signed char sint8;
typedef signed int sint32;
typedef signed int sint16;

#define TEMPLATEMATCHING_IMAGE_LENGTH (4000000)
#define CONVOLUTION_OPERATION (0)
#define CORRELATION_OPERATION (1)

#define MODE_PAD_ZERO (0)
#define MODE_SYMMETRIC (1)
#define MODE_REPLICATE (2)
#define MODE_CIRCULAR (3)

uint8 imageData[TEMPLATEMATCHING_IMAGE_LENGTH];

struct matrix{
	uint32 numberOfRows;
	uint32 numberOfColumns;
	float* values;
};

void applyFilter(struct matrix* image,struct matrix* filter,struct matrix* filteredImage,uint8 operation,uint8 mode);

float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,uint32 filterPosX,uint32 filterPosY,uint8 mode);

void initMatrix(struct matrix* mat,uint32 numRows,uint32 numColumns);

void destroyMatrix(struct matrix* mat);

void printMatrix(struct matrix* mat);

uint32 mod (sint32 a, sint32 b);


#endif /* TEMPLATEMATCHING_H_ */
