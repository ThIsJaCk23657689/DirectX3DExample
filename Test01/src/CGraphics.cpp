// =========================
// Filename: CGraphics.cpp
// =========================

#include "CGraphics.h"
#include "Common.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>

CGraphics::CGraphics() : 
    m_D3D(nullptr),
    m_Camera(nullptr),
    m_Model(nullptr),
    m_TextureShader(nullptr)
{
}

CGraphics::CGraphics(const CGraphics& other)
{
}

CGraphics::~CGraphics()
{
}

bool CGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    bool result;

    // Create the Direct3D object.
    m_D3D = new CD3D;

    // Initialize the Direct3D Object
    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
        return false;
    }

    // Create the camera object.
    m_Camera = new CCamera;
    m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

    // Create and initialize the model object.
    m_Model = new CModel;

    // Set the name of the texture file that we will be loading.
    std::string textureFilename = "assets/textures/wall.jpg";
    result = m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), textureFilename.c_str());
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize model object.", L"Error", MB_OK);
        return false;
    }

    // Create and initialize the texture shader object.
    m_TextureShader = new CTextureShader;
    result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize shader object.", L"Error", MB_OK);
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui Style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(m_D3D->GetDevice(), m_D3D->GetDeviceContext());

    return true;
}

void CGraphics::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    
    // Release the color shader object.
    SAFE_SHUTDOWN_AND_DELETE(m_TextureShader);

    // Release the model object.
    SAFE_SHUTDOWN_AND_DELETE(m_Model);

    // Release the camera object.
    SAFE_DELETE(m_Camera);
    
    // Release the D3D object.
    SAFE_SHUTDOWN_AND_DELETE(m_D3D);

    return;
}

void CGraphics::RenderImGui() 
{
    if (m_ShowDemoWindow)
    {
        ImGui::ShowDemoWindow(&m_ShowDemoWindow);
    }

    {
        ImGui::Begin("Hello ImGui");
        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &m_ShowDemoWindow);
        ImGui::ColorEdit3("Clear Color", (float*)&m_ClearColor);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

bool CGraphics::Frame()
{
    bool result;

    // Render the graphics scene.
    result = Render();
    if (!result)
    {
        return false;
    }

    return true;
}

bool CGraphics::Render()
{
    // ImGui
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    RenderImGui();
    ImGui::Render();

    
    XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
    bool result;
    
    // Clear the buffers to begin the scene.
    m_D3D->BeginScene(m_ClearColor);

    // Generate the view matrix based on the camera's position.
    m_Camera->Render();

    // Get the world, view and projection matrices from the camera and d3d objects.
    m_D3D->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_D3D->GetProjectionMatrix(projectionMatrix);

    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
    m_Model->Render(m_D3D->GetDeviceContext());

    // Render the model using the color shader.
    result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), 
                                     worldMatrix, viewMatrix, projectionMatrix, 
                                     m_Model->GetTexture());
    if (!result) 
    {
        return false;
    }

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Present the rendered scene to the screen.
    m_D3D->EndScene();

    return true;
}