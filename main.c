#include <stdio.h>
#include <string.h>
#include "kitchen_server.h"
#include "order_client.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [server|client]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        run_kitchen_server();
    } 
    else if (strcmp(argv[1], "client") == 0) {
        run_order_client();
    } 
    else {
        printf("Invalid argument. Use 'server' or 'client'\n");
        return 1;
    }

    return 0;
}
