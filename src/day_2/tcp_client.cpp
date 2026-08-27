// tcp_client.cpp
// TCP-sandare for sensordata. Ansluter till servern, skickar JSON
// och skriver ut svaret.
#include "net_common.h"

// --- Dokumenterad konfiguration (maste matcha tcp_server.cpp) ---
constexpr const char* SERVER_IP = "127.0.0.1";
constexpr uint16_t TCP_PORT = 5000;

// Samma sensordata som anvands i UDP- och MQTT-flodet, se caset.
constexpr const char* SENSOR_JSON = "{\"sensorId\":\"sensor-01\",\"value\":23.5,\"unit\":\"C\"}";

int main() {
    if (!net_init()) {
        std::cerr << "Kunde inte initiera natverk.\n";
        return 1;
    }

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        print_last_error("socket()");
        net_cleanup();
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
        print_last_error("connect()");
        CLOSESOCKET(sock);
        net_cleanup();
        return 1;
    }
    std::cout << "Ansluten till server " << SERVER_IP << ":" << TCP_PORT << "\n";

    send(sock, SENSOR_JSON, static_cast<int>(strlen(SENSOR_JSON)), 0);
    std::cout << "Skickat: " << SENSOR_JSON << "\n";

    char buffer[512] = {};
    int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Svar fran server: " << buffer << "\n";
    } else if (bytes_received == 0) {
        std::cout << "Servern stangde anslutningen.\n";
    } else {
        print_last_error("recv()");
    }

    CLOSESOCKET(sock);
    net_cleanup();
    return 0;
}
