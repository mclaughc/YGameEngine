#include "D3D11Renderer/PrecompiledHeader.h"
#include "D3D11Renderer/D3D11GPUDevice.h"
#include "D3D11Renderer/D3D11GPUContext.h"
#include "D3D11Renderer/D3D11GPUBuffer.h"
#include "D3D11Renderer/D3D11GPUOutputBuffer.h"
#include "Engine/EngineCVars.h"
Log_SetChannel(D3D11GPUDevice);

D3D11SamplerState::D3D11SamplerState(const GPU_SAMPLER_STATE_DESC *pSamplerStateDesc, ID3D11SamplerState *pD3DSamplerState)
    : GPUSamplerState(pSamplerStateDesc), m_pD3DSamplerState(pD3DSamplerState)
{

}

D3D11SamplerState::~D3D11SamplerState()
{
    m_pD3DSamplerState->Release();
}

void D3D11SamplerState::GetMemoryUsage(uint32 *cpuMemoryUsage, uint32 *gpuMemoryUsage) const
{
    if (cpuMemoryUsage != nullptr)
        *cpuMemoryUsage = sizeof(*this) + sizeof(ID3D11SamplerState);

    // approximation
    if (gpuMemoryUsage != nullptr)
        *gpuMemoryUsage = 128;
}

void D3D11SamplerState::SetDebugName(const char *name)
{
    D3D11Helpers::SetD3D11DeviceChildDebugName(m_pD3DSamplerState, name);
}

D3D11RasterizerState::D3D11RasterizerState(const RENDERER_RASTERIZER_STATE_DESC *pRasterizerStateDesc, ID3D11RasterizerState *pD3DRasterizerState)
    : GPURasterizerState(pRasterizerStateDesc), m_pD3DRasterizerState(pD3DRasterizerState)
{

}

D3D11RasterizerState::~D3D11RasterizerState()
{
    m_pD3DRasterizerState->Release();
}

void D3D11RasterizerState::GetMemoryUsage(uint32 *cpuMemoryUsage, uint32 *gpuMemoryUsage) const
{
    if (cpuMemoryUsage != nullptr)
        *cpuMemoryUsage = sizeof(*this) + sizeof(ID3D11RasterizerState);

    // approximation
    if (gpuMemoryUsage != nullptr)
        *gpuMemoryUsage = 128;
}

void D3D11RasterizerState::SetDebugName(const char *name)
{
    D3D11Helpers::SetD3D11DeviceChildDebugName(m_pD3DRasterizerState, name);
}

D3D11DepthStencilState::D3D11DepthStencilState(const RENDERER_DEPTHSTENCIL_STATE_DESC *pDepthStencilStateDesc, ID3D11DepthStencilState *pD3DDepthStencilState)
    : GPUDepthStencilState(pDepthStencilStateDesc), m_pD3DDepthStencilState(pD3DDepthStencilState)
{

}

D3D11DepthStencilState::~D3D11DepthStencilState()
{
    m_pD3DDepthStencilState->Release();
}

void D3D11DepthStencilState::GetMemoryUsage(uint32 *cpuMemoryUsage, uint32 *gpuMemoryUsage) const
{
    if (cpuMemoryUsage != nullptr)
        *cpuMemoryUsage = sizeof(*this) + sizeof(ID3D11DepthStencilState);

    // approximation
    if (gpuMemoryUsage != nullptr)
        *gpuMemoryUsage = 128;
}

void D3D11DepthStencilState::SetDebugName(const char *name)
{
    D3D11Helpers::SetD3D11DeviceChildDebugName(m_pD3DDepthStencilState, name);
}

D3D11BlendState::D3D11BlendState(const RENDERER_BLEND_STATE_DESC *pBlendStateDesc, ID3D11BlendState *pD3DBlendState)
    : GPUBlendState(pBlendStateDesc), m_pD3DBlendState(pD3DBlendState)
{

}

D3D11BlendState::~D3D11BlendState()
{
    m_pD3DBlendState->Release();
}

void D3D11BlendState::GetMemoryUsage(uint32 *cpuMemoryUsage, uint32 *gpuMemoryUsage) const
{
    if (cpuMemoryUsage != nullptr)
        *cpuMemoryUsage = sizeof(*this) + sizeof(ID3D11BlendState);

    // approximation
    if (gpuMemoryUsage != nullptr)
        *gpuMemoryUsage = 128;
}

void D3D11BlendState::SetDebugName(const char *name)
{
    D3D11Helpers::SetD3D11DeviceChildDebugName(m_pD3DBlendState, name);
}


D3D11GPUDevice::D3D11GPUDevice(IDXGIFactory *pDXGIFactory, IDXGIAdapter *pDXGIAdapter, ID3D11Device *pD3DDevice, ID3D11Device1 *pD3DDevice1, DXGI_FORMAT windowBackBufferFormat, DXGI_FORMAT windowDepthStencilFormat)
    : m_pDXGIFactory(pDXGIFactory)
    , m_pDXGIAdapter(pDXGIAdapter)
    , m_pD3DDevice(pD3DDevice)
    , m_pD3DDevice1(pD3DDevice1)
    , m_swapChainBackBufferFormat(windowBackBufferFormat)
    , m_swapChainDepthStencilBufferFormat(windowDepthStencilFormat)
{
    if (m_pDXGIFactory != nullptr)
        m_pDXGIFactory->AddRef();
    if (m_pDXGIAdapter != nullptr)
        m_pDXGIAdapter->AddRef();
    if (m_pD3DDevice != nullptr)
        m_pD3DDevice->AddRef();
    if (m_pD3DDevice1 != nullptr)
        m_pD3DDevice1->AddRef();
}

D3D11GPUDevice::~D3D11GPUDevice()
{
    SAFE_RELEASE(m_pD3DDevice1);
    SAFE_RELEASE(m_pD3DDevice);

    SAFE_RELEASE(m_pDXGIAdapter);
    SAFE_RELEASE(m_pDXGIFactory);
}

GPUSamplerState *D3D11GPUDevice::CreateSamplerState(const GPU_SAMPLER_STATE_DESC *pSamplerStateDesc)
{
    ID3D11SamplerState *pD3DSamplerState = D3D11Helpers::CreateD3D11SamplerState(m_pD3DDevice, pSamplerStateDesc);
    if (pD3DSamplerState == NULL)
        return NULL;

    D3D11SamplerState *pSamplerState = new D3D11SamplerState(pSamplerStateDesc, pD3DSamplerState);
    return pSamplerState;
}

GPURasterizerState *D3D11GPUDevice::CreateRasterizerState(const RENDERER_RASTERIZER_STATE_DESC *pRasterizerStateDesc)
{
    ID3D11RasterizerState *pD3DRasterizerState = D3D11Helpers::CreateD3D11RasterizerState(m_pD3DDevice, pRasterizerStateDesc);
    if (pD3DRasterizerState == NULL)
        return NULL;

    D3D11RasterizerState *pRasterizerState = new D3D11RasterizerState(pRasterizerStateDesc, pD3DRasterizerState);
    return pRasterizerState;
}

GPUDepthStencilState *D3D11GPUDevice::CreateDepthStencilState(const RENDERER_DEPTHSTENCIL_STATE_DESC *pDepthStencilStateDesc)
{
    ID3D11DepthStencilState *pD3DDepthStencilState = D3D11Helpers::CreateD3D11DepthStencilState(m_pD3DDevice, pDepthStencilStateDesc);
    if (pD3DDepthStencilState == NULL)
        return NULL;

    D3D11DepthStencilState *pDepthStencilState = new D3D11DepthStencilState(pDepthStencilStateDesc, pD3DDepthStencilState);
    return pDepthStencilState;
}

GPUBlendState *D3D11GPUDevice::CreateBlendState(const RENDERER_BLEND_STATE_DESC *pBlendStateDesc)
{
    ID3D11BlendState *pD3DBlendState = D3D11Helpers::CreateD3D11BlendState(m_pD3DDevice, pBlendStateDesc);
    if (pD3DBlendState == NULL)
        return NULL;

    D3D11BlendState *pBlendState = new D3D11BlendState(pBlendStateDesc, pD3DBlendState);
    return pBlendState;
}