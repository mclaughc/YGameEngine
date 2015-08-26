#pragma once
#include "D3D12Renderer/D3D12Common.h"
#include "D3D12Renderer/D3D12ScratchBuffer.h"

class D3D12GPUContext : public GPUContext
{
public:
    D3D12GPUContext(D3D12RenderBackend *pBackend, D3D12GPUDevice *pDevice, ID3D12Device *pD3DDevice);
    ~D3D12GPUContext();

    // Start of frame
    virtual void BeginFrame() override final;

    // State clearing
    virtual void ClearState(bool clearShaders = true, bool clearBuffers = true, bool clearStates = true, bool clearRenderTargets = true) override final;

    // Retrieve RendererVariables interface.
    virtual GPUContextConstants *GetConstants() override final { return m_pConstants; }

    // State Management (D3D12RenderSystem.cpp)
    virtual GPURasterizerState *GetRasterizerState() override final;
    virtual void SetRasterizerState(GPURasterizerState *pRasterizerState) override final;
    virtual GPUDepthStencilState *GetDepthStencilState() override final;
    virtual uint8 GetDepthStencilStateStencilRef() override final;
    virtual void SetDepthStencilState(GPUDepthStencilState *pDepthStencilState, uint8 stencilRef) override final;
    virtual GPUBlendState *GetBlendState() override final;
    virtual const float4 &GetBlendStateBlendFactor() override final;
    virtual void SetBlendState(GPUBlendState *pBlendState, const float4 &blendFactor = float4::One) override final;

    // Viewport Management (D3D12RenderSystem.cpp)
    virtual const RENDERER_VIEWPORT *GetViewport() override final;
    virtual void SetViewport(const RENDERER_VIEWPORT *pNewViewport) override final;
    virtual void SetFullViewport(GPUTexture *pForRenderTarget = NULL) override final;

    // Scissor Rect Management (D3D12RenderSystem.cpp)
    virtual const RENDERER_SCISSOR_RECT *GetScissorRect() override final;
    virtual void SetScissorRect(const RENDERER_SCISSOR_RECT *pScissorRect) override final;

    // Buffer mapping/reading/writing
    virtual bool ReadBuffer(GPUBuffer *pBuffer, void *pDestination, uint32 start, uint32 count) override final;
    virtual bool WriteBuffer(GPUBuffer *pBuffer, const void *pSource, uint32 start, uint32 count) override final;
    virtual bool MapBuffer(GPUBuffer *pBuffer, GPU_MAP_TYPE mapType, void **ppPointer) override final;
    virtual void Unmapbuffer(GPUBuffer *pBuffer, void *pPointer) override final;

    // Texture reading/writing
    virtual bool ReadTexture(GPUTexture1D *pTexture, void *pDestination, uint32 cbDestination, uint32 mipIndex, uint32 start, uint32 count) override final;
    virtual bool ReadTexture(GPUTexture1DArray *pTexture, void *pDestination, uint32 cbDestination, uint32 arrayIndex, uint32 mipIndex, uint32 start, uint32 count) override final;
    virtual bool ReadTexture(GPUTexture2D *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 cbDestination, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool ReadTexture(GPUTexture2DArray *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 cbDestination, uint32 arrayIndex, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool ReadTexture(GPUTexture3D *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 destinationSlicePitch, uint32 cbDestination, uint32 mipIndex, uint32 startX, uint32 startY, uint32 startZ, uint32 countX, uint32 countY, uint32 countZ) override final;
    virtual bool ReadTexture(GPUTextureCube *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 cbDestination, CUBEMAP_FACE face, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool ReadTexture(GPUTextureCubeArray *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 cbDestination, uint32 arrayIndex, CUBEMAP_FACE face, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool ReadTexture(GPUDepthTexture *pTexture, void *pDestination, uint32 destinationRowPitch, uint32 cbDestination, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool WriteTexture(GPUTexture1D *pTexture, const void *pSource, uint32 cbSource, uint32 mipIndex, uint32 start, uint32 count) override final;
    virtual bool WriteTexture(GPUTexture1DArray *pTexture, const void *pSource, uint32 cbSource, uint32 arrayIndex, uint32 mipIndex, uint32 start, uint32 count) override final;
    virtual bool WriteTexture(GPUTexture2D *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 cbSource, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool WriteTexture(GPUTexture2DArray *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 cbSource, uint32 arrayIndex, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool WriteTexture(GPUTexture3D *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 sourceSlicePitch, uint32 cbSource, uint32 mipIndex, uint32 startX, uint32 startY, uint32 startZ, uint32 countX, uint32 countY, uint32 countZ) override final;
    virtual bool WriteTexture(GPUTextureCube *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 cbSource, CUBEMAP_FACE face, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool WriteTexture(GPUTextureCubeArray *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 cbSource, uint32 arrayIndex, CUBEMAP_FACE face, uint32 mipIndex, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;
    virtual bool WriteTexture(GPUDepthTexture *pTexture, const void *pSource, uint32 sourceRowPitch, uint32 cbSource, uint32 startX, uint32 startY, uint32 countX, uint32 countY) override final;

    // Texture copying
    virtual bool CopyTexture(GPUTexture2D *pSourceTexture, GPUTexture2D *pDestinationTexture) override final;
    virtual bool CopyTextureRegion(GPUTexture2D *pSourceTexture, uint32 sourceX, uint32 sourceY, uint32 width, uint32 height, uint32 sourceMipLevel, GPUTexture2D *pDestinationTexture, uint32 destX, uint32 destY, uint32 destMipLevel) override final;

    // Blit (copy) a texture to the currently bound framebuffer. If this texture is a different size, it'll be resized
    virtual void BlitFrameBuffer(GPUTexture2D *pTexture, uint32 sourceX, uint32 sourceY, uint32 sourceWidth, uint32 sourceHeight, uint32 destX, uint32 destY, uint32 destWidth, uint32 destHeight, RENDERER_FRAMEBUFFER_BLIT_RESIZE_FILTER resizeFilter = RENDERER_FRAMEBUFFER_BLIT_RESIZE_FILTER_NEAREST) override final;

    // Mip generation
    virtual void GenerateMips(GPUTexture *pTexture) override final;

    // Query accessing
    virtual bool BeginQuery(GPUQuery *pQuery) override final;
    virtual bool EndQuery(GPUQuery *pQuery) override final;
    virtual GPU_QUERY_GETDATA_RESULT GetQueryData(GPUQuery *pQuery, void *pData, uint32 cbData, uint32 flags) override final;

    // Predicated drawing
    virtual void SetPredication(GPUQuery *pQuery) override final;

    // RT Clearing
    virtual void ClearTargets(bool clearColor = true, bool clearDepth = true, bool clearStencil = true, const float4 &clearColorValue = float4::Zero, float clearDepthValue = 1.0f, uint8 clearStencilValue = 0) override final;
    virtual void DiscardTargets(bool discardColor = true, bool discardDepth = true, bool discardStencil = true) override final;

    // Swap chain
    virtual GPUOutputBuffer *GetOutputBuffer() override final;
    virtual void SetOutputBuffer(GPUOutputBuffer *pSwapChain) override final;
    virtual bool GetExclusiveFullScreen() override final;
    virtual bool SetExclusiveFullScreen(bool enabled, uint32 width, uint32 height, uint32 refreshRate) override final;
    virtual bool ResizeOutputBuffer(uint32 width = 0, uint32 height = 0) override final;
    virtual void PresentOutputBuffer(GPU_PRESENT_BEHAVIOUR presentBehaviour) override final;

    // RT Changing
    virtual uint32 GetRenderTargets(uint32 nRenderTargets, GPURenderTargetView **ppRenderTargetViews, GPUDepthStencilBufferView **ppDepthBufferView) override final;
    virtual void SetRenderTargets(uint32 nRenderTargets, GPURenderTargetView **ppRenderTargets, GPUDepthStencilBufferView *pDepthBufferView) override final;

    // Drawing Setup
    virtual DRAW_TOPOLOGY GetDrawTopology() override final;
    virtual void SetDrawTopology(DRAW_TOPOLOGY topology) override final;

    // Vertex Buffer Setup
    virtual uint32 GetVertexBuffers(uint32 firstBuffer, uint32 nBuffers, GPUBuffer **ppVertexBuffers, uint32 *pVertexBufferOffsets, uint32 *pVertexBufferStrides) override final;
    virtual void SetVertexBuffer(uint32 bufferIndex, GPUBuffer *pVertexBuffer, uint32 offset, uint32 stride) override final;
    virtual void SetVertexBuffers(uint32 firstBuffer, uint32 nBuffers, GPUBuffer *const *ppVertexBuffers, const uint32 *pVertexBufferOffsets, const uint32 *pVertexBufferStrides) override final;
    virtual void GetIndexBuffer(GPUBuffer **ppBuffer, GPU_INDEX_FORMAT *pFormat, uint32 *pOffset) override final;
    virtual void SetIndexBuffer(GPUBuffer *pBuffer, GPU_INDEX_FORMAT format, uint32 offset) override final;

    // Shader Setup
    virtual void SetShaderProgram(GPUShaderProgram *pShaderProgram) override final;

    // constant buffer management
    virtual void WriteConstantBuffer(uint32 bufferIndex, uint32 fieldIndex, uint32 offset, uint32 count, const void *pData, bool commit = false) override final;
    virtual void WriteConstantBufferStrided(uint32 bufferIndex, uint32 fieldIndex, uint32 offset, uint32 bufferStride, uint32 copySize, uint32 count, const void *pData, bool commit = false) override final;
    virtual void CommitConstantBuffer(uint32 bufferIndex) override final;

    // Draw calls
    virtual void Draw(uint32 firstVertex, uint32 nVertices) override final;
    virtual void DrawInstanced(uint32 firstVertex, uint32 nVertices, uint32 nInstances) override final;
    virtual void DrawIndexed(uint32 startIndex, uint32 nIndices, uint32 baseVertex) override final;
    virtual void DrawIndexedInstanced(uint32 startIndex, uint32 nIndices, uint32 baseVertex, uint32 nInstances) override final;

    // Draw calls with user-space buffer
    virtual void DrawUserPointer(const void *pVertices, uint32 vertexSize, uint32 nVertices) override final;

    // Compute shaders
    virtual void Dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ) override final;

    // --- our methods ---

    // accessors
    ID3D12Device *GetD3DDevice() const { return m_pD3DDevice; }
    ID3D12CommandList *GetCurrentCommandList() const { return m_pCurrentCommandList; }
    D3D12GPUShaderProgram *GetD3D12ShaderProgram() const { return m_pCurrentShaderProgram; }

    // create device
    bool Create();

    // access to shader states for the shader mutators to modify
    void SetShaderConstantBuffers(SHADER_PROGRAM_STAGE stage, uint32 index, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);
    void SetShaderResources(SHADER_PROGRAM_STAGE stage, uint32 index, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);
    void SetShaderSamplers(SHADER_PROGRAM_STAGE stage, uint32 index, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);
    void SetShaderUAVs(SHADER_PROGRAM_STAGE stage, uint32 index, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);

    // synchronize the states with the d3d context
    void SynchronizeRenderTargetsAndUAVs();

    // temporarily disable predication to force a call to go through
    void BypassPredication();
    void RestorePredication();

    // create a resource barrier on the current command list
    void ResourceBarrier(ID3D12Resource *pResource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);
    void ResourceBarrier(ID3D12Resource *pResource, uint32 subResource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

private:
    // preallocate constant buffers
    void CreateConstantBuffers();
    bool CreateQueuedFrameData();
    void MoveToNextFrameList();
    bool UpdatePipelineState();

    // allocate from scratch buffer
    bool AllocateScratchBufferMemory(uint32 size, ID3D12Resource **ppScratchBufferResource, uint32 *pScratchBufferOffset, void **ppCPUPointer, D3D12_GPU_VIRTUAL_ADDRESS *pGPUAddress);

    D3D12RenderBackend *m_pBackend;
    D3D12GPUDevice *m_pDevice;
    ID3D12Device *m_pD3DDevice;

    GPUContextConstants *m_pConstants;

    // command allocator/command queue
    ID3D12CommandAllocator *m_pCommandAllocator;
    ID3D12CommandQueue *m_pCommandQueue;

    // Current command list
    ID3D12GraphicsCommandList *m_pCurrentCommandList;
    D3D12ScratchBuffer *m_pCurrentScratchBuffer;

    // Pool of command lists
    struct QueuedFrameData
    {
        ID3D12GraphicsCommandList *pCommandList;
        D3D12ScratchBuffer *pScratchBuffer;
        uint64 FenceValue;
        uint32 FrameNumber;
    };
    MemArray<QueuedFrameData> m_queuedFrameData;
    uint32 m_currentQueuedFrameIndex;

    // state
    RENDERER_VIEWPORT m_currentViewport;
    RENDERER_SCISSOR_RECT m_scissorRect;
    DRAW_TOPOLOGY m_currentTopology;

    D3D12GPUBuffer *m_pCurrentVertexBuffers[D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    uint32 m_currentVertexBufferOffsets[D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    uint32 m_currentVertexBufferStrides[D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    uint32 m_currentVertexBufferBindCount;

    D3D12GPUBuffer *m_pCurrentIndexBuffer;
    GPU_INDEX_FORMAT m_currentIndexFormat;
    uint32 m_currentIndexBufferOffset;

    D3D12GPUShaderProgram *m_pCurrentShaderProgram;

    // constant buffers
    struct ConstantBuffer
    {
        byte *pLocalMemory;
        uint32 Size;
        int32 DirtyLowerBounds;
        int32 DirtyUpperBounds;
    };
    MemArray<ConstantBuffer> m_constantBuffers;

    // shader stage state
    // we can cheat this in d3d by storing pointers to the d3d objects themselves,
    // since they're reference counted by the runtime. even if our wrapper object is
    // deleted by release, the runtime will hold its own reference.
    struct ShaderStageState
    {
        D3D12_GPU_DESCRIPTOR_HANDLE ConstantBuffers[D3D12_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        uint32 ConstantBufferBindCount;
        int32 ConstantBufferDirtyLowerBounds;
        int32 ConstantBufferDirtyUpperBounds;

        D3D12_GPU_DESCRIPTOR_HANDLE Resources[D3D12_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        uint32 ResourceBindCount;
        int32 ResourceDirtyLowerBounds;
        int32 ResourceDirtyUpperBounds;

        D3D12_GPU_DESCRIPTOR_HANDLE Samplers[D3D12_COMMONSHADER_SAMPLER_SLOT_COUNT];
        uint32 SamplerBindCount;
        int32 SamplerDirtyLowerBounds;
        int32 SamplerDirtyUpperBounds;

        D3D12_GPU_DESCRIPTOR_HANDLE UAVs[D3D12_PS_CS_UAV_REGISTER_COUNT];
        uint32 UAVBindCount;
        int32 UAVDirtyLowerBounds;
        int32 UAVDirtyUpperBounds;
    };
    ShaderStageState m_shaderStates[SHADER_PROGRAM_STAGE_COUNT];

    D3D12GPURasterizerState *m_pCurrentRasterizerState;
    D3D12GPUDepthStencilState *m_pCurrentDepthStencilState;
    uint8 m_currentDepthStencilRef;
    D3D12GPUBlendState *m_pCurrentBlendState;
    float4 m_currentBlendStateBlendFactors;
    bool m_pipelineChanged;

    D3D12GPUOutputBuffer *m_pCurrentSwapChain;

    D3D12GPURenderTargetView *m_pCurrentRenderTargetViews[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT];
    D3D12GPUDepthStencilBufferView *m_pCurrentDepthBufferView;
    uint32 m_nCurrentRenderTargets;

    // predication
    GPUQuery *m_pCurrentPredicate;
    //ID3D12Predicate *m_pCurrentPredicateD3D;
    uint32 m_predicateBypassCount;
};



