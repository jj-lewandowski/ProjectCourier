#include "MainWindow.h"
#include <commctrl.h>                                                               //This includes the control class names like WC_TREEVIEW or WC_LISTVIEW

#pragma comment(lib, "comctl32.lib")                                                //Tells the linker to pull the binaries for common controls when bulding

HWND g_hTreeView = NULL;
HWND g_hListView = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_CREATE: {                                                               //Here we handle a WM_CREATE message that came from the message loop
        HINSTANCE hInstance = ((LPCREATESTRUCT)lParam)->hInstance;                  //We extract the hInstance that came in the lParam from the message

        //We create the SysTreeView32 on the left
        g_hTreeView = CreateWindowExW(
            0,                                                                      //Extended Style
            WC_TREEVIEWW,                                                            //Class Name that was loaded in the InitCommonControlsEx call in main.cpp
            NULL,                                                                   //The name of the window, since we don't want one we pass in NULL
            WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS |     //The styles that we want to create, these are default window styles
            TVS_LINESATROOT,                                                        //but also styles for the treeview
            0,                                                                      //X - initial horizontal position
            0,                                                                      //Y - initial vertical position
            0,                                                                      //nWidth - width in device units of the window
            0,                                                                      //nLength - lenght in device units of the window
            hwnd,                                                                   //handle to the parent window, here we pass the hwnd from the WindowProc
            (HMENU)1,                                                               //identifier for our child window, here it's 1 and the list view will have 2
            hInstance,                                                              //handle to an instance of our window we got from lParam of the WindowProc function
            NULL                                                                    //pointer to the value to be passed to the window through the CREATESTURCT structure
        );
        //We create the SysListView32 on the right in Report Mode
        g_hListView = CreateWindowExW(
            0,
            WC_LISTVIEW,
            NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
            0,
            0,
            0,
            0,
            hwnd,
            (HMENU)2,
            hInstance,
            NULL
        );
        //We add columns to the List view 
        LVCOLUMN lvc = { 0 };                                                       //Declare a column structure
        lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;                           //We specify which members of the structure are valid here we want to specify the text and width and the subitem

        lvc.pszText = (LPWSTR)L"!";                                                 //We populate the column with the text of the column which in our case is an exclamation mark
        lvc.cx = 30;                                                                //Narrow column for priority indicator which is assigned to the cx property of the column structure
        ListView_InsertColumn(g_hListView, 0, &lvc);                                //We use the InsertColumn function and pass it the handle to the list view, the column id and the pointer to the column struct

        lvc.pszText = (LPWSTR)L"From";                                              //We populate the text of the column for the From column                                          
        lvc.cx = 150;                                                               //We add the width for the From column
        ListView_InsertColumn(g_hListView, 1, &lvc);                                //We insert the column with id 1

        lvc.pszText = (LPWSTR)L"Subject";                                           //We populate the text of the column for the Subject column
        lvc.cx = 300;                                                               //Width for the Subject column
        ListView_InsertColumn(g_hListView, 2, &lvc);                                //We add the column with id 2

        return 0;
    }

    case WM_SIZE: {                                                                 //Case for when a size message comes in from the message queue
        int clientWidth = LOWORD(lParam);                                           //Declare the width for the clinet
        int clientHeight = HIWORD(lParam);                                          //Decalre the height for the client

        int treeWidth = 200;                                                        //We define a fixed sidebar width for the treeview 

        //If the TreeView and ListView are not null
        if (g_hTreeView && g_hListView) {                                           
            MoveWindow(g_hTreeView, 0, 0, treeWidth, clientHeight, TRUE);           //position the treeView on the left side

            //position ListView to take up the remaining space on the right
            MoveWindow(g_hListView, treeWidth, 0, clientWidth - treeWidth, clientHeight, TRUE); 
            
            int col0Width = 40;                                                     //Define fixed width for the ! column
            int col1Width = 150;                                                    //Define fixed width for the From column

            int listViewWdith = clientWidth - treeWidth;                            //Calculate the exact width of the LsitView itself

            int subjectWdith = listViewWdith - (col0Width + col1Width);             //Force the subject column to consume all remaining space

            //Safety check to ensure it never collapses below a minimum readable width
            if (subjectWdith < 100) {
                subjectWdith = 100;
            }

            //Apply the wdiths to the ListView columns
            ListView_SetColumnWidth(g_hListView, 0, col0Width);
            ListView_SetColumnWidth(g_hListView, 1, col1Width);
            ListView_SetColumnWidth(g_hListView, 2, subjectWdith);
        }

        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // TODO: Render custom Windows 95 UI elements and two-pane layout here
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}