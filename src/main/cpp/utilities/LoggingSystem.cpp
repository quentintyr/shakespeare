#include "utilities/LoggingSystem.h"
#include "Constants.h"
#include <fstream>

ModeInfo last_mode = {LOG_RESET, "[INIT]"};
std::ofstream logFile;

void SetupLogging() {
    logFile.open(Constants::FILE_PATH, std::ios::out | std::ios::app);
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());
}