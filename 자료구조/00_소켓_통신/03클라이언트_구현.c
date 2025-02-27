#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define IS_CLIENT
#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

DWORD WINAPI thread_tx(LPVOID param);
DWORD WINAPI thread_rx(LPVOID param);

SOCKET sock, new_socket;
typedef enum {
	NONE = 0,
	RUN,
	STOP,
	EXIT
} STATE_APP;

STATE_APP stateApp;

int main(void) {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	struct sockaddr_in address;
	int addrlen = sizeof(address);

	// 소켓 설정
	sock = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
#ifdef IS_CLIENT
	//address.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (inet_pton(AF_INET, SERVER_IP, &address.sin_addr) != 1) {
		printf("inet_pton 변환 실패! 잘못된 IP 주소: %s\n", SERVER_IP);
		return 1;
	}
#else
	address.sin_addr.s_addr = INADDR_ANY;
#endif

	// 소켓 연결
#ifdef IS_CLIENT
	connect(sock, (struct sockaddr*)&address, sizeof(address));
#else
	bind(sock, (struct sockaddr*)&address, sizeof(address));
	listen(sock, 3);

	printf("서버 대기 중... 포트 : %d\n", PORT);

	// 접속 대기(waiting...)
	new_socket = accept(sock, (struct sockaddr*)&address, &addrlen);
#endif

	// 새로운 스레드 생성
	HANDLE thread_transmit, thread_receive;
	thread_transmit = CreateThread(NULL, 0, thread_tx, NULL, 0, NULL);
	if (thread_transmit == NULL) printf("transmit 스레드 생성 실패\n");
	thread_receive = CreateThread(NULL, 0, thread_rx, NULL, 0, NULL);
	if (thread_receive == NULL) printf("receive 스레드 생성 실패\n");

	while (stateApp != EXIT);

	// 접속 종료
	closesocket(new_socket);
	closesocket(sock);

	// 스레드 종료 대기
	//WaitForMultipleObjects(1, thread_transmit, TRUE, INFINITE);
	//WaitForMultipleObjects(1, thread_receive, TRUE, INFINITE);
	// 스레드 핸들 닫기
	CloseHandle(thread_transmit);
	CloseHandle(thread_receive);
}

// 송신 스레드
DWORD WINAPI thread_tx(LPVOID param) {
	char txBuffer[80];
	while (1) {
		fgets(txBuffer, sizeof(txBuffer), stdin);
		if (strncmp(txBuffer, "disconnect", 10) == 0)
			break;
#ifdef IS_CLIENT
		send(sock, txBuffer, strlen(txBuffer), 0);
#else
		send(new_socket, txBuffer, strlen(txBuffer), 0);
#endif
	}
	stateApp = EXIT;
	return 0;
}

// 수신 스레드
DWORD WINAPI thread_rx(LPVOID param) {
	char buffer[BUFFER_SIZE] = { 0 };

	// 데이터 수신
	while (1) {
		memset(buffer, 0, sizeof(buffer));
#ifdef IS_CLIENT
		recv(sock, buffer, BUFFER_SIZE, 0);
#else
		recv(new_socket, buffer, BUFFER_SIZE, 0);
#endif
		if (stateApp == EXIT) break;
		printf("클라이언트 : %s\n", buffer);
		if (strcmp(buffer, "stop") == 0) break;
	}

	return 0;
}