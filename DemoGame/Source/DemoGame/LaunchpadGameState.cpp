#include "DemoGame/PrecompiledHeader.h"
#include "DemoGame/LaunchpadGameState.h"
#include "DemoGame/DemoGame.h"
#include "DemoGame/BaseDemoGameState.h"
#include "Renderer/ImGuiBridge.h"
Log_SetChannel(LaunchpadGameState);

LaunchpadGameState::LaunchpadGameState(DemoGame *pDemoGame)
    : m_pDemoGame(pDemoGame)
{

}

LaunchpadGameState::~LaunchpadGameState()
{

}

void LaunchpadGameState::OnSwitchedIn()
{
    if (!m_pDemoGame->IsQuitPending())
    {
        // run new demo
        //InvokeSkeletalAnimationDemo();
        //InvokeDrawCallStressDemo();
    }

    m_pDemoGame->ActivateImGui();
}

void LaunchpadGameState::OnSwitchedOut()
{
    m_pDemoGame->DeactivateImGui();
}

void LaunchpadGameState::OnBeforeDelete()
{

}

void LaunchpadGameState::OnWindowResized(uint32 width, uint32 height)
{

}

void LaunchpadGameState::OnWindowFocusGained()
{

}

void LaunchpadGameState::OnWindowFocusLost()
{

}

bool LaunchpadGameState::OnWindowEvent(const union SDL_Event *event)
{
    return false;
}

void LaunchpadGameState::OnMainThreadPreFrame(float deltaTime)
{

}

void LaunchpadGameState::OnMainThreadBeginFrame(float deltaTime)
{

}

void LaunchpadGameState::OnMainThreadAsyncTick(float deltaTime)
{
    
}

void LaunchpadGameState::OnMainThreadTick(float deltaTime)
{
    
}

void LaunchpadGameState::OnMainThreadEndFrame(float deltaTime)
{

}

void LaunchpadGameState::OnRenderThreadPreFrame(float deltaTime)
{

}

void LaunchpadGameState::OnRenderThreadBeginFrame(float deltaTime)
{
    // Clear targets. Have to do since no worldrenderer.
    GPUContext *pGPUContext = m_pDemoGame->GetGPUContext();
    pGPUContext->SetRenderTargets(0, nullptr, nullptr);
    pGPUContext->SetFullViewport();
    pGPUContext->ClearTargets(true, true, true);
}

void LaunchpadGameState::OnRenderThreadDraw(float deltaTime)
{
    m_pDemoGame->GetGUIContext()->DrawTextAt(16, 16, g_pRenderer->GetFixedResources()->GetDebugFont(), 32, MAKE_COLOR_R8G8B8_UNORM(255, 255, 255), "Demo selector");

    bool invoked = false;
    ImGui::SetNextWindowPos(ImVec2(16, 64), ImGuiSetCond_Always);
    if (ImGui::Begin("Demo Selector", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        if (ImGui::Button("Skeletal Animation Demo") && !invoked)
        {
            invoked = true;
            QUEUE_MAIN_THREAD_LAMBDA_COMMAND([this]() {
                InvokeSkeletalAnimationDemo();
            });
        }

        if (ImGui::Button("ImGui Demo") && !invoked)
        {
            invoked = true;
            QUEUE_MAIN_THREAD_LAMBDA_COMMAND([this]() {
                InvokeImGuiDemo();
            });
        }

        if (ImGui::Button("Draw Call Stress Demo") && !invoked)
        {
            invoked = true;
            QUEUE_MAIN_THREAD_LAMBDA_COMMAND([this]() {
                InvokeDrawCallStressDemo();
            });
        }

        if (ImGui::Button("Exit") && !invoked)
        {
            invoked = true;
            QUEUE_MAIN_THREAD_LAMBDA_COMMAND([this]() {
                m_pDemoGame->Quit();
            });
        }

        ImGui::End();
    }
}

void LaunchpadGameState::OnRenderThreadEndFrame(float deltaTime)
{

}

bool LaunchpadGameState::RunDemo(BaseDemoGameState *pGameState)
{
    if (!pGameState->Initialize())
    {
        pGameState->Shutdown();
        delete pGameState;
        return false;
    }

    m_pDemoGame->BeginModalGameState(pGameState);
    return true;
}
