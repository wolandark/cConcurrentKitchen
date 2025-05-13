#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/kitchen_socket"

static void send_order(const char *order) {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
        perror("Connect failed");
        exit(1);
    }

    write(sock, order, strlen(order) + 1);
    close(sock);
}

void run_order_client() {
    int rep = 20;
    for (int i = 0; i < rep; i++) {
        send_order("Burgerx2 Friesx1");
        sleep(1);
        send_order("Wingsx3");
        sleep(1);
        send_order("Burgerx2 Wingsx3");
    }
}
