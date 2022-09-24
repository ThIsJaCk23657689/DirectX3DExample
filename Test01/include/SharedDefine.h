#pragma once

#ifdef SAFE_RELEASE
#define SAFE_RELESE(p)              { if (p) { (p)->Release();  (p) = NULL; } }
#endif // SAFE_RELEASE

#ifdef SAFE_DELETE
#define SAFE_DELETE(p)              { if (p) { delete (p);      (p) = NULL; } }
#endif // SAFE_DELETE

#ifdef SAFE_D3D_CALL
#define SAFE_D3D_CALL(x)            { if(FAILED(x)) assert(0); }
#endif // SAFE_D3D_CALL

#define PI 3.14159265358979323846