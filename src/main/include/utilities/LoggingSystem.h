#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>

#define LOG_RESET   "\033[0m"
#define LOG_RED     "\033[31m"
#define LOG_YELLOW  "\033[33m"
#define LOG_GREEN   "\033[32m"
#define LOG_CYAN    "\033[36m"
#define LOG_BLUE    "\033[34m"
#define LOG_PURPLE  "\033[35m"
#define LOG_WHITE   "\033[37m"

#define BOLD        "\033[1m"
#define bold_res    "\033[22m"
#define ITALICS     "\033[3m"
#define UNDERLINE   "\033[4m"

struct ModeInfo {
    std::string color;
    std::string name;
};

extern ModeInfo last_mode;

void SetupLogging();

inline std::string current_time() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t now_c = system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

// default log infos
#define LOG_INFO(value)    { std::cout << "[" << current_time() << "] " << BOLD << LOG_GREEN   << "[INFO] "  << LOG_RESET << value << std::endl; }
#define LOG_WARN(value)    { std::cout << "[" << current_time() << "] " << LOG_YELLOW  << "[WARN] "  << LOG_RESET << value << std::endl; }
#define LOG_ERROR(value)   { std::cerr << "[" << current_time() << "] " << LOG_RED     << "[ERROR] " << LOG_RESET << value << std::endl; }

// mode log infos
#define LOG_AUTONOMOUS(value)   { std::cout << "[" << current_time() << "] " << LOG_PURPLE << "[AUTONOMOUS] "    << LOG_RESET << value << std::endl; }
#define LOG_TELEOP(value)       { std::cout << "[" << current_time() << "] " << LOG_CYAN   << "[TELEOP] "        << LOG_RESET << value << std::endl; }
#define LOG_TEST(value)         { std::cout << "[" << current_time() << "] " << LOG_YELLOW << "[TEST] "          << LOG_RESET << value << std::endl; }
#define LOG_DISABLED(value)     { std::cout << "[" << current_time() << "] " << last_mode.color << last_mode.name << LOG_RESET << value << std::endl; }
