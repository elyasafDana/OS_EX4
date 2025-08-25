#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>
#include <list>
#include <thread>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <mutex>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace graph;
using namespace std::chrono;
using namespace std;


#define PORT 8080

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    // create server socket
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cerr << "Failed to create server socket!" << endl;
        return -1;
    }
    int optval = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        cerr << "Failed to set SO_REUSEADDR option!" << endl;
        close(server_sock);
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);  // port to listen on
    server.sin_addr.s_addr = INADDR_ANY;  // listen on any IP

    // bind socket to address and port
    if (bind(server_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        cerr << "Failed to bind socket to address and port!" << endl;
        return -1;
    }

    // listen for connections
    if (listen(server_sock, 5) == -1) {
        cerr << "Failed to listen for connections!" << endl;
        return -1;
    }

    cout << "Server listening on port " << PORT << "..." << endl;

    // accept client connection
    if ((client_sock = accept(server_sock, (struct sockaddr*)&client, &client_len)) == -1) {
        cerr << "Failed to accept client connection!" << endl;
        return -1;
    }

    cout << "Client connected!" << endl;

    // receive message from client
    char buffer[1024];
    int recv_len;
    if ((recv_len = recv(client_sock, buffer, sizeof(buffer), 0)) == -1) {
        cerr << "Failed to receive message from client!" << endl;
        return -1;
    }

    buffer[recv_len] = '\0';  // terminate string with NULL
    cout << "Message received from client: " << buffer << endl;

    std::string input(buffer, recv_len);
    int v, e, r;
    sscanf(input.c_str(), "%d,%d,%d", &v, &e, &r);

    std::cout << "v=" << v << ", e=" << e << ", r=" << r << std::endl;

    graph::Graph g(v);
    g = g.generateRandomGraph(v,e);
    g.print_graph();

    memset(buffer, 0, sizeof(buffer));

    if ((recv_len = recv(client_sock, buffer, sizeof(buffer), 0)) == -1) {
        cerr << "Failed to receive message from client!" << endl;
        return -1;
    }

    std::string input2(buffer, recv_len);  
    if(input2 == "y"){
       bool EulerCircle =  Algorithms::Euler_circle(g,r);

       if (EulerCircle)
       {
            // send response to client
            const char* message = "There IS an Euler circle in this graph!";
            if (send(client_sock, message, strlen(message), 0) == -1) {
                cerr << "Sending failed!" << endl;
                return -1;
            }

       }else{
            // send response to client
            const char* message = "There is NOT an Euler circle in this graph!";
            if (send(client_sock, message, strlen(message), 0) == -1) {
                cerr << "Sending failed!" << endl;
                return -1;
            }
       }

       cout << "The message has been sent" << endl;

       // close sockets
       close(client_sock);
       close(server_sock);
    }
    else{
        // close sockets
        close(client_sock);
        close(server_sock);
    }

    return 0;
}
