// =========================
// Filename: main.cpp
// =========================

#include <memory>
#include "CSystem.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdshow)
{
    std::unique_ptr<CSystem> system = nullptr;
    bool result;

    // Create the system object.
    system = std::make_unique<CSystem>();
    if (!system)
    {
        return 0;
    }

    // Initialize and run the system object.
    result = system->Initialize();
    if (result)
    {
        system->Run();
    }

    // Shutdown and release the system object.
    system->Shutdown();
    return 0;
}