// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  

#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h> 
#include <time.h>
#include <cctype>
#include "resource.h"
#include <string>

// Controls
#define IDC_MAIN_EDIT 102;
#define IDC_MAIN_BUTTON 103;
#define IDI_TIMER1 104;
#define IDC_MAIN_STOPBUTTON 105;

// Global variables  
HWND hEdit;
HWND hWndStartButton;
HWND hWndStopButton;
UINT TimmerID = 0;
int seconds{ 0 };
char nsec;
struct tm fTimer;
char buffer[80];
time_t counter;

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Timer");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// Setup Timer
	fTimer.tm_sec = 0;
	fTimer.tm_min = 0;
	fTimer.tm_hour = 0;
	//TimmerID = SetTimer(hWnd, 104, 1000, (TIMERPROC)NULL);

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Welcome to the new Timer app");

	switch (message)
	{
	case WM_CREATE:
		hEdit = CreateWindowEx(WS_EX_STATICEDGE,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE,
			20,
			30,
			200,
			20,
			hWnd,
			(HMENU)102,
			GetModuleHandle(NULL),
			NULL);
		hWndStartButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Start",
			WS_TABSTOP | WS_VISIBLE |
			WS_CHILD | BS_DEFPUSHBUTTON,
			250,
			30,
			100,
			24,
			hWnd,
			(HMENU)103,
			GetModuleHandle(NULL),
			NULL);
		hWndStopButton = CreateWindowEx(NULL,
			L"BUTTON",
			L"Stop",
			WS_TABSTOP | WS_VISIBLE |
			WS_CHILD | BS_DEFPUSHBUTTON,
			375,
			30,
			100,
			24,
			hWnd,
			(HMENU)105,
			GetModuleHandle(NULL),
			NULL);
		
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 103:
			//auto now = time;
			//SendMessageA(hEdit, WM_SETTEXT, 0, (LPARAM)"Hello");
			SetTimer(hWnd, 1, 1000, NULL);
			break;
		case 105:
			KillTimer(hWnd,1);
			break;
		default:
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.  
		// For this introduction, we just print out "Hello, World!"  
		// in the top left corner.  
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.  

		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:

		//seconds++;
		//nSec = std::to_string(seconds)

		counter++;
		strftime(buffer, 80, "%T", gmtime(&counter));
		SendMessageA(hEdit, WM_SETTEXT, 0, (LPARAM)buffer);
	
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}