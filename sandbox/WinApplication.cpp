#include "WinApplication.h"

HWND WinApplication::m_hwnd = nullptr;


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
	// UpdateWindow(m_hwnd); Force WM_PAINT to repaint the window without waiting for the message loop to send the event

	MSG msg = {};

	while (msg.message != WM_QUIT) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return static_cast<char>(msg.wParam);
}