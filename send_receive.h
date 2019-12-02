#ifndef SERVER_WITH_POSIX_SOCKETS_SEND_RECEIVE_H
#define SERVER_WITH_POSIX_SOCKETS_SEND_RECEIVE_H

#include <iostream>
#include <sys/socket.h>


int receive_message(int socket, char* buf, size_t message_length);

int receive_option(int socket, char* buf);

int send_message(int socket, char* buf, size_t message_length);

int send_option(int sender_socket, char* buf);

uint16_t receive_number(int socket, char* buf);

int send_number(int socket, char* buf, uint16_t number);

#endif //SERVER_WITH_POSIX_SOCKETS_SEND_RECEIVE_H
