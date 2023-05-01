#ifndef _MACROS_H_
#define _MACROS_H_
#include <iostream>
#include <cstring>
#define SYSTEM_ERROR "system error: "
#define ERROR_MSG_SOCKET_CREATION "Error creating socket"
#define ERROR_MSG_IP_CONVERSION "Error converting IP address"
#define ERROR_MSG_CONNECTION_FAILURE "Connection failure"
#define ERROR_MSG_SEND "Error sending message"
#define ERROR_MSG_ACK "Error sending/receiving acknowledgment"
#define EXIT_FAILURE_CODE 1
#define FIRST_MESSAGE_SIZE 1
#define INCREMENT_MESSAGE_FACTOR 2
#define MB_1 1024 * 1024
/**
 * We decided to use 1000 messages in our program because it takes approximately 20 seconds to complete the execution,
 * and we have observed that this number of messages yields results that are comparable to those obtained with larger
 * numbers of messages such as 5000, 10000, and even 100000.
 */
#define K_NUM_MESSAGES 1000.L
#define DEFAULT_PORT 8081



void printErrorAndExit (std::string errorMsg)
{
    std::cerr << SYSTEM_ERROR << errorMsg << std::endl;
    exit (EXIT_FAILURE_CODE);
}

#endif //_MACROS_H_