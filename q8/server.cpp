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

#include <bits/stdc++.h>


#include "stradegy.hpp"
#include "factory.hpp"
using namespace graph;
using namespace std::chrono;
using namespace std;


#define PORT 8080

string calculate(string name, Graph& g,int start,int end){
    factory f;
    stradegy* action=f.create(name);
    return action->run(g,start,end);
    
    
}


static int server_sock = -1;
static std::mutex m;
static std::condition_variable cv;
static bool leader_present = false;

static void worker_loop(int tid) {
    for (;;) {
        // --- להפוך למנהיג: להמתין עד שאין מנהיג פעיל ---
        {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [] { return !leader_present; });
            leader_present = true; // אני המנהיג כרגע
        }

        // --- המנהיג ממתין לקליינט חדש ---
        sockaddr_in cli{}; socklen_t clilen = sizeof(cli);
        int client_fd = ::accept(server_sock, (sockaddr*)&cli, &clilen);
        if (client_fd < 0) {
            // שחרור הנהגה כדי שלא ניתקע
            {
                std::lock_guard<std::mutex> lk(m);
                leader_present = false;
                cv.notify_one(); // קדם מנהיג חדש
            }
            if (errno == EINTR) continue;
            perror("accept");
            continue;
        }

        // --- לקדם מנהיג חדש ולרדת להיות Worker ---
        {
            std::lock_guard<std::mutex> lk(m);
            leader_present = false; // מפנה תפקיד
            cv.notify_one();        // מעיר Follower – יהיה המנהיג הבא
        }

        // ====== טיפול בלקוח ======

    cout<<"the current client_fd is: "<< client_fd <<endl;
    char buffer[1024];
    int recv_len;
    if ((recv_len = recv(client_fd, buffer, sizeof(buffer), 0)) == -1) {
        cerr << "Failed to receive message from client!" << endl;
        return;
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
//////////////////////////////////////////////////////////////////



    // memset(buffer, 0, sizeof(buffer));

    // if ((recv_len = recv(client_fd, buffer, sizeof(buffer), 0)) == -1) {
    //     cerr << "Failed to receive message from client!" << endl;
    //     return;
    // }
    
    // std::string input2(buffer, recv_len);  
    string Smessege="Euler circle: "+calculate("Euler circle",g,r,v)+"\n"+"max flow: "+calculate("max flow",g,r,v)+"\n"+"count cliques: "+calculate("count cliques",g,r,v)+"\n"+"find Max clique: "+calculate("find Max clique",g,r,v)+"\n"+"MST: "+calculate("MST",g,r,v)+"\n";
    
    const char* message = Smessege.c_str();
            if (send(client_fd, message, strlen(message), 0) == -1) {
                cerr << "Sending failed!" << endl;
                return;
            }
       

       cout << "The message has been sent" << endl;
    // close(client_sock);
    // close(server_sock);
        


        // 1) קבלת "V,E,R"
        // std::string header;
        // if (!recv_once(client_fd, header)) {
        //     ::close(client_fd);
        //     continue;
        // }

        // int v = 0, e = 0, r = 0;
        // {
        //     // צורה פשוטה: "V,E,R"
        //     if (sscanf(header.c_str(), "%d,%d,%d", &v, &e, &r) != 3) {
        //         std::string err = "ERROR: bad header, expected V,E,R\n";
        //         send_all(client_fd, err.data(), err.size());
        //         ::close(client_fd);
        //         continue;
        //     }
        //     if (v <= 0 || e < 0 || r < 0 || r >= v) {
        //         std::string err = "ERROR: invalid V/E/R values\n";
        //         send_all(client_fd, err.data(), err.size());
        //         ::close(client_fd);
        //         continue;
        //     }
        // }

        // // 2) בניית גרף רנדומי (לפי הקוד שלך)
        // Graph g(v);
        // try {
        //     g = g.generateRandomGraph(v, e);  // משתמש בפונקציה שלך
        // } catch (...) {
        //     std::string err = "ERROR: failed to generate graph\n";
        //     send_all(client_fd, err.data(), err.size());
        //     ::close(client_fd);
        //     continue;
        // }

        // // אופציונלי: הדפסה לשרת
        // // g.print_graph(); //  :contentReference[oaicite:5]{index=5}

        // // 3) לולאת פקודות: כל פעם מתקבל שם אלגוריתם -> מחזירים תשובה
        // for (;;) {
        //     std::string cmd;
        //     if (!recv_once(client_fd, cmd)) {
        //         // סגר? צא לשירות לקוח הבא
        //         break;
        //     }
        //     // לנקות \r\n אם הגיעו
        //     while (!cmd.empty() && (cmd.back() == '\r' || cmd.back() == '\n')) cmd.pop_back();

        //     if (cmd.empty()) {
        //         std::string err = "ERROR: empty command\n";
        //         send_all(client_fd, err.data(), err.size());
        //         continue;
        //     }

        //     // הפעלת האלגוריתם דרך ה-factory/strategy שלך
        //     std::string result;
        //     try {
        //         result = calculate(cmd, g, r, v);
        //     } catch (const std::exception& ex) {
        //         result = std::string("ERROR: ") + ex.what();
        //     } catch (const char* ex) {
        //         result = std::string("ERROR: ") + ex;
        //     } catch (...) {
        //         result = "ERROR: unknown";
        //     }
        //     if (!result.empty() && result.back() != '\n') result.push_back('\n');
        //     if (!send_all(client_fd, result.data(), result.size())) {
        //         break; // בעיית שידור – נסגור חיבור
        //     }
        // }

        // ::close(client_fd);
        // // חוזר ללופ – יהיה שוב Follower וימתין להיות מנהיג
    }
}

int main() {
    int client_sock;
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

//----------------------------LF----------------------

     // הפעלת Thread-Pool
    const unsigned hw = std::thread::hardware_concurrency();
    const int N = hw ? int(hw) : 4;         // לפחות 4 ת’רדים לנוחות
    std::vector<std::thread> pool;
    pool.reserve(N);
    for (int i = 0; i < N; ++i) pool.emplace_back(worker_loop, i);

    // מנהיג ראשון
    {
        std::lock_guard<std::mutex> lk(m);
        leader_present = false;
        cv.notify_one();
    }

    for (auto& t : pool) t.join();
    ::close(server_sock);
    
    //-----------------------------------------------------------------------------------------

    // accept client connection
//     if ((client_sock = accept(server_sock, (struct sockaddr*)&client, &client_len)) == -1) {
//         cerr << "Failed to accept client connection!" << endl;
//         return -1;
//     }

//     cout << "Client connected!" << endl;

//     // receive message from client
//     char buffer[1024];
//     int recv_len;
//     if ((recv_len = recv(client_sock, buffer, sizeof(buffer), 0)) == -1) {
//         cerr << "Failed to receive message from client!" << endl;
//         return -1;
//     }

//     buffer[recv_len] = '\0';  // terminate string with NULL
//     cout << "Message received from client: " << buffer << endl;

//     std::string input(buffer, recv_len);
//     int v, e, r;
//     sscanf(input.c_str(), "%d,%d,%d", &v, &e, &r);

//     std::cout << "v=" << v << ", e=" << e << ", r=" << r << std::endl;

//     graph::Graph g(v);
//     g = g.generateRandomGraph(v,e);
//     g.print_graph();
// //////////////////////////////////////////////////////////////////



//     memset(buffer, 0, sizeof(buffer));

//     if ((recv_len = recv(client_sock, buffer, sizeof(buffer), 0)) == -1) {
//         cerr << "Failed to receive message from client!" << endl;
//         return -1;
//     }
    
//     std::string input2(buffer, recv_len);  
//     string Smessege=calculate(input2,g,r,v);
//     const char* message = Smessege.c_str();
//             if (send(client_sock, message, strlen(message), 0) == -1) {
//                 cerr << "Sending failed!" << endl;
//                 return -1;
//             }
       

//        cout << "The message has been sent" << endl;
//     // close(client_sock);
//     // close(server_sock);
        

    return 0;
}
