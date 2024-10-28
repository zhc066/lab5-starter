#include "http-server.h"
#include <string.h>

int global_num = 0; // Persistent server state


void handle_response(char *request, int client_sock) {
    char url[256];

    printf("\nSERVER LOG: Got request \"%s\"\n", request);

    // Parse the url out of the request line (limit buffer size; sscanf null-terminates)
    if (sscanf(request, "GET %255s", url) != 1) {
        printf("Invalid request line\n");
        return;
    }
    printf("SERVER LOG: Url is \"%s\"\n", url);

    // TODO: Respond appropriately based on the url
}

int main(int argc, char *argv[]) {
    int port = 0;
    if(argc >= 2) {
        port = atoi(argv[1]);
    }

    start_server(&handle_response, port);
}
