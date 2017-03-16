// ToggleWindowTopMost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <string>


bool ToggleWindowTopMost(HWND h)
{
    auto style = GetWindowLong(h, GWL_EXSTYLE);
    bool wasSet = (style & WS_EX_TOPMOST) == WS_EX_TOPMOST;
    if (wasSet)
    {
        SetWindowPos(h, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
    else
    {
        SetWindowPos(h, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
    auto styleAfter = GetWindowLong(h, GWL_EXSTYLE);
    bool isSet = (styleAfter & WS_EX_TOPMOST) == WS_EX_TOPMOST;

    return wasSet != isSet;
}


BOOL CALLBACK EnumWindowProc(HWND h, LPARAM p)
{
    char* pattern = reinterpret_cast<char*>(p);
    char title[1024] = {};
    GetWindowTextA(h, title, 1024);
    if (strstr(title, pattern) != nullptr)
    {
        printf("\t0x%08x\t%s\n", h, title);
    }
    return TRUE;
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        int h = 0;
        try
        {
            h = std::stoi(argv[1], nullptr, 16);

            HWND handle = reinterpret_cast<HWND>(h);
            if (IsWindow(handle))
            {
                auto result = ToggleWindowTopMost(handle);
                printf("window top most property switching result: %s\n", result ? "true" : "false");
                return 0;
            }
        }
        catch (std::invalid_argument&)
        {

        }
        // try to search the window that match the string.

        printf("Listing all windows that title matches %s\n", argv[1]);
        EnumWindows(EnumWindowProc, reinterpret_cast<LPARAM>(argv[1]));
        return 0;
        
    }
  
    printf("Usage: \n\tToggleWindowTopMost [handle (hex numbers)] \n Or \n\tToggleWindowTopMost [title (string)] to list the matching windows\n");
    return 0;
}

