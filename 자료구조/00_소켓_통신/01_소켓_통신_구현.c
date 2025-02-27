#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT            8080
#define BUFFER_SIZE     1024

int main(void) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = { 0 };
    char* message = "Hello from server";

    // 소켓 설정
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("서버 대기 중... 포트 : %d\n", PORT);

    // 접속 대기
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

    // 데이터 수신
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        printf("클라이언트 : %s\n", buffer);
        if (strcmp(buffer, "stop") == 0) break;
    }
    

    // 접속 종료
    closesocket(new_socket);
    closesocket(server_fd);

}