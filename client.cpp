#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "send_receive.h"

#define DESIRED_PORT 3500
#define BUFSIZE 512

int main(int argc, char** argv){

    if (argc < 3){
        std::cerr << "CLIENT: Too few arguments.\nUsage: client <server_ip> <d|t|h|m> [message]" << std::endl;
        return EXIT_FAILURE;
    }

    // Creating client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == -1){
        std::cerr << "CLIENT: Failed to create socket." << std::endl;
        close(client_socket);
        return EXIT_FAILURE;
    }

    // Configuration of server
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DESIRED_PORT);
//    addr.sin_addr.s_addr = inet_addr(argv[1]);
//    std::cout << argv[1] << std::endl;
    int server_socket = connect(client_socket, (struct sockaddr*) &addr, sizeof(addr));
    if (server_socket == -1) {
        std::cerr << "CLIENT: Failed to connect." << std::endl;
        close(client_socket);
        return EXIT_FAILURE;
    }

    // Buffer for messages
    char buf[BUFSIZE];

    // Sending option
    char option = argv[2][0];
    buf[0] = option;
    buf[1] = '\0';

    if (!((option == 'd') || (option == 't') || (option == 'h') || (option == 'm'))){
        std::cerr << "CLIENT: Invalid option.\nUsage: client <server_ip> <d|t|h|m> [message]" << std::endl;
        return EXIT_FAILURE;
    }

    if (send_option(client_socket, buf) != EXIT_SUCCESS) {
        std::cerr << "CLIENT: Failed to send option." << std::endl;
        close(client_socket);
        return EXIT_FAILURE;
    }

    uint16_t message_length;
    // Sending message
    if ((option == 'm') && (argc > 3)){
        message_length = static_cast<uint16_t>(strlen(argv[3] + 1));
        send_number(client_socket, buf, message_length);
        strncpy (buf, argv[3], static_cast<size_t>(message_length - 1));
        buf[message_length - 1] = '\0';

        if (send_message(client_socket, buf, message_length) != EXIT_SUCCESS) {
            std::cerr << "CLIENT: Failed to send message." << std::endl;
            close(client_socket);
            return EXIT_FAILURE;
        }
    }

    message_length = receive_number(client_socket, buf);
    // Receiving result
    if (receive_message(client_socket, buf, message_length) != EXIT_SUCCESS) {
        std::cerr << "CLIENT: Failed to receive message." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << buf << std::endl;

    close(client_socket);
    return 0;
}