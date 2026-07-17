#ifndef LOGX_H
#define LOGX_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

class Logx {
public:
    enum class Level : uint8_t {
        DEBUG = 0,
        INFO  = 1,
        WARN  = 2,
        ERROR = 3,
    };

    static bool colored();

    static const char* level_str(Level level) {
        switch (level) {
            case Level::DEBUG: return "DEBUG";
            case Level::INFO:  return "INFO ";
            case Level::WARN:  return "WARN ";
            case Level::ERROR: return "ERROR";
        }
        return "?????";
    }

    static const char* level_color(Level level) {
        if (!colored()) return "";
        switch (level) {
            case Level::DEBUG: return "\033[36m";  // cyan
            case Level::INFO:  return "\033[32m";  // green
            case Level::WARN:  return "\033[33m";  // yellow
            case Level::ERROR: return "\033[31m";  // red
        }
        return "";
    }

    static const char* reset_color() {
        return colored() ? "\033[0m" : "";
    }

    class LogStream {
    public:
        LogStream(Level level, const char* file, int line)
            : m_level(level), m_file(file), m_line(line) {}

        ~LogStream() {
            std::ostringstream full;
            full << level_color(m_level)
                 << "[" << level_str(m_level) << "] "
                 << reset_color()
                 << m_file << ":" << m_line << " "
                 << m_ss.str() << std::endl;
            std::cerr << full.str();
        }

        template<typename T>
        LogStream& operator<<(const T& val) {
            m_ss << val;
            return *this;
        }

        // Support manipulators like std::endl
        LogStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
            manip(m_ss);
            return *this;
        }

    private:
        Level m_level;
        const char* m_file;
        int m_line;
        std::ostringstream m_ss;

        static std::string timestamp() {
            using namespace std::chrono;
            auto now = system_clock::now();
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
            auto t = system_clock::to_time_t(now);
            std::tm tm;
            localtime_r(&t, &tm);
            std::ostringstream ss;
            ss << std::put_time(&tm, "%H:%M:%S") << '.'
               << std::setfill('0') << std::setw(3) << ms.count();
            return ss.str();
        }
    };

    static LogStream debug(const char* file, int line) {
        return LogStream(Level::DEBUG, file, line);
    }

    static LogStream info(const char* file, int line) {
        return LogStream(Level::INFO, file, line);
    }

    static LogStream warn(const char* file, int line) {
        return LogStream(Level::WARN, file, line);
    }

    static LogStream error(const char* file, int line) {
        return LogStream(Level::ERROR, file, line);
    }
};

#ifdef DEBUG
    #define LOG_DEBUG Logx::debug(__FILE__, __LINE__)
    #define LOG_INFO  Logx::info(__FILE__, __LINE__)
    #define LOG_WARN  Logx::warn(__FILE__, __LINE__)
    #define LOG_ERROR Logx::error(__FILE__, __LINE__)
#else
    // Compile to nothing in release mode
    #define LOG_DEBUG if(false) Logx::debug(__FILE__, __LINE__)
    #define LOG_INFO  if(false) Logx::info(__FILE__, __LINE__)
    #define LOG_WARN  if(false) Logx::warn(__FILE__, __LINE__)
    #define LOG_ERROR if(false) Logx::error(__FILE__, __LINE__)
#endif

#endif // LOGX_H
