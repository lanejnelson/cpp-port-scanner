#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


using namespace std;

static unordered_map<int, string> port_map {{21, "FTP"}, {22, "SSH"}, {25, "SMTP"}, {80, "HTTP"}, {443, "HTTPS"}};

void print_summary(vector<int> open_ports, int total_ports) {
    int open_count = open_ports.size();
    int closed_count = total_ports - open_count;
    //cout << endl << endl;
    cout << "-----------------------------------" << endl;
    for (auto port: open_ports) {
        if (port_map.count(port) != 0) {
            cout << port << ": " << port_map[port] << endl;
        }
        else {
            cout << port << ": " << "Unknown Service" << endl;
        }
    }
    cout << "-----------------------------------" << endl;
    cout << "TOTAL" << endl;
    cout << open_count << " OPEN ports" << endl;
    cout << closed_count << " CLOSED ports" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "USAGE: ./scan <IP> <HIGHEST PORT>" << endl;
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    const string ip = argv[1];
    const char * ip_c_str = ip.c_str();
    address.sin_addr.s_addr = inet_addr(ip_c_str);
    int highest_port = stoi(argv[2]);
    vector<int> open_ports;
    // Create socket for connections

    // Loop through all ports
    for (int port = 1; port <= highest_port; port++) {
        address.sin_port = htons(port);
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        int success = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
        if (success == 0) {
            cout << "Port " << port << " is open!" << endl;
            open_ports.push_back(port);
        }
        else {
            cout << "Port " << port << " is closed!" << endl;
        }
        close(sockfd);
    }
    print_summary(open_ports, highest_port);
    //cout << "Hello world!" << endl;
    return 0;
}
