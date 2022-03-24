#include <map>
#include "WinLib.h"
#include "WinLib/Exceptions/RetriedInitialize.h"

#define DEFAULT_WINDOW_WIDTH   600
#define DEFAULT_WINDOW_HEIGHT  300

namespace WinLib {
  namespace {
    bool initialized;

    std::map<HWND, Window*> wndmap;
    WNDCLASSEX wcex;

    LRESULT CALLBACK g_wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
      return wndmap[hwnd]->wndproc(hwnd, msg, wp, lp);
    }
  }

  class WindowImpl {
  public:
    HWND hwnd;

    WindowImpl(std::wstring title, int width, int height) {
      hwnd = CreateWindow(
        wcex.lpszClassName, title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr,
        wcex.hInstance, nullptr
      );

      if( hwnd == nullptr ) {
        throw 5;
      }
    }


  };

  Window::Window()
    : impl(new WindowImpl(L"", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT))
  {
    wndmap[impl->hwnd] = this;
  }
  
  Window::Window(std::wstring title)
    : impl(new WindowImpl(title.c_str(), DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT))
  {
    wndmap[impl->hwnd] = this;
  }
  
  Window::Window(std::wstring title, int width, int height)
    : impl(new WindowImpl(title.c_str(), width, height))
  {
    wndmap[impl->hwnd] = this;
  }
  
  Window::~Window() {

  }

  void Window::show() {
    ShowWindow(impl->hwnd, SW_SHOW);
  }

  Window* Window::get_window(HWND hwnd) {
    return wndmap[hwnd];
  }

  void Window::Initialize(HINSTANCE hInstance) {
    if( initialized ) {
      throw RetriedInitialize();
    }

    wcex = {
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

    if( !RegisterClassEx(&wcex) ) {
      throw 1;
    }

    initialized = true;
  }

  LRESULT CALLBACK Window::wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if( wndmap.contains(hwnd) ) {
      return wndmap[hwnd]->wndproc(hwnd, msg, wp, lp);
    }

    return DefWindowProc(hwnd, msg, wp, lp);
  }

  
}