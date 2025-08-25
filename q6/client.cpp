#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

int main() {
    int sock = 0;
    sockaddr_in serv_addr;

    // יצירת socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); 

 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

 
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }
    
        string v;
        string e;
        string r;
        cout << " let's make a new graph "<< endl;
        cout << " please enter number of vertex: "<< endl;
        cin >> v;
        cout << " please enter number of edges: "<< endl;
        cin >> e;
        cout << " please enter the number of the root vertex: : "<< endl;
        cin >> r;
        
       

    
        string commend;
        commend = v +","+ e + "," + r;

        send(sock, commend.c_str(), commend.size(), 0);

        string ans;
        cout << " do you wanna caculate Euler circle? (enter y/n): "<< endl;
        cin >> ans;
    
        send(sock, ans.c_str(), ans.size(), 0);

        char buffer[1024];
        int recv_len;
        if((recv_len = recv(sock, buffer, sizeof(buffer), 0)) == -1) {
        cerr << "you cant recev masseges from the server" << endl;
        return -1;
    }

    buffer[recv_len] = '\0';  
    cout << "the massege from the server: " << buffer << endl;

}
