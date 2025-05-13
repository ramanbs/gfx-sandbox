#pragma once
#include "stdafx.h"

using Microsoft::WRL::ComPtr;

class GfxDevice
{
public:

	bool Init();
	void LoadPipeline();
	void Render();
	void Cleanup();
	void WaitForPreviousFrame();

private:

	void GetHardwareAdapter(
		_In_ IDXGIFactory1* pFactory,
		_Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter, 
		bool requestHighPerformanceAdapter = false);


	static const UINT BACKBUFFERLIMIT = 3;

	ComPtr<ID3D12Device> m_device;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;

	//Resource
	ComPtr<ID3D12Resource> m_renderTargetView[BACKBUFFERLIMIT];

	//Fence
	UINT64 m_fenceValue[BACKBUFFERLIMIT];
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;

	int m_gpuFrameIndex;
	bool m_useWarpDevice;
};

