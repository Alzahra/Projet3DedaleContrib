#include "BitmapLoader.h"

unsigned char* BitmapLoader::bmpData = NULL;
BITMAPINFOHEADER BitmapLoader::bmpInfo = {};

BitmapLoader::BitmapLoader()
{
}

BitmapLoader::~BitmapLoader()
{
}

/*** Dave Astle: "OpenGL Game Programming" ***/
void BitmapLoader::loadBmp(char* filename) {

	FILE *filePtr;							// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	int					imageIdx = 0;		// image index counter
	unsigned char		tempRGB;				// swap variable

												// open filename in "read binary" mode
	fopen_s(&filePtr, filename, "rb");
	if (filePtr == NULL)
		return;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != 0x4D42)
	{
		fclose(filePtr);
		return;
	}

	// read the bitmap information header
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bmpData = (unsigned char*)malloc(bmpInfo.biSizeImage);

	// verify memory allocation
	if (!bmpData)
	{
		free(bmpData);
		fclose(filePtr);
		return;
	}

	// read in the bitmap image data
	fread(bmpData, 1, bmpInfo.biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bmpData == NULL)
	{
		fclose(filePtr);
		return;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bmpInfo.biSizeImage; imageIdx += 3)
	{
		tempRGB = bmpData[imageIdx];
		bmpData[imageIdx] = bmpData[imageIdx + 2];
		bmpData[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
}

/*** Dave Astle: "OpenGL Game Programming" ***/
void BitmapLoader::bindTexture(unsigned int texId) {

	if (!bmpData) {
		OutputDebugString(L"Empty BMP Data!");
		return;
	}

	glGenTextures(1, &texId);

	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpInfo.biWidth, bmpInfo.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bmpData);
}