#pragma once

namespace Sanji {
  class TimelineWindow : public WinLib::Window {
  public:
    using WinLib::Window::Window;

    LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override;
  };
}