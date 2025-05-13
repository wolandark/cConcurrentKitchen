#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <pthread.h>

#define SOCKET_PATH "/tmp/kitchen_socket"

static void process_order(char *order) {
    printf("Processing order: %s\n", order);
    sleep(5);  // Simulating processing time
    printf("Order ready: %s\n", order);
}

static void* handle_client(void *arg) {
    int client_sock = *(int *)arg;
    char buffer[256];

    read(client_sock, buffer, sizeof(buffer));
    process_order(buffer);
    close(client_sock);
    free(arg);
    return NULL;
}

void run_kitchen_server() {
    int server_sock, *client_sock;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);

    printf("Kitchen server is running...\n");

    while (1) {
        client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_sock);
        pthread_detach(thread);
    }

    close(server_sock);
}
