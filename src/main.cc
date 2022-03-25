#include <iostream>
#include "WinLib.h"

namespace Sanji {
  class MyWindow : public WinLib::Window {
  public:
    using WinLib::Window::Window;

    LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override {
      switch( msg ) {
        case WM_CREATE: {


          break;
        }

        case WM_DESTROY: {
          PostQuitMessage(0);
          break;
        }
      }

      return 0;
    }
  };

  int Main(std::vector<std::wstring> const& args) {
    auto w = new MyWindow();

    w->show();

    return 0;
  }
}