// net_common.h
// Gemensam hjälpheader för TCP/UDP-exemplen i Laboration 2.
// Samma server-/klientkod kan kompileras med:
//   - Winsock i Windows
//   - POSIX-sockets i Linux
#pragma once

#include <cstring>
#include <cstdint>
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib") // gäller vid kompilering med MSVC
    using socket_t = SOCKET;
    #define CLOSESOCKET closesocket
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <cerrno>
    using socket_t = int;
    #define CLOSESOCKET close
    constexpr int INVALID_SOCKET = -1;
    constexpr int SOCKET_ERROR = -1;
#endif

// Initierar Winsock (no-op på Linux). Måste anropas innan sockets skapas.
inline bool net_init() {
#ifdef _WIN32
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
#else
    return true;
#endif
}

// Städar upp Winsock (no-op på Linux). Anropas innan programmet avslutas.
inline void net_cleanup() {
#ifdef _WIN32
    WSACleanup();
#endif
}

// Skriver ut senaste nätverksfelet på ett plattformsoberoende sätt.
inline void print_last_error(const std::string& context) {
#ifdef _WIN32
    std::cerr << context << " misslyckades, WSA-fel: " << WSAGetLastError() << "\n";
#else
    std::cerr << context << " misslyckades: " << strerror(errno) << "\n";
#endif
}
