#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

using namespace std;

int main() {
    int clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024] = {0};
    const char* message = "Hello from Client";

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        cout << "Socket creation failed\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Connection failed\n";
        return 1;
    }

    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    buffer[bytesRead] = '\0';
    cout << "Message received from server: " << buffer << endl;

    send(clientSocket, message, strlen(message), 0);
    cout << "Message sent to server: " << message << endl;

    close(clientSocket);
    return 0;
}

