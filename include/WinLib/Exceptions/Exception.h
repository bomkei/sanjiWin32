#pragma once

#include <string>

namespace WinLib {
  class Exception {
  public:
    virtual std::wstring what() const {
      return L"exception";
    }
  };
}