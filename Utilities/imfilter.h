/*
 * imfilter.h
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#ifndef UTILITIES_IMFILTER_H_
#define UTILITIES_IMFILTER_H_

#include "misc.h"
#include "matrix.h"

#define CONVOLUTION_OPERATION (0)
#define CORRELATION_OPERATION (1)

#define MODE_PAD_ZERO (0)
#define MODE_SYMMETRIC (1)
#define MODE_REPLICATE (2)
#define MODE_CIRCULAR (3)

struct matrix* imfilter(struct matrix* image,struct matrix* filter,uint8 operation,uint8 mode);

float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,uint32 filterPosX,uint32 filterPosY,uint8 mode);

struct matrix* imsharpen(struct matrix* image);

#endif /* UTILITIES_IMFILTER_H_ */
