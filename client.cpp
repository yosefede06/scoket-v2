#include <chrono>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <fstream>
#include "MACROS.h"
#define DECIMALS_NUMBER 100000.0

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
    //  Warm up cycles
    bool warm_cycle_flag = true;
    struct timeval start, end;

    char* message = new char[MB_1]; // Allocate buffer for largest message size
    int message_size = FIRST_MESSAGE_SIZE;
    while (message_size <= MB_1) {
        gettimeofday(&start, nullptr);
        long int total_bytes_sent = 0;
        while (total_bytes_sent < message_size * K_NUM_MESSAGES) {
            long int byte_sent = send(sock, message, message_size, 0);
            if (byte_sent != message_size) {
                printErrorAndExit(ERROR_MSG_SEND);
                return 1;
            }
            total_bytes_sent += byte_sent;
        }
        char ack;
        if (recv(sock, &ack, sizeof(ack), 0) != sizeof(ack)) {
            printErrorAndExit(ERROR_MSG_ACK);
            return 1;
        }
        gettimeofday(&end, nullptr);
        if(!warm_cycle_flag) {
            long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
            double throughput = K_NUM_MESSAGES * message_size / elapsed_time;
            cout << message_size << "\t" << round(throughput * DECIMALS_NUMBER) / DECIMALS_NUMBER
            << "\tbytes/microseconds\n";
            message_size *= INCREMENT_MESSAGE_FACTOR;
        }

        else {
            warm_cycle_flag = false;
        }
    }
    delete[] message;
    close(sock);
    return 0;
}
