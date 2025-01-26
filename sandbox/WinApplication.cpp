#include "WinApplication.h"
/* NTI : https://stackoverflow.com/questions/3152011/why-are-translatemessage-and-dispatchmessage-separate-calls
*/


HWND WinApplication::m_hwnd = nullptr;

bool g_FullScreen = false;


int WinApplication::Run(HINSTANCE hInstance, int nCmdShow)
{
	int width = 1280;
	int height = 720;

	if (g_FullScreen) 
	{
		HMONITOR hmon = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		GetMonitorInfo(hmon, &mi);

		width = mi.rcMonitor.right - mi.rcMonitor.left;
		height = mi.rcMonitor.bottom - mi.rcMonitor.top;
	}

	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"GraphicsSandbox";
	RegisterClassEx(&windowClass);

	RECT windowRect = { 0, 0, width, height };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindow(
		windowClass.lpszClassName,
		L"Graphics Sandbox",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!m_hwnd) 
	{
		MessageBox(nullptr, L" Error Creating Window", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (g_FullScreen)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, 0);
	}

	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd); // Force WM_PAINT to repaint the window without waiting for the message loop to send the event

	MSG msg = {};

	while (msg.message != WM_QUIT) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg); // translates virtual key messages like WM_KEYDOWN and WM_KEYUP to WM_CHAR - which character according to current keyboard layout.
			DispatchMessage(&msg); // Calls the associated windows procedure in WNDCLASSEX struct 
		}
	}

	return static_cast<char>(msg.wParam);
}

LRESULT CALLBACK WinApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{

	switch (message)
	{
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(0, L"Are you sure you want to exit ?", L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					if (MessageBox(0, L"Are you really sure you want to exit ? Really ? Really ?", L"Really ? Really ? ", MB_YESNO | MB_ICONQUESTION) == IDNO)
					{
						if (MessageBox(0, L" You are going to die if you quit now. Now, are you sure ? ", L"Really? Really? Really?", MB_YESNO | MB_ICONQUESTION) == IDYES) 
						{
							DestroyWindow(hWnd);
						}
					}
					
				}
			}
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}