#include "GfxDevice.h"

void GfxDevice::GetHardwareAdapter(
	_In_ IDXGIFactory1* pFactory,
	_Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
	bool requestHighPerformanceAdapter = false) 
{
	*ppAdapter = nullptr;

	ComPtr<IDXGIAdapter1> adapter;
	ComPtr<IDXGIFactory6> factory;

	if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory))))
	{

	}
}
