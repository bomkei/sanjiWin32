#pragma once

#include <map>

namespace WinLib {
  class Window {
  public:
    HWND hwnd;

    static inline WNDCLASSEX wcex;
    static inline std::map<HWND, Window*> window_map;

    virtual LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) = 0;

    bool show() const;

  protected:
    Window();
  };
}