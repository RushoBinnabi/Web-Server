/*ICSI 333. System Fundametals, Spring 2022, Project4
 TA: Sourav Dutta
 Name: Rockwon Seo
 ID:001494901
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    FILE *html_data; //Open a file to serve
    html_data = fopen("index.html", "r");

    char response_data[1024];
    fgets(response_data, 1024, html_data);

    char http_header[2048] = "HTTP/1.1 200 ok\r\n\n";
    strcat(http_header, response_data);

    int server_socket; //Create a socket. 
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address; //Define the address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;
    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
       
    }

    return 0;
}
