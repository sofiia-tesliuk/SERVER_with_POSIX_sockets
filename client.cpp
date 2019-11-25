#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define DESIRED_ADDRESS "127.0.0.1"
#define DESIRED_PORT 3500
#define BUFSIZE 512

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == -1){
        std::cerr << "CLIENT: Failed to create socket." << std::endl;
        close(client_socket);
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DESIRED_PORT);
    int server_socket = connect(client_socket, (struct sockaddr*) &addr, sizeof(addr));
    if (server_socket == -1) {
        std::cerr << "CLIENT: Failed to connect." << std::endl;
        perror("Connection error");
        close(client_socket);
        return EXIT_FAILURE;
    }
    
    char buf[BUFSIZE];
    buf[0] = 't';
    if (send(client_socket, buf, 1, 0) == -1) {
        std::cerr << "CLIENT: Failed to send." << std::endl;
        perror("Send error");
        close(client_socket);
        close(server_socket);
        return EXIT_FAILURE;
    }

    close(client_socket);
    return 0;
}