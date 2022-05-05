#include "BaseWindow.h"

//public:
BaseWindow::BaseWindow(const int& width, const int& height, std::string& Title) : Height(height), Width(width)
{
    FreeConsole();

    //init
    hInstance = NULL;
    CLASS_NAME = L"Application";
    msg = {};

    //register class
    wc.lpfnWndProc = BaseWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    //create a window
    hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        NULL,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL,
        NULL,
        hInstance,
        this
    );
    SetWindowTextA(hWnd, Title.c_str());

}
BaseWindow::~BaseWindow()
{
    DestroyWindow(hWnd);
}
void BaseWindow::Show()
{
    if (hWnd == NULL)
    {
        return;
    }
    ShowWindow(hWnd, SW_SHOW);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
BOOL BaseWindow::Create(const int& width, const int& height, std::string& Title)
{
    FreeConsole();

    //init
    hInstance = NULL;
    CLASS_NAME = L"Application";
    msg = {};

    //register class
    wc.lpfnWndProc = BaseWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    //create a window
    hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        NULL,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL,
        NULL,
        hInstance,
        this
    );
    SetWindowTextA(hWnd, Title.c_str());
    if (hWnd != NULL)
    {
        return TRUE;
    }
    return FALSE;
}
//private:
LRESULT CALLBACK BaseWindow::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    BaseWindow* bWin = nullptr;
    if (Msg == WM_NCCREATE)
    {
        CREATESTRUCT* create_ptr = reinterpret_cast<CREATESTRUCT*>(lParam);
        bWin = reinterpret_cast<BaseWindow*>(create_ptr->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(bWin));
        bWin->hWnd = hWnd;
    }
    else
    {
        bWin = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (bWin != nullptr)
    {
        return bWin->EventHandle(Msg, wParam, lParam);
    }
    else
    {
        return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }
}