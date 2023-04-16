#include <chrono>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "MACROS.h"

using namespace std;



int main(int argc, char** argv) {
    if (argc != 2) {
        printErrorAndExit("Usage: " + (string)argv[0] + " <server-ip>");
        return 1;
    }

    const char* server_ip = argv[1];
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printErrorAndExit(ERROR_MSG_SOCKET_CREATION);
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    // Converts the character string src into a network address structure in the AF_INET (IPv4) address family
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        printErrorAndExit(ERROR_MSG_IP_CONVERSION);
        return 1;
    }

    if (connect(sock, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        printErrorAndExit (ERROR_MSG_CONNECTION_FAILURE);
        return 1;
    }

    char* message = new char[MB_1]; // Allocate buffer for largest message size
    for (int message_size = FIRST_MESSAGE_SIZE; message_size <= MB_1; message_size *= INCREMENT_MESSAGE_FACTOR) {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < K_NUM_MESSAGES; ++i) {
            int byte_sent = send(sock, message, message_size, 0);
            if (byte_sent != message_size) {
                cout << byte_sent;
                printErrorAndExit(ERROR_MSG_SEND);
                return 1;
            }
        }
        char ack;
        if (recv(sock, &ack, sizeof(ack), 0) != sizeof(ack)) {
            printErrorAndExit(ERROR_MSG_ACK);
            return 1;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        double elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000000.0;
        double throughput = K_NUM_MESSAGES * message_size / elapsed_time;

        cout << message_size << "\t" << throughput << "\tbytes/s\n";
    }

    delete[] message;
    close(sock);

    return 0;
}
