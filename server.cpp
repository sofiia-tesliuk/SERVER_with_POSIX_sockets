#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "additionals.h"
#include "send_receive.h"

#define DESIRED_ADDRESS "127.0.0.1"
#define DESIRED_PORT 3500
#define BUFSIZE 512


int main(int argc, char** argv){
    // Buffer for messages
    char buf[BUFSIZE];
    char buf_number[3];

    // Server configuration
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == -1){
        std::cerr << "SERVER: Failed to create socket." << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Bind some address
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DESIRED_PORT);

    char* ip_address = DESIRED_ADDRESS;

    if (argc > 1)
        ip_address = argv[1];

    addr.sin_addr.s_addr = inet_addr(ip_address);
    if (bind(server_socket, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        std::cerr << "SERVER: Unable to bind address. IP address: " << ip_address << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Listen
    if (listen(server_socket, 1) == -1) {
        std::cerr << "SERVER: Failed to listen." << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }


    int client_socket;
    uint16_t message_length;

    for (int i=0; i < 10; i++) {
        std::cout << "Connection try: " << i << std::endl;
        
        // Accept connection
        socklen_t socklen = sizeof addr;
        client_socket = accept(server_socket, (struct sockaddr *) &addr, &socklen);
        if (client_socket == -1) {
            std::cerr << "SERVER: Failed to accept." << std::endl;
            continue;
        }

        // Receiving option
        if (receive_option(client_socket, buf) != EXIT_SUCCESS) {
            std::cerr << "SERVER: Failed to receive option." << std::endl;
            close(client_socket);
            continue;
        }

        // Processing option
        if (buf[0] == 'h') {
            get_greetings(buf);
        } else if (buf[0] == 'd'){
            get_date(buf);
        } else if (buf[0] == 't'){
            get_time(buf);
        } else if (buf[0] == 'm'){
            message_length = receive_number(client_socket, buf_number);
            receive_message(client_socket, buf, message_length);
            count_words(buf);
        } else {
            std::cerr << "SERVER: Unrecognized option." << std::endl;
            close(client_socket);
            continue;
        }

        send_number(client_socket, buf_number, static_cast<uint16_t>(strlen(buf) + 1));
        // Sending back result
        if (send_message(client_socket, buf, strlen(buf) + 1) != EXIT_SUCCESS) {
            std::cerr << "SERVER: Failed to send message." << std::endl;
            close(client_socket);
            continue;
        }

        close(client_socket);
    }

    // Close server socket
    close(server_socket);
    return EXIT_SUCCESS;
}