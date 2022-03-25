#include "WinLib.h"

namespace WinLib {
  bool Window::show() const {
    return ShowWindow(this->hwnd, SW_SHOW);
  }

  Window::Window() {
    /*
    CreateWindow 関数の最後にこの Window のポインタ (this) を持たせておくと、
      この関数呼び出しにより lpCreateParams に this が入った CREATESTRUCT へのポインタを
      lParam とした WM_CREATE メッセージが g_wndproc に送信されます。
    */
    this->hwnd = CreateWindow(
      wcex.lpszClassName, TEXT("Yeah"),
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      500, 300,
      nullptr, nullptr,
      wcex.hInstance, this
    );

    if( this->hwnd == nullptr ) {
      throw std::exception();
    }
  }
}