#pragma once

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

class socket_client : socket {
public:
    socket_client()
        : socket(), m_server_descriptor(-1), m_last_send_enter(false) {}

    void connect(std::string_view ip, int port) {
        m_server_descriptor = socket::connect(ip, port);
    }

    void send(std::string_view msg) {
        if (msg.empty()) {
            if (m_last_send_enter) {
                socket::send(m_server_descriptor,
                             m_last_send + std::string{msg});
                std::cout << "client sent: " << m_last_send + std::string{msg} << std::endl;
                if (msg == "exit") {
                    close();
                }
                m_last_send_enter = false;
                m_last_send = "";
                return;
            }
            m_last_send_enter = true;
            m_last_send = "\n";
            return;
        }
        m_last_send.append(msg).append("\n");
        m_last_send_enter = true;
    }

    std::string recv(int size = 1024) {
        char* buffer = new char[size];
        std::memset(buffer, 0, size);
        bool ok = socket::recv(m_server_descriptor, buffer, size);
        auto res = std::string(buffer);
        delete[] buffer;
        if (!ok || res == "exit\n") {
            res = "";
            std::cout << "[INFO] server disconnected" << std::endl;
            close();
        }
        return res;
    }

    void close() {
        if (m_server_descriptor != -1) {
            std::cout << "[INFO] disconnected" << std::endl;
            ::close(m_server_descriptor);
            m_server_descriptor = -1;
        }
        socket::close();
    }

private:
    int m_server_descriptor;
    bool m_last_send_enter;
    std::string m_last_send{};
};

#endif // _CLIENT_H_