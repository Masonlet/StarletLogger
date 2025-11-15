#pragma once

#include <string>

namespace Starlet::Logger {
  enum class Level {
    Info,
    Debug,
    Warning,
    Error
  };

  bool log(const char* caller, const char* function, const std::string& msg);
  bool debug(const char* caller, const char* function, const std::string& msg);
  bool warning(const char* caller, const char* function, const std::string& msg, bool retValue = false);
  bool error(const char* caller, const char* function, const std::string& msg);
}
