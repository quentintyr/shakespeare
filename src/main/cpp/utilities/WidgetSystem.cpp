#include "utilities/WidgetSystem.h"

#include "Constants.h"
#include <fstream>
#include <cstdio>
#include <mutex>

std::ofstream widgetLogFile;
std::mutex widget_log_mutex;

void SetupLogWidgets() {
    std::remove(Constants::WIDGET_FILE_PATH);
    widgetLogFile.open(Constants::WIDGET_FILE_PATH, std::ios::out);
    std::cout.rdbuf(widgetLogFile.rdbuf());
    std::cerr.rdbuf(widgetLogFile.rdbuf());
}