#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 12345  

using namespace std;

int main() {
    int serverSocket, clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024] = {0};
    const char* message = "Hello from Server";

    // Create a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cout << "Socket creation failed\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;           
    serverAddr.sin_addr.s_addr = INADDR_ANY;    // Accept connections from any IP
    serverAddr.sin_port = htons(PORT);          // Set port (convert to network byte order)

    // Bind the socket to the IP and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Bind failed\n";
        return 1;
    }

    // Listen for incoming connections (max 1 in queue)
    listen(serverSocket, 1);
    cout << "Server is listening on port " << PORT << "...\n";

    // Accept a connection from a client
    socklen_t addrLen = sizeof(serverAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&serverAddr, &addrLen);
    if (clientSocket < 0) {
        cout << "Failed to accept connection\n";
        return 1;
    }

    send(clientSocket, message, strlen(message), 0);
    cout << "Message sent to client: " << message << endl;

    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    buffer[bytesRead] = '\0';  
    cout << "Message received from client: " << buffer << endl;

    close(clientSocket);
    close(serverSocket);

    return 0;
}

