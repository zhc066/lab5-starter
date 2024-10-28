#include "http-server.h"
#include <string.h>

char const* HTTP_200_OK = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";
char const* HTTP_404_NOT_FOUND = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\n";
int num = 0;

// Function to parse the HTTP request
// Returns 1 if the request is valid, 0 otherwise
uint8_t parse_http_request(char *request, char *url) {
    char method[10], version[10], host[256];
    char content_type[50];
    int content_length = 0;

    // Parse the request line (method, URL, HTTP version)
    if (sscanf(request, "%s %s %s", method, url, version) != 3) {
        printf("Invalid request line\n");
        return 0;
    }

    // printf("Method: %s\n", method);
    // printf("URL: %s\n", url);
    // printf("Version: %s\n", version);

    // Move the pointer to start parsing the headers
    char *headers = strstr(request, "\r\n") + 2;

    // Parse headers
    while (strncmp(headers, "\r\n", 2) != 0) {
        if (sscanf(headers, "Host: %s", host) == 1) {
            printf("Host: %s\n", host);
        } else if (sscanf(headers, "Content-Type: %s", content_type) == 1) {
            printf("Content-Type: %s\n", content_type);
        } else if (sscanf(headers, "Content-Length: %d", &content_length) == 1) {
            printf("Content-Length: %d\n", content_length);
        }

        // next header
        headers = strstr(headers, "\r\n") + 2;
    }

    // Validate the method (only GET)
    if (strcmp(method, "GET") != 0) {
        printf("Invalid HTTP method: %s\n", method);
        return 0;
    }

    // Check if Host header is present
    if (strlen(host) == 0) {
        printf("Missing Host header\n");
        return 0;
    }

    // If Content-Length is provided, validate the body
    if (content_length > 0) {
        char *body = strstr(headers, "\r\n\r\n") + 4; // Move past headers
        if ((int)strlen(body) < content_length) {
            printf("Content-Length does not match body size\n");
            return 0;
        }
        printf("Body: %s\n", body);
    }

    return 1;
}

void handle_basic(int client_sock) {
    char const intro[] = {67, 83, 69, 32, 50, 57, 32, 76, 97, 98, 32, 53, 32, 87, 101, 98, 115, 101, 114, 118, 101, 114, 10, 10, 82, 111, 117, 116, 101, 115, 32, 97, 118, 97, 
                          105, 108, 97, 98, 108, 101, 32, 105, 110, 32, 116, 104, 105, 115, 32, 65, 80, 73, 58, 10, 9, 42, 32, 47, 115, 104, 111, 119, 110, 117, 109, 32, 45, 32, 
                          80, 114, 105, 110, 116, 32, 111, 117, 116, 32, 116, 104, 101, 32, 99, 117, 114, 114, 101, 110, 116, 32, 118, 97, 108, 117, 101, 32, 111, 102, 32, 116, 
                          104, 101, 32, 98, 97, 99, 107, 101, 110, 100, 39, 115, 32, 110, 117, 109, 98, 101, 114, 10, 9, 42, 32, 47, 105, 110, 99, 114, 101, 109, 101, 110, 116, 
                          32, 45, 32, 73, 110, 99, 114, 101, 109, 101, 110, 116, 32, 116, 104, 101, 32, 98, 97, 99, 107, 101, 110, 100, 39, 115, 32, 110, 117, 109, 98, 101, 114, 
                          32, 98, 121, 32, 49, 10, 9, 42, 32, 47, 97, 100, 100, 63, 118, 97, 108, 117, 101, 61, 60, 118, 97, 108, 117, 101, 62, 32, 45, 32, 65, 100, 100, 32, 118, 
                          97, 108, 117, 101, 32, 116, 111, 32, 98, 97, 99, 107, 101, 110, 100, 39, 115, 32, 110, 117, 109, 98, 101, 114};

    char response[BUFFER_SIZE];
    strncpy(response, HTTP_200_OK, sizeof(response)-1);
    strncpy(response, intro, sizeof(response)-1);
    write(client_sock, response, strlen(response));
}

void handle_shownum(int client_sock) {
    /*
        YOUR CODE HERE
    */
}

void handle_increment(int client_sock) {
    /*
        YOUR CODE HERE
    */
}

void handle_add(int client_sock, char *query) {
    /*
        YOUR CODE HERE
    */
}

void handle_response(char *request, int client_sock) {
    char url[256], query[256];

    if (!parse_http_request(request, url)) {
        printf("Invalid request header\n");
        return;
    }

    // show number path
    if () {
        handle_shownum();
    } else if () {
        handle_increment();
    } else if () {
        strcpy(query, strchr(url, '?') + 1);
        handle_add();
    } else {
        handle_basic(client_sock);
    }
}

int main(int argc, char *argv[]) {
    int port = 0;
    if(argc >= 2) {
        port = atoi(argv[1]);
    }
    start_server(&handle_response, port);
}