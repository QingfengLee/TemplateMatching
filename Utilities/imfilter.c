/*
 * imfilter.c
 *
 *  Created on: 31-Oct-2015
 *      Author: Indumathi Duraipandian
 */

#include "imfilter.h"

float laplacianFilter[3][3] = {{0.1667,0.6667,0.1667},
							   {0.6667,-3.3333,0.6667},
							   {0.1667,0.6667,0.1667}};

struct matrix* imfilter(struct matrix* image,struct matrix* filter,uint8 operation,uint8 mode){

	float tempResult ;
	float tempPixelValue = 0.0;
	struct matrix* filteredImage = createMatrix(image->numberOfRows,image->numberOfColumns);

#ifdef DEBUG
	//For debugging initialised a temporary matrix with boundary padded
	// according to the mode given
	struct matrix* tempMatrix = createMatrix(filter->numberOfRows,filter->numberOfColumns);
#endif
	//Iterate the rows of the image
	for (uint16 i = 0; i < image->numberOfRows; ++i) {
		//Iterate the columns of the image
		for (uint16 j = 0; j < image->numberOfColumns; ++j) {
				tempResult = 0.0;
				//Iterate the rows of the filter
				for (int l = 0; l < filter->numberOfRows; ++l) {
					//Iterate the columns of the filter
					for (int m = 0; m < filter->numberOfColumns; ++m) {
						// get the pixel value for the given filter mask position(l,m)
						tempPixelValue = getPixelValue(image,i,j,l-(filter->numberOfRows/2),m-(filter->numberOfColumns/2),mode);
#ifdef DEBUG
						MAT(tempMatrix,l,m) = tempPixelValue;
#endif
						// for convolution operation the filter should be inverted
						if(operation == CONVOLUTION_OPERATION)
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,(filter->numberOfRows-1-l),(filter->numberOfColumns-1-m)));
						}
						// for correlation the filter should be used as it is
						else
						{
							tempResult = tempResult + (tempPixelValue * MAT(filter,l,m));
						}
					}
				}
#ifdef DEBUG
				printMatrix(tempMatrix);
#endif
				MAT(filteredImage,i,j) = tempResult;

		}
	}

#ifdef DEBUG
	printMatrix(filteredImage);
#endif

	return filteredImage;
}



float getPixelValue(struct matrix* image,uint32 imgPosX,uint32 imgPosY,
		uint32 filterPosX,uint32 filterPosY,uint8 mode)
{
	float pixelValue = 0.0;
	// add the image and filter position
	sint32 imgCurrentPosX = imgPosX+filterPosX;
	sint32 imgCurrentPosY = imgPosY+filterPosY;

	// check whether the resulting added position lies outside the image boundary
	if((imgCurrentPosX < 0) ||
		(imgCurrentPosX > (image->numberOfRows-1)) ||
		(imgCurrentPosY < 0) ||
		(imgCurrentPosY > (image->numberOfColumns-1)))
	{
			// values outside the bounds of the image are the nearest array borders
			if(mode == MODE_REPLICATE)
			{
				imgCurrentPosX = ((imgCurrentPosX < 0) ? 0 : (imgCurrentPosX > image-> numberOfRows-1) ? (image-> numberOfRows-1) : imgCurrentPosX);
				imgCurrentPosY = ((imgCurrentPosY < 0) ? 0 : (imgCurrentPosY > image-> numberOfColumns-1) ? (image-> numberOfColumns-1) : imgCurrentPosY);

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
			// values outside the bounds of the image are mirror reflecting the array across the border
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
			// values outside the bounds of the image are periodic
			else if(mode == MODE_CIRCULAR)
			{
				if(imgCurrentPosX < 0 || imgCurrentPosX > image->numberOfRows-1)
				{
					imgCurrentPosX = mod(imgCurrentPosX,image->numberOfRows);
				}
				if(imgCurrentPosY < 0 || imgCurrentPosY > image->numberOfColumns-1)
				{
					imgCurrentPosY = mod(imgCurrentPosY,image->numberOfColumns);
				}

				pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
			}
	}
	//  If the postion is inside the image bound,use the current position's value
	else
	{
		pixelValue = MAT(image,imgCurrentPosX,imgCurrentPosY);
	}

	return pixelValue;

}

// sharpening image - apply laplacian filter and
//subtract the resultant image from the original image
struct matrix* imsharpen(struct matrix* image)
{
	struct matrix* filter;
	filter = createMatrix(3,3);

	initMatrix(filter, (void*)laplacianFilter);

	struct matrix* filteredImage = imfilter(image,filter,CORRELATION_OPERATION,MODE_PAD_ZERO);

	struct matrix* sharpenedImage = subtractMatrices(image,filteredImage);

	destroyMatrix(filter);
	destroyMatrix(filteredImage);

	return sharpenedImage;
}


