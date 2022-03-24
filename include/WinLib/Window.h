#pragma once

#include <memory>

namespace WinLib {
  class WindowImpl;
  class Window {
    /*
    static std::wstring classname;

    HWND hwnd;

    std::wstring title;
    int width;
    int height;

    bool create_wnd(std::wstring title, int width, int height);
*/
  public:
    Window();
    Window(std::wstring title);
    Window(std::wstring title, int width, int height);
    ~Window();

    void show();
    static Window* get_window(HWND hwnd);

    virtual LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    static void Initialize(HINSTANCE hInstance);

    std::unique_ptr<WindowImpl> impl;
    //static std::map<HWND, Window*> wndmap;
  };
}