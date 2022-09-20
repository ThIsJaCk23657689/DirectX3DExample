// =========================
// Filename: CInput.cpp
// =========================

#include "CInput.h"

CInput::CInput()
{
}

CInput::CInput(const CInput& other)
{
}

CInput::~CInput()
{
}

void CInput::Initialize()
{
    int i;

    // Initialize all the keys to being released and not pressed.
    for (i = 0; i < 256; i++)
    {
        m_keys[i] = false;
    }

    return;
}

void CInput::KeyDown(unsigned int input)
{
    // If a key is pressed then save that state in the key array.
    m_keys[input] = true;
    return;
}

void CInput::KeyUp(unsigned int input)
{
    // If a key is released then clear that state in the key array.
    m_keys[input] = false;
    return;
}

bool CInput::IsKeyDown(unsigned int input)
{
    // Return what state the key is in (pressed/not pressed).
    return m_keys[input];
}