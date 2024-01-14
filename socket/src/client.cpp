#include "include/socket_client.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

bool check_ipv4(std::string& addr) {
    if (addr.empty() || addr.back() == '.' || addr.front() == '.') {
        return false;
    }
    if (addr == "localhost") {
        addr = "127.0.0.1";
    }
    int num{0};
    int dot{0};
    for (auto& c : addr) {
        if (c == '.') {
            if (num < 0 || num > 255) {
                return false;
            }
            num = 0;
            ++dot;
            continue;
        }
        if (c < '0' || c > '9') {
            return false;
        }
        num = num * 10 + (c - '0');
    }
    if (num < 0 || num > 255 || dot != 3) {
        return false;
    }
    return true;
}

void receive(socket_client& socket) {
    while (true) {
        auto msg = socket.recv();
        if (msg.empty()) {
            socket.close();
            exit(0);
        }
        std::cout << "received: " << msg << std::endl;
    }
}

int main(const int argc, const char** argv) {
    const auto show_usage = [argv]() {
        std::cerr << "Usage: " << argv[0] << " <ip> <port> [--file <file>]" << std::endl;
    };

    if ((argc != 3 && argc != 5) || (argc == 5 && std::string{argv[3]} != "--file")) {
        std::cerr << "Invalid arguments" << std::endl;
        show_usage();
        return 1;
    }

    std::string ip{argv[1]};
    if (!check_ipv4(ip)) {
        std::cerr << "Invalid ip" << std::endl;
        show_usage();
        return 1;
    }

    int port{-1};
    try {
        port = std::stoi(argv[2]);
    } catch (std::exception& e) {
        std::cerr << "Invalid port" << std::endl;
        show_usage();
        return 1;
    }

    if (port < 0 || port > 65535) {
        std::cerr << "Invalid port" << std::endl;
        show_usage();
        return 1;
    }

    socket_client client{};
    client.connect(ip, port);

    std::thread recv_t(receive, std::ref(client));

    if (argc == 5) {
        std::fstream in{argv[4]};
        std::string str{};
        std::string tmp{};
        while (std::getline(in, tmp)) {
            str.append(tmp).append("\n");
        }
        client.send(str);
        client.send("");
    }

    while (true) {
        std::string msg;
        std::getline(std::cin, msg);
        client.send(msg);
    }

    recv_t.join();
}
