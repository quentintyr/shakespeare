#include "utilities/LoggingSystem.h"
#include "Constants.h"
#include <fstream>
#include <cstdio>

ModeInfo last_mode = {LOG_RESET, "[INIT]"};
std::ofstream logFile;

void SetupLogging() {
    std::remove(Constants::FILE_PATH);
    logFile.open(Constants::FILE_PATH, std::ios::out);
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());
}