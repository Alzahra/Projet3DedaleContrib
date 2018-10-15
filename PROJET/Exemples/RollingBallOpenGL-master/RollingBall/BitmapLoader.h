#pragma once
#define BITMAP_ID 0x4D42;
#include "includes.h"

class BitmapLoader
{
private:
	unsigned static char* bmpData;
	static BITMAPINFOHEADER bmpInfo;
public:
	BitmapLoader();
	~BitmapLoader();
	static void loadBmp(char* filename);
	static void bindTexture(unsigned int texId);
};

