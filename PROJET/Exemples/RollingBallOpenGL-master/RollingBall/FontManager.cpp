#include "FontManager.h"

unsigned int FontManager::BASE = 0;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

/*** Dave Astle: "OpenGL Game Programming" ***/
void FontManager::createBmpFont(HDC graphicsDevice, LPCWSTR fontName, int size) {

	HFONT hFont;

	BASE = glGenLists(96);

	hFont = CreateFont(
		size,
		0, 0, 0,
		FW_BOLD,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		fontName
	);

	if (!hFont) {
		OutputDebugString(L"Could not create font!");
		return;
	}

	SelectObject(graphicsDevice, hFont);
	wglUseFontBitmaps(graphicsDevice, 32, 96, BASE);
}