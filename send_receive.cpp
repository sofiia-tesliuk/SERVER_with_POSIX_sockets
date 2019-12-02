#include "send_receive.h"


int receive_message(int socket, char* buf, size_t message_length){
    ssize_t readden = recv(socket, buf, message_length, 0);
    if (readden < 0) {
        std::cerr << "Receive error." << std::endl;
        return EXIT_FAILURE;
    } else if (readden == 0) {
        std::cerr << "Sender orderly shut down the connection." << std::endl;
        return EXIT_FAILURE;
    }

    if (readden < message_length){
        std::cerr << "Received less bytes then requested." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receive_option(int socket, char* buf){
    return receive_message(socket, buf, 1);
}

uint16_t receive_number(int socket, char* buf){
    if (receive_message(socket, buf, sizeof(uint16_t)) == EXIT_SUCCESS){
        uint16_t twoBytes = 0;
        twoBytes = buf[1] << 8;
        twoBytes |= buf[0];
        return twoBytes;
    }
    return static_cast<uint16_t>(-1);
}

int send_message(int socket, char* buf, size_t message_length){
    if (send(socket, buf, message_length, 0) == -1) {
        std::cerr << "Failed to send." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int send_option(int sender_socket, char* buf){
    return send_message(sender_socket, buf, 1);
}

int send_number(int socket, char* buf, uint16_t number){
    buf[0] = number & 0xFF;
    buf[1] = number >> 8;
    return send_message(socket, buf, 2);
}