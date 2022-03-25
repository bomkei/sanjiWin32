#include <thread>
#include "WinLib.h"

using namespace WinLib;

namespace Sanji {
  int Main(std::vector<std::wstring> const& args);
}

LRESULT CALLBACK g_wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  auto& windowptr = Window::window_map[hwnd];

  if( windowptr ) {
    windowptr->window_proc(hwnd, msg, wp, lp);
  }

  switch( msg ) {
    case WM_CREATE: {
      if( !windowptr ) {
        auto createstruct = (LPCREATESTRUCT)lp;
        windowptr = (Window*)createstruct->lpCreateParams;
      }

      break;
    }

    default: {
      return DefWindowProc(hwnd, msg, wp, lp);
    }
  }

  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  MSG msg;
  std::vector<std::wstring> args;

  Window::wcex = {
    .cbSize = sizeof(WNDCLASSEX),
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = g_wndproc,
    .cbClsExtra = 0,
    .cbWndExtra = 0,
    .hInstance = hInstance,
    .hIcon = nullptr,
    .hCursor = nullptr,
    .hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH),
    .lpszMenuName = nullptr,
    .lpszClassName = TEXT("WINDOW")
  };

  if( !RegisterClassEx(&Window::wcex) ) {
    return -1;
  }

  Sanji::Main(args);

  while( GetMessage(&msg, NULL, 0, 0) ) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}