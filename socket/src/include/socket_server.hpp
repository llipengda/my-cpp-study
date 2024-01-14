#pragma once

#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.hpp"
#include <cstring>
#include <iostream>
#include <vector>

class socket_server : socket {
public:
    socket_server() : socket() {}

    void bind(int port) { socket::bind(port); }

    void listen(int n = 10) { socket::listen(n); }

    int accept() {
        int connected = socket::accept();
        m_connections.push_back(connected);
        return connected;
    }

    void send_all(std::string_view msg) {
        if (msg.empty()) {
            if (m_last_send_enter) {
                m_send_all(m_last_send + std::string{msg});
                std::cout << "server sent: " << m_last_send + std::string{msg}
                          << std::endl;
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

    void send(int to, std::string_view msg) {
        if (msg.empty()) {
            if (m_last_send_enter) {
                socket::send(to, m_last_send + std::string{msg});
                if (msg == "exit") {
                    m_close(to);
                    return;
                }
                std::cout << "server sent: " << m_last_send + std::string{msg}
                          << std::endl;
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

    const std::string recv(int from, int size = 1024) {
        char* buffer = new char[size];
        std::memset(buffer, 0, size);
        bool ok = socket::recv(from, buffer, size);
        auto res = std::string(buffer);
        delete[] buffer;
        if (!ok || res == "exit\n") {
            send(from, "exit");
            send(from, "");
            std::cout << "[INFO] client " << from << " disconnected" << std::endl;
            m_close(from);
            res = "";
        }
        return res;
    }

    void close() { socket::close(); }

private:
    std::vector<int> m_connections{};

    bool m_last_send_enter{false};

    std::string m_last_send{};

    void m_close(int client) {
        for (auto it = m_connections.begin(); it != m_connections.end(); ++it) {
            if (*it == client) {
                m_connections.erase(it);
                break;
            }
        }
    }

    void m_send_all(std::string_view msg) {
        for (auto& client : m_connections) {
            socket::send(client, msg);
        }
    }
};

#endif // _SERVER_H_
