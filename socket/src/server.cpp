#include "include/socket_server.hpp"
#include <csignal>
#include <functional>
#include <iostream>
#include <thread>

void handle_connection(socket_server& socket, int client) {
    while (true) {
        auto msg = socket.recv(client);
        if (msg.empty()) {
            break;
        }
        std::cout << "server received from " << client << ": " << msg << std::endl;
        msg = msg.substr(0, msg.size() - 1);
        socket.send_all(msg == "\n" ? "" : msg);
        socket.send_all("");
    }
}

void input(socket_server& socket) {
    while (true) {
        std::string msg{};
        std::getline(std::cin, msg);
        socket.send_all(msg);
        if (msg == "exit") {
            socket.send_all("");
            socket.close();
            exit(0);
        }
    }
}

int main(const int argc, const char** argv) {
    const auto show_usage = [argv]() {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    };

    if (argc != 2) {
        show_usage();
        return 1;
    }

    int port{-1};
    try {
        port = std::stoi(argv[1]);
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

    socket_server server{};

    server.bind(port);
    server.listen();

    std::vector<std::thread> threads{};

    std::thread input_t{input, std::ref(server)};

    while (true) {
        int client = server.accept();
        threads.emplace_back(handle_connection, std::ref(server), client);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}