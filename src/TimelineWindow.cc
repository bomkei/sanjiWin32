#include "WinLib.h"
#include "TimelineWindow.h"

namespace Sanji {
  LRESULT CALLBACK TimelineWindow::wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    
    switch( msg ) {
      case WM_CREATE: {

        MessageBox(hwnd, TEXT("Hello"), TEXT(""), MB_OK);

        break;
      }

      default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    return 0;
  }

}