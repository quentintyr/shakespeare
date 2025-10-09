#pragma once
#include <cstdint>

// Start a tiny HTTP server using WPILib's wpi::HttpServerConnection.
// - Responds to GET / with "Hello", and GET /json with a small JSON.
// - Runs in its own thread and uses WPILib's libuv wrappers.
void StartMiniHttpServer(uint16_t port = 8080);