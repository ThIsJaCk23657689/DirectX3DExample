// =========================
// Filename: CInput.h
// =========================

#pragma once

class CInput
{
public:
    CInput();
    CInput(const CInput&);
    ~CInput();

    void Initialize();

    void KeyDown(unsigned int);
    void KeyUp(unsigned int);

    bool IsKeyDown(unsigned int);

private:
    bool m_keys[256];

};