#include <iostream>
#include "WinLib.h"
#include "WinLib/Exceptions/Exception.h"
#include "debug.h"

//static WNDCLASSEX wcex;
static std::vector<std::wstring> args;

int Main(std::vector<std::wstring> const& args);

bool bAttachToConsole()
{
    if (!AttachConsole(ATTACH_PARENT_PROCESS))
    {
        if (GetLastError() != ERROR_ACCESS_DENIED) //already has a console
        {
            if (!AttachConsole(GetCurrentProcessId()))
            {
                DWORD dwLastError = GetLastError();
                if (dwLastError != ERROR_ACCESS_DENIED) //already has a console
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  using namespace WinLib;

  HWND hwnd;
  MSG msg;



/*
  wcex = {
    .cbSize = sizeof(WNDCLASSEX),
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = global_wndproc,
    .cbClsExtra = 0,
    .cbWndExtra = 0,
    .hInstance = hInstance,
    .hIcon = nullptr,
    .hCursor = nullptr,
    .hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH),
    .lpszMenuName = nullptr,
    .lpszClassName = TEXT("yeah")
  };

  if( !RegisterClassEx(&wcex) ) {
    return -1;
  }
  */
  /*
  hwnd = CreateWindow(
    TEXT("yeah"), TEXT("hello"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    400, 200,
    nullptr, nullptr,
    hInstance, nullptr
  );

  if( hwnd == nullptr ) {
    std::cout << "no\n";
    return -1;
  }

  ShowWindow(hwnd, SW_SHOW);
*/

  try {
    if( !bAttachToConsole() ) {
      MessageBox(nullptr, TEXT("bAttachToConsole() was failed"), TEXT(""), MB_OK);
    }

    _msg("starting application");

    Window::Initialize(hInstance);

    //MessageBox(nullptr, TEXT("uo"), TEXT(""), MB_OK);

    Main(args);

    while( GetMessage(&msg, nullptr, 0, 0) ) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    return msg.wParam;
  }
  catch( WinLib::Exception const& e ) {
    MessageBox(nullptr, e.what().c_str(), TEXT("exception has been occurred"), MB_OK);
  }
  catch( ... ) {
    MessageBox(nullptr, TEXT("unhandled exception has been occurred"), TEXT("error"), MB_OK);
  }

  MessageBox(nullptr, TEXT("aaa"), TEXT(""), MB_OK);

  return -1;

  // std::vector<std::wstring> args;

  // TODO: make args

  // return Main(args);
}