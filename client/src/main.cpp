#include <windows.h>
#include "MainWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"ProjectCourierWindowClass";

    WNDCLASSW wc = {};                              //Initialize the Class to be empty, and set the properties below
    wc.lpfnWndProc = WindowProc;                    //WindowProc function from the MainWindow.cpp file (include at the top of the file)
    wc.hInstance = hInstance;                       //handle of the instance given by the OS to our program
    wc.lpszClassName = CLASS_NAME;                  //pointer to a class name from above
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    //handle to a system cursor  (standard arrow)
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1); //color for the background 

    if (!RegisterClassW(&wc)) {                     //if the RegisterClass function failed return a 0
        return 0;
    }

    HWND hwnd = CreateWindowExW(
        0,                                          //dwExStyle
        CLASS_NAME,                                 //lpClassName
        L"Project Courier",                         //lpWindowName (Text displayed on the title bar)
        WS_OVERLAPPEDWINDOW,                        //dwStyle
        CW_USEDEFAULT,                              //X (X coordinate for initial horizontal position of the window)
        CW_USEDEFAULT,                              //Y (Y coordinate for initial vertical position of the window) 
        1024,                                       //nWidth (width in device units for the window)
        768,                                        //nHeight (height in device units for the window)
        nullptr,                                    //hWndParent (handle to a parent window null for us as there is no parent)
        nullptr,                                    //hMenu (handle to a menu)
        hInstance,                                  //hInstance (handle to the instance of the module)
        nullptr                                     //lpParam (pointer to custom creation data passed via WM_CREATE)
    );

    if (hwnd == nullptr) {                          //if the handle to the window is broken the program quits.
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);                     //This function shows the window from the handle and show parameters from WinMain function

    MSG msg = {};                                   //Initialize empty message structure
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {   //While there are messages in the queue
        TranslateMessage(&msg);                     //This translates the message from a raw keyboard press to a WM_CHAR message.
        DispatchMessage(&msg);                      //This gives the message to the WindowProc to handle and then when it gets the LRESULT it returns here
    }

    return 0;                                       //Returns a 0 when the program finished correctly (for example when WM_DESTROY was called)
}