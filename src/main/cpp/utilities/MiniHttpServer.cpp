#include "utilities/MiniHttpServer.h"

#include <memory>
#include <thread>
#include <vector>
#include <atomic>

#include <wpi/HttpServerConnection.h>
#include <wpi/HttpParser.h>
#include <wpi/StringRef.h>
#include <wpi/uv/Loop.h>
#include <wpi/uv/Tcp.h>
#include <wpi/uv/Stream.h>

// A tiny handler: you only implement ProcessRequest().
class MiniHttpConnection : public wpi::HttpServerConnection
{
public:
    explicit MiniHttpConnection(std::shared_ptr<wpi::uv::Stream> stream)
        : wpi::HttpServerConnection(std::move(stream)) {}

private:
    void ProcessRequest() override
    {
        using namespace wpi;

        auto url = m_request.GetUrl();       // e.g. "/"
        auto method = m_request.GetMethod(); // HTTP_GET, etc.

        if (method == HTTP_GET && (url == "/" || url == "/index.html"))
        {
            SendResponse(200, "OK", "text/plain; charset=utf-8",
                         "Hello from WPILib HttpServerConnection!\n");
        }
        // json output
        else if (method == HTTP_GET && url == "/json")
        {
            SendResponse(200, "OK", "application/json",
                         R"({"ok":true,"msg":"hi from robot"})");
        }
        else
        {
            SendError(404, "No such path");
        }
    }
};

namespace
{
    std::atomic<bool> g_started{false};
    std::thread g_serverThread;
    // Keep connections alive while in use
    std::vector<std::shared_ptr<MiniHttpConnection>> g_conns;
}

void StartMiniHttpServer(uint16_t port)
{
    if (g_started.exchange(true))
        return;

    g_serverThread = std::thread([port]()
                                 {
    // create a libuv loop
    auto loop = wpi::uv::Loop::Create();

    // create a TCP server socket and bind to 0.0.0.0:port
    auto server = wpi::uv::Tcp::Create(loop);
    server->Bind("0.0.0.0", port);

        server->connection.connect([server]() {
                auto client = server->Accept();
                if (!client) return;
                auto conn = std::make_shared<MiniHttpConnection>(client);
                g_conns.emplace_back(std::move(conn));
        });

        // Start listening with backlog 16
        server->Listen(16);

    // Run the loop in this thread forever
    loop->Run(); });

    g_serverThread.detach();
}