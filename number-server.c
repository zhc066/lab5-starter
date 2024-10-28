#include "http-server.h"
#include <string.h>

char const HTTP_200_OK[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
char const HTTP_404_NOT_FOUND[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\r\n";

int global_num = 0; // Persistent server state

void handle_404(int client_sock, char *url)  {
    printf("SERVER LOG: Got request for unrecognized url \"%s\"\n", url);

    char response_buff[BUFFER_SIZE];
    snprintf(response_buff, BUFFER_SIZE, "Error 404: Unrecognized url \"%s\"\r\n", url);
    // snprintf includes a null-terminator

    write(client_sock, HTTP_404_NOT_FOUND, strlen(HTTP_404_NOT_FOUND));
    write(client_sock, response_buff, strlen(response_buff));
}

void handle_shownum(int client_sock) {
    char response_buff[BUFFER_SIZE];
    snprintf(response_buff, BUFFER_SIZE, "Your number is %d\r\n", global_num);
    // snprintf always null-terminates

    write(client_sock, HTTP_200_OK, strlen(HTTP_200_OK));
    write(client_sock, response_buff, strlen(response_buff));
}

void handle_response(char *request, int client_sock) {
    char url[256], query[256];

    // request looks like:
    // "GET /someurl 1.1\r\n
    printf("SERVER LOG: Got request \"%s\"\n", request);

    char version[10];
    // Parse the request line (method, URL, HTTP version)
    if (sscanf(request, "GET %s %s", url, version) != 1) {
        printf("Invalid request line\n");
        return;
    }

    // show number path
    if (strncmp(url, "/shownum", 8)) { // if url starts with shownum
        handle_shownum(client_sock);
    } else {
        handle_404(client_sock, url);
    }
}

int main(int argc, char *argv[]) {
    int port = 0;
    if(argc >= 2) {
        port = atoi(argv[1]);
    }

    start_server(&handle_response, port);
}




// == STASHED FOR LATER

// // strncpy won't leave room for a null terminator if string is too long,
// // so tell it to use one less than the full size of the buffer

// // Append our actual response
// // When using strncat, need to subtract size of string already in buffer
// strncat(response, msg1,       sizeof(response) - 1 - strlen(response));
// strncat(response, url,        sizeof(response) - 1 - strlen(response));
// strncat(response, msg2,       sizeof(response) - 1 - strlen(response));

       //     "Valid endpoints are:\n"
       //     "    /shownum: prints current value of number\n"
       //     "    /increment: increments number (and prints current value)\n"
       //     "    /add?value=XXX: adds `XXX` (as an integer) to number";
       //
    // use snprintf to fmt the url into a response message
    //char response[BUFFER_SIZE];
    //snprintf(response, BUFFER_SIZE, msg_fmt, url);

// Function to parse the HTTP request
// Returns 1 if the request is valid, 0 otherwise
// uint8_t parse_http_request(char *request, char *url) {
//     char method[10], version[10], host[256];
//
//     // Parse the request line (method, URL, HTTP version)
//     if (sscanf(request, "GET %s %s", url, version) != 1) {
//         printf("Invalid request line\n");
//         return 0;
//     }
//
//     return 1;
// }

