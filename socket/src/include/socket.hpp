#pragma once

#ifndef _SIMPLE_SOCKET_H_
#define _SIMPLE_SOCKET_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unistd.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

class socket {
public:
    socket() : m_descriptor(-1) {
#ifdef _WIN32
        WSADATA wsa_data;
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }
#endif
        m_descriptor = ::socket(AF_INET, SOCK_STREAM, 0);
        if (m_descriptor < 0) {
            throw std::runtime_error("create socket failed");
        }
    }

    virtual ~socket() noexcept { m_close_socket(); }

    void bind(int port) {
        if (port < 0 || port > 65535) {
            m_close_socket();
            throw std::runtime_error("invalid port");
        }

        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        if (::bind(m_descriptor, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            m_close_socket();
            throw std::runtime_error("bind to port " + std::to_string(port) + " failed\n maybe the port is already in use");
        } else {
            m_info("bind to port " + std::to_string(port));
        }
    }

    void listen(int n = 10) {
        if (::listen(m_descriptor, n) == -1) {
            m_close_socket();
            throw std::runtime_error("listen socket failed");
        } else {
            m_info("listening");
        }
    }

    int accept() {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int connected =
            ::accept(m_descriptor, (sockaddr*)&client_addr, &client_addr_len);
        if (connected == -1) {
            m_close_socket();
            throw std::runtime_error("accept socket failed");
        } else {
            m_info("accept socket id " + std::to_string(connected) + " from " + std::string(inet_ntoa(client_addr.sin_addr)) + ":" + std::to_string(ntohs(client_addr.sin_port)));
        }
        return connected;
    }

    int connect(const char* ip, int port) {
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_port = htons(port);

        int connected = ::socket(AF_INET, SOCK_STREAM, 0);

        if (::connect(connected, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            m_close_socket();
            throw std::runtime_error("connect to " + std::string(ip) + ":" + std::to_string(port) + " failed");
        } else {
            m_info("connect to " + std::string(ip) + ":" + std::to_string(port));
        }
        return connected;
    }

    int connect(std::string ip, int port) { return connect(ip.c_str(), port); }

    int connect(std::string_view ip, int port) {
        return connect(ip.data(), port);
    }

    void send(int to, const char* data, int len) {
        if (::send(to, data, len, 0) == -1) {
            m_error("send data to " + std::to_string(to) + " failed");
        }
    }

    void send(int to, std::string_view data) {
        send(to, data.data(), data.size());
    }

    bool recv(int from, char* data, int len) {
        int read_num = ::recv(from, data, len, 0);
        if (read_num == -1) {
            m_error("recv data from " + std::to_string(from) + " failed");
            return false;
        }
        if (read_num == 0) {
            return false;
        }
        return true;
    }

    void close() { m_close_socket(); }

private:
    int m_descriptor;

    void m_close_socket() {
        if (m_descriptor != -1) {
            m_info("socket closed");
            ::close(m_descriptor);
            m_descriptor = -1;
        }
    }

    void m_info(const std::string& msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void m_error(const std::string& msg) {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
};

#endif // _SIMPLE_SOCKET_H_