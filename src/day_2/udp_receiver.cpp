// udp_receiver.cpp
// UDP-mottagare for sensordata. Binder till en annan port an TCP,
// tar emot ett datagram och skriver ut sandarens adress och JSON.
#include "net_common.h"

// --- Dokumenterad konfiguration ---
constexpr const char* RECEIVER_IP = "127.0.0.1";
constexpr uint16_t UDP_PORT = 5001; // annan port an TCP_PORT (5000)

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

    if (bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        print_last_error("bind()");
        CLOSESOCKET(sock);
        net_cleanup();
        return 1;
    }

    std::cout << "UDP-mottagare lyssnar pa " << RECEIVER_IP << ":" << UDP_PORT << " ...\n";

    sockaddr_in sender_addr{};
    socklen_t sender_len = sizeof(sender_addr);
    char buffer[1024] = {};

    int bytes_received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                   reinterpret_cast<sockaddr*>(&sender_addr), &sender_len);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        char sender_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sender_addr.sin_addr, sender_ip, sizeof(sender_ip));
        std::cout << "Datagram fran " << sender_ip << ":" << ntohs(sender_addr.sin_port) << "\n";
        std::cout << "Mottagen data (" << bytes_received << " bytes): " << buffer << "\n";
    } else {
        print_last_error("recvfrom()");
    }

    CLOSESOCKET(sock);
    net_cleanup();
    return 0;
}
