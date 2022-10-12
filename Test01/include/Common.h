#pragma once

#define SAFE_RELEASE(p)					{ if (p) { (p)->Release();  (p) = NULL; } }
#define SAFE_DELETE(p)					{ if (p) { delete (p);      (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)			{ if (p) { delete[] (p);    (p) = NULL; } }
#define SAFE_SHUTDOWN_AND_DELETE(p)		{ if (p) { (p)->Shutdown(); delete (p);      (p) = NULL; } }
#define SAFE_D3D_CALL(x)				{ if(FAILED(x)) assert(0); }

#define PI 3.14159265358979323846