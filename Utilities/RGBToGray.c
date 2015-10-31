/*
 * RGBToGray.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "RGBToGray.h"

// function to convert RGB to gray values
struct matrix* convertRGBToGrayScale(uint8* rgb,uint32 rgbSize,uint32 width,uint32 height)
{
	struct matrix* grayScale = createMatrix(height,width);

	float grayValue;
	float red,green,blue;

	uint32 j,k;

	for (int i = 0; i < rgbSize; i+=3) {
		red = (float)rgb[i];
		green = (float)rgb[i+1];
		blue = (float)rgb[i+2];

		grayValue = 0.2989*red + 0.5870*green + 0.1140*blue;

		j = (i/3)/width;
		k = (i/3)%width;

		MAT(grayScale,j,k) = grayValue;
	}

	return grayScale;
}
