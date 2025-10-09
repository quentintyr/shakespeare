#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <mutex>

#define WIDGET_LOG_RESET  "</span>";
#define WIDGET_LOG_COLOR  "<span style=\"color:#FFFFFF\">";
#define WIDGET_LOG_WHITE  "<span style=\"color:#FFFFFF\">"
#define WIDGET_LOG_YELLOW "<span style=\"color:#FFFF00\">"

extern std::mutex widget_log_mutex;

void SetupLogWidgets();


inline std::string current_time()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t now_c = system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

#define WIDGET_LOG_INFO(value)                                                                                                  \
    {                                                                                                                    \
        std::lock_guard<std::mutex> lock(widget_log_mutex); \
        std::cout << "[" << current_time() << "] " << BOLD << WIDGET_LOG_YELLOW << "[WIDGET INFO] " << WIDGET_LOG_RESET << value << std::endl; \
    }