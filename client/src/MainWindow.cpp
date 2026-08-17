#include "MainWindow.h"                                                             //Here we include the MainWindow header file that contains the declaration for the WindowProc function

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {   //Here we define the WindowProc function, it is defined by me but the func and var names are common standards
    switch (uMsg) {                                                                 //Here we use a switch case on the Message that we get from the DispatchMessage function
    case WM_DESTROY:                                                                //If the Window is being destroyed
        PostQuitMessage(0);                                                         //Tell the program that it can safely stop and quit
        return 0;                                                                   //Returns a 0 to signify that the function completed correctly

    case WM_PAINT: {                                                                //If the Window get a paint message (the system or another application wants to paint a portion of the window
        PAINTSTRUCT ps;                                                             //Declaration of a Paint Structure with the name ps
        HDC hdc = BeginPaint(hwnd, &ps);                                            //HDC is a paintbrush and canvas letting the user paint on the screen. It gets the window handle and the address of the PAINTSTRUCT
        // TODO: Render custom Windows 95 UI elements and two-pane layout here
        EndPaint(hwnd, &ps);                                                        //We release the resources used by BeginPaint
        return 0;                                                                   //Returns a 0 to signify that the function completed correctly
    }
    }   
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);                              //Default Windows built in procedure to handle anything we didn't account for or needed in the switch statement
}