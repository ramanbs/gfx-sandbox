#include "stdafx.h"
#include "Winapplication.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) 
{
	return WinApplication::Run(hInstance, nCmdShow);
}