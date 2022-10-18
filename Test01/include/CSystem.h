// =========================
// Filename: CSystem.h
// =========================

#pragma once

// Pre-Processing Directives
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "CInput.h"
#include "CGraphics.h"

class CSystem
{
public:
    CSystem();
    CSystem(const CSystem&);
    ~CSystem();

    bool Initialize();
    void Shutdown();
    void Run();
    CGraphics* GetGraphics() const { return m_Graphics; };

    LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
    bool Frame();
    void InitializeWindows(int&, int&);
    void ShutdownWindows();

    LPCTSTR m_applicationName;
    HINSTANCE m_hinstance;
    HWND m_hwnd;

    CInput* m_Input;
    CGraphics* m_Graphics;
};

// =========================
// Function Prototypes
// =========================
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// =========================
// Globals
// =========================
static CSystem* ApplicationHandle = 0;