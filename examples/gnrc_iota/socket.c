#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "proto_compiled/test.pb.h"

#define PORT 51037
#define MAXLINE 1000

char socket_buffer[1000];
int socket_buffer_length;

extern int send_test_message(TestMessage * message, int socket, struct sockaddr_in6 * client_addr);

extern int decode_message(TestMessage * message_ptr, uint8_t * encoded_msg_ptr, size_t encoded_msg_size);

typedef enum {
    SETUP_TEST_MESSAGE,
    RPC_SEND_TEST_MESSAGE,
    RPC_RECEIVE_TEST_MESSAGE,
    PRINT_MESSAGE,
    NONE_MESSAGE
} rpc_message_t;

rpc_message_t get_rpc_message_type(uint8_t type){
    switch(type){
        case 88:
            return SETUP_TEST_MESSAGE;
        case 91:
            return PRINT_MESSAGE;
        case 92:
            return RPC_RECEIVE_TEST_MESSAGE;
        case 93:
            return RPC_SEND_TEST_MESSAGE;
        default:
            return NONE_MESSAGE;
    }
}

void handle_send_message(int socket, struct sockaddr_in6 * client_addr_ptr){
    puts("Handle send message.");
    TestMessage message = TestMessage_init_zero;
    message.test = 15;
    send_test_message(&message, socket, client_addr_ptr);
}

void handle_receive_message(int socket, struct sockaddr_in6 * client_addr_ptr){
    puts("Handle received message.");
    TestMessage message = TestMessage_init_zero;
    uint8_t * encoded_msg_ptr = &socket_buffer[1];
    decode_message(&message, encoded_msg_ptr, socket_buffer_length - 1);
    int32_t answer = message.test;
    char text[] = "The answer is: ";

    sendto(
            socket, text, sizeof(text), 0,
            (struct sockaddr *)client_addr_ptr, sizeof(struct sockaddr_in6));
    sendto(
            socket, &answer, sizeof(answer), 0,
            (struct sockaddr *)client_addr_ptr, sizeof(struct sockaddr_in6));
}

void debug_server(int fd, struct sockaddr_in6 * client_addr){
    puts("Address: ");
    for(int i = 0; i < 16; i+= 2){
        printf("%x", client_addr->sin6_addr.s6_addr[i]);
        printf("%x:", client_addr->sin6_addr.s6_addr[i + 1]);
    }
    puts("");
    char ntd[] = "Nothing to do";
    sendto(fd, ntd, sizeof(ntd), 0,(struct sockaddr *)client_addr, sizeof(struct sockaddr_in6));
}

static void start_server(void){
    int fd;
    if ( (fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0 ) {
        perror( "socket failed" );
    }
    int addr_len;
    struct sockaddr_in6 client_addr;
    struct sockaddr_in6 server_addr = {.sin6_addr = IPV6_ADDR_UNSPECIFIED};
    memset( &server_addr, 0, sizeof(server_addr) );
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons( PORT );
    server_addr.sin6_scope_id = 0;

    if ( bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
        perror( "bind failed" );
    }

    for ( int i = 0; i < 1000000000; i++ ) {
        int length = recvfrom( fd, socket_buffer,
                sizeof(socket_buffer) - 1, 0, (struct sockaddr *)&client_addr, &addr_len );
        if ( length < 0 ) {
            perror( "recvfrom failed" );
            break;
        }
        socket_buffer[length] = '\0';
        socket_buffer_length = length;

        rpc_message_t message_type = get_rpc_message_type(socket_buffer[0]);

        switch (message_type){
            case SETUP_TEST_MESSAGE:
                puts("Received setup test message.");
                break;
            case PRINT_MESSAGE:
                printf("%s\n", socket_buffer);
                break;
            case RPC_SEND_TEST_MESSAGE:
                handle_send_message(fd, &client_addr);
                break;
            case RPC_RECEIVE_TEST_MESSAGE:
                handle_receive_message(fd, &client_addr);
                break;
            default:
                puts("Nothing to do.");
                debug_server(fd, &client_addr);
                break;
        }

        //char send_chars[] = "bllaaa";
        //sendto ( fd, send_chars, sizeof(send_chars), 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in6) );
    }

    close( fd );
}


int server_cmd(int argc, char **argv){
    int is_start = strcmp(argv[1], "start");

    if (argc < 1 || is_start != 0) {
        printf("usage: %s [start|stop]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        start_server();
        return 0;
    }

    return 0;
}