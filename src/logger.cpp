#include "starlet-logger/logger.hpp"
#include <cstdio>

namespace Starlet::Logger {
  namespace {
    const char* lvlStr(const Level level) {
      switch(level){
        case Level::Debug:   return "DEBUG";
        case Level::Info:    return "INFO";
        case Level::Warning: return "WARNING";
        case Level::Error:   return "ERROR";
        default:             return "UNKNOWN";
      }
    }

    void _log(Level level, const char* caller, const char* function, const std::string& msg, bool retValue = true) {
      FILE* output = (retValue == false) ? stderr : stdout;
      fprintf(output, "[%s %s %s] %s\n", caller, function, lvlStr(level), msg.c_str());
    }
  }

  bool log(const char* caller, const char* function, const std::string& msg) {
    _log(Level::Info, caller, function, msg);
    return true;
  }

  bool debug(const char* caller, const char* function, const std::string& msg) {
#ifndef NDEBUG
    _log(Level::Debug, caller, function, msg);
#endif
    return true;
  }

  bool warning(const char* caller, const char* function, const std::string& msg, bool retValue) {
    _log(Level::Warning, caller, function, msg, retValue);
    return retValue;
  }

  bool error(const char* caller, const char* function, const std::string& msg) {
    _log(Level::Error, caller, function, msg, false);
    return false;
  }
}
