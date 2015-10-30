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

uint8 imageData[TEMPLATEMATCHING_IMAGE_LENGTH];

struct matrix{
	uint32 numberOfRows;
	uint32 numberOfColumns;
	float* values;
};

void applyFilter(struct matrix* image,struct matrix* filter,struct matrix* filteredImage);

float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,uint32 filterPosX,uint32 filterPosY);

void initMatrix(struct matrix* mat,uint32 numRows,uint32 numColumns);

void destroyMatrix(struct matrix* mat);

void printMatrix(struct matrix* mat);

#endif /* TEMPLATEMATCHING_H_ */
