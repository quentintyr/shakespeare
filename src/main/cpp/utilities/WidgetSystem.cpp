#include "utilities/WidgetSystem.h"

#include "Constants.h"
#include <fstream>
#include <cstdio>
#include <mutex>

std::ofstream widgetLogFile;
std::mutex log_mutex;

void SetupLogging() {
    std::remove(Constants::WIDGET_FILE_PATH);
    logFile.open(Constants::WIDGET_FILE_PATH, std::ios::out);
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());
}