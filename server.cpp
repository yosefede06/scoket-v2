#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "MACROS.h"
#define ERROR_MSG_BIND "Error binding socket"
#define ERROR_MSG_LISTEN "Error listening on socket"
#define ERROR_MSG_RECV "Error receiving message"
#define ERROR_MSG_ACCEPT_FAILURE "Socket accept error"
#define MAX_CLIENTS_LISTENED 1

int get_connection (int s)
{
    int t = accept (s, NULL, NULL); /* socket of connection */
    if (t < 0) {
        printErrorAndExit(ERROR_MSG_ACCEPT_FAILURE);
    }
    return t;
}


int main() {
    sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket < 0) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    if (bind(mySocket, (sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        printErrorAndExit(ERROR_MSG_BIND);
        return 1;
    }

    if (listen(mySocket, MAX_CLIENTS_LISTENED) == -1) {
        printErrorAndExit(ERROR_MSG_LISTEN);
        return 1;
    }

    while (true) {
        int client_sock = get_connection(mySocket);
        if (client_sock == -1) {
            printErrorAndExit(ERROR_MSG_CONNECTION_FAILURE);
            continue;
        }
        bool warm_cycle_flag = true;
        int message_size = FIRST_MESSAGE_SIZE;
        while (message_size <= MB_1) {
            char* message = new char[message_size];
            int curr_recv = 0;
            while (curr_recv < message_size * K_NUM_MESSAGES) {
                int bytes_recv = recv(client_sock, message, message_size, 0);
                if (bytes_recv == -1) {
                    continue;
                }
                curr_recv += bytes_recv;
            }
            char ack = 0;
            if (send(client_sock, &ack, sizeof(ack), 0) != sizeof(ack)) {
                printErrorAndExit(ERROR_MSG_ACK);
                delete[] message;
                close(client_sock);
                return 1;

            }
            delete[] message;
            if(!warm_cycle_flag) {
                message_size *= INCREMENT_MESSAGE_FACTOR;
            }
            else {
                warm_cycle_flag = false;
            }
        }
        close(client_sock);
        close(mySocket);
        return 0;
    }

}
