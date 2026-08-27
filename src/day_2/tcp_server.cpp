// tcp_server.cpp
// TCP-mottagare för sensordata. Binder till en dokumenterad IP/port,
// accepterar en klient, tar emot JSON och svarar {"status":"ok"}.
#include "net_common.h"

// --- Dokumenterad konfiguration (Del 3 kräver detta i README/kommentarer) ---
constexpr const char* SERVER_IP = "127.0.0.1"; // byt till egen IP vid test mellan datorer
constexpr uint16_t TCP_PORT = 5000;

int main() {
    if (!net_init()) {
        std::cerr << "Kunde inte initiera nätverk.\n";
        return 1;
    }

    socket_t listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) {
        print_last_error("socket()");
        net_cleanup();
        return 1;
    }

    // Tillåter snabb omstart av servern under testning (undviker "address in use")
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR,
               reinterpret_cast<const char*>(&opt), sizeof(opt));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (bind(listen_sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
        print_last_error("bind()");
        CLOSESOCKET(listen_sock);
        net_cleanup();
        return 1;
    }

    if (listen(listen_sock, 1) == SOCKET_ERROR) {
        print_last_error("listen()");
        CLOSESOCKET(listen_sock);
        net_cleanup();
        return 1;
    }

    std::cout << "TCP-server lyssnar pa " << SERVER_IP << ":" << TCP_PORT << " ...\n";

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    socket_t client_sock = accept(listen_sock, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
    if (client_sock == INVALID_SOCKET) {
        print_last_error("accept()");
        CLOSESOCKET(listen_sock);
        net_cleanup();
        return 1;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    std::cout << "Klient ansluten: " << client_ip << ":" << ntohs(client_addr.sin_port) << "\n";

    char buffer[1024] = {};
    int bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Mottagen data (" << bytes_received << " bytes): " << buffer << "\n";

        const char* response = "{\"status\":\"ok\"}";
        send(client_sock, response, static_cast<int>(strlen(response)), 0);
        std::cout << "Svar skickat: " << response << "\n";
    } else if (bytes_received == 0) {
        std::cout << "Klienten stangde anslutningen utan att skicka data.\n";
    } else {
        print_last_error("recv()");
    }

    CLOSESOCKET(client_sock);
    CLOSESOCKET(listen_sock);
    net_cleanup();
    return 0;
}
