#pragma once																	//Pragma once is an instruction to the preprocessor to only link this file once
#include <windows.h>															//This header file includes features from the Windows32API (the functions/data types/ macros live in other header files)

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //Here we declare this function that is used in MainWindow.cpp and in main.cpp