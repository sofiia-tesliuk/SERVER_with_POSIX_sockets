#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


#define DESIRED_ADDRESS "127.0.0.1"
#define DESIRED_PORT 3500
#define BUFSIZE 512

int main(){
    // Create socket
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

    addr.sin_addr.s_addr = inet_addr(DESIRED_ADDRESS);
    if (bind(server_socket, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        std::cerr << "SERVER: Unable to bind address." << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Listen
    if (listen(server_socket, 1) == -1) {
        std::cerr << "SERVER: Failed to listen." << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Accept connection
    socklen_t socklen = sizeof addr;
    int client_sock = accept(server_socket, (struct sockaddr*) &addr, &socklen);
    if (client_sock == -1) {
        std::cerr << "SERVER: Failed to accept." << std::endl;
        close(server_socket);
        return EXIT_FAILURE;
    }

    // Receive message
    char buf[BUFSIZE];
    ssize_t readden = recv(client_sock, buf, 1, 0);
    if (readden < 0) {
        std::cerr << "SERVER: Receive error." << std::endl;
        close(client_sock);
        close(server_socket);
        return EXIT_FAILURE;
    } else if (readden == 0) {
        std::cerr << "SERVER: Client orderly shut down the connection." << std::endl;
    } else {
        if (readden < 1){
            std::cerr << "SERVER: Received less bytes then requested." << std::endl;
        }
        std::cout << "SERVER: " << buf << std::endl;
        close(client_sock);
    }


    // Close server socket
    close(server_socket);
    return 0;
}