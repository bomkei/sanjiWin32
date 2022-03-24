#include "WinLib.h"
#include "TimelineWindow.h"

int Main(std::vector<std::wstring> const& args) {
	using namespace Sanji;
	using namespace WinLib;

	TimelineWindow tl_window{ L"my window", 500, 300 };

	tl_window.show();


}