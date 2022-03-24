#pragma once

#include "Exception.h"

namespace WinLib {
  class RetriedInitialize : public Exception {
  public:
    std::wstring what() const override {
      return L"retried initialize";
    }
  };
}