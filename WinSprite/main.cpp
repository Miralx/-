// WinSprite.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinSprite.h"

#include "SpriteRenderWindow.h"
using namespace SpriteFrameWork;

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    SpriteRenderWindow renderWindow(hInstance);

    renderWindow.Loop();

    return 0;
}