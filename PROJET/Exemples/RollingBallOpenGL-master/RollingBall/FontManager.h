#pragma once
#include "includes.h"

class FontManager
{
public:
	unsigned static int BASE;
	FontManager();
	~FontManager();
	static void createBmpFont(HDC graphicsDevice, LPCWSTR fontName, int size);
};

