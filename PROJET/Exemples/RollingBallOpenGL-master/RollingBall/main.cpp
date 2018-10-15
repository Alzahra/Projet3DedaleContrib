#include "includes.h"
#include "GameWorld.h"
#include "Timer.h"

HDC deviceContext;
bool keyPressed[256];

const static int WIDTH = 800, HEIGHT = 600;

GameWorld* gameWorld;

time_t oldWndProcTime;

/**** Source: Dave Astle: "OpenGL Game Programming" ****/
void SetupPixelFormat(HDC hDC)
{
	int nPixelFormat;					// our pixel format index

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of structure
		1,								// default version
		PFD_DRAW_TO_WINDOW |			// window drawing support
		PFD_SUPPORT_OPENGL |			// OpenGL support
		PFD_DOUBLEBUFFER,				// double buffering support
		PFD_TYPE_RGBA,					// RGBA color mode
		32,								// 32 bit color mode
		0, 0, 0, 0, 0, 0,				// ignore color bits, non-palettized mode
		0,								// no alpha buffer
		0,								// ignore shift bit
		0,								// no accumulation buffer
		0, 0, 0, 0,						// ignore accumulation bits
		16,								// 16 bit z-buffer size
		0,								// no stencil buffer
		0,								// no auxiliary buffer
		PFD_MAIN_PLANE,					// main drawing plane
		0,								// reserved
		0, 0, 0 };						// layer masks ignored

	nPixelFormat = ChoosePixelFormat(hDC, &pfd);	// choose best matching pixel format

	SetPixelFormat(hDC, nPixelFormat, &pfd);		// set pixel format to device context
}

/**** Source: Dave Astle: "OpenGL Game Programming" ****/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	time_t newKeyTime;
	double diff;
	wchar_t str[30];

	static HGLRC hRC; // rendering context
	static HDC hDC; // device context

	int width, height;

	switch (message) {

	case WM_CREATE:
		hDC = GetDC(hwnd);
		deviceContext = hDC;
		SetupPixelFormat(hDC);

		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		return 0;
		break;

	case WM_CLOSE:
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		PostQuitMessage(0);

		return 0;
		break;

	case WM_KEYDOWN:
		if (oldWndProcTime == NULL)
			oldWndProcTime = time(0);
		keyPressed[wParam] = true;
		return 0;
		newKeyTime = time(0);
		diff = difftime(newKeyTime, oldWndProcTime);
		swprintf_s(str, 30, L"Key press diff: %f\n", diff);
		OutputDebugString(str);
		break;

	case WM_KEYUP:
		keyPressed[wParam] = false;
		return 0;
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, message, wParam, lParam));
}

Directions getDirections() {

	Directions dirs = { false, false, false, false };

	if (keyPressed[VK_UP])
		dirs.up = true;
	if (keyPressed[VK_DOWN])
		dirs.down = true;
	if (keyPressed[VK_LEFT])
		dirs.left = true;
	if (keyPressed[VK_RIGHT])
		dirs.right = true;

	return dirs;
}

/**** Source: Dave Astle: "OpenGL Game Programming" ****/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	WNDCLASSEX windowClass;
	HWND hwnd;
	MSG msg;
	DWORD dwExStyle,
		dwStyle;
	RECT windowRect;

	bool running;

	windowRect.left = (long)0;
	windowRect.right = (long)WIDTH;
	windowRect.top = (long)0;
	windowRect.bottom = (long)HEIGHT;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// default icon
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground = NULL;								// don't need background
	windowClass.lpszMenuName = NULL;								// no menu
	windowClass.lpszClassName = L"MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon

	if (!RegisterClassEx(&windowClass))
		return 0;

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	hwnd = CreateWindowEx(
		NULL, 
		L"MyClass",
		L"Rolling Ball",
		dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0, 
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
		return 0;

	MessageBox(NULL, L"A simple rolling ball game.\nArrow keys move.", L"Rolling Ball", MB_OK);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	running = true;

	// initialize
	gameWorld = new GameWorld(deviceContext);

	while (running) {
		
		Timer::getInstance()->calcStart();

		PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);

		if (msg.message == WM_QUIT)
			running = false;

		else {

			// handle key presses

			// update
			gameWorld->update(getDirections());

			// render
			gameWorld->render(deviceContext);

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Timer::getInstance()->sleep();
	}

	delete gameWorld;

	return msg.wParam;
}