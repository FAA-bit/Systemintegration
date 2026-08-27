// udp_sender.cpp
// UDP-sandare for sensordata. Skickar samma JSON-data som TCP-flodet
// till mottagaren, som ett enda datagram.
#include "net_common.h"

// --- Dokumenterad konfiguration (maste matcha udp_receiver.cpp) ---
constexpr const char* RECEIVER_IP = "127.0.0.1";
constexpr uint16_t UDP_PORT = 5001;

constexpr const char* SENSOR_JSON = "{\"sensorId\":\"sensor-01\",\"value\":23.5,\"unit\":\"C\"}";

int main() {
    if (!net_init()) {
        std::cerr << "Kunde inte initiera natverk.\n";
        return 1;
    }

    socket_t sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        print_last_error("socket()");
        net_cleanup();
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    inet_pton(AF_INET, RECEIVER_IP, &addr.sin_addr);

    int bytes_sent = sendto(sock, SENSOR_JSON, static_cast<int>(strlen(SENSOR_JSON)), 0,
                             reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (bytes_sent == SOCKET_ERROR) {
        print_last_error("sendto()");
    } else {
        std::cout << "Skickat till " << RECEIVER_IP << ":" << UDP_PORT << ": " << SENSOR_JSON << "\n";
    }

    CLOSESOCKET(sock);
    net_cleanup();
    return 0;
}
