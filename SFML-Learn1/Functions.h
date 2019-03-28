#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include "Movements.h"


enum switches {
	LEFT, RIGHT, UP, DOWN
};

#pragma comment(lib, "ws2_32.lib")


void SendBytes(SOCKET &sock, switches S) {
	if (S == LEFT) {
		send(sock, "Left", sizeof("Left"), NULL);
	}
	else if (S == RIGHT) {
		send(sock, "Right", sizeof("Right"), NULL);
	}
	else if (S == UP) {
		send(sock, "Up", sizeof("Up"), NULL);
	}
	else if (S == DOWN) {
		send(sock, "Down", sizeof("Down"), NULL);
	}
}


bool InitConnection() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		std::cerr << "Couldn't Initialize Winsock" << std::endl;
		return false;
	}
	return true;
}

SOCKET CreateSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
	if (sock == INVALID_SOCKET) {
		return INVALID_SOCKET;
	}
	else {
		return sock;
	}
}

void ConnectSocket(SOCKET &socket, std::string &&ipAddress, int port) {
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	u_long mode = 1;
	ioctlsocket(socket, FIONBIO, &mode);
	int connectResult = connect(socket, (sockaddr*)&hint, sizeof(hint));
}

void bytesCommand(std::vector<std::shared_ptr<Player>> &players, std::string &command, animation_right &animation) {
	if (command == "connected") {
		players.emplace_back(std::make_unique<Player>("Sprites/Character3.png"));
	}
	if (command == " Disconnected") {
		players.pop_back();
	}
	if (command == "Down") {
		players.at(1)->move(0, 4);
		animation.move_down(players.at(1)->sprite);
	}
	if (command == "Left") {
		players.at(1)->move(-4, 0);
		animation.move_left(players.at(1)->sprite);
	}
	if (command == "Right") {
		players.at(1)->move(4, 0);
		animation.move_right(players.at(1)->sprite);
	}
	if (command == "Up") {
		players.at(1)->move(0, -4);
		animation.move_up(players.at(1)->sprite);
	}
}


void movements(std::vector<std::shared_ptr<Player>> &players, animation_right &animation, switches S, float &x, float &y, SOCKET &sock) {
	switch (S) {
	case LEFT: {
		players.at(0)->move(-4, 0);
		animation.move_left(players.at(0)->sprite);
		x -= 4;
		SendBytes(sock, LEFT);
		break;
		}
	case RIGHT: {
		players.at(0)->move(4, 0);
		animation.move_right(players.at(0)->sprite);
		x += 4;
		SendBytes(sock, RIGHT);
		break;
		}
	case DOWN: {
		players.at(0)->move(0, 4);
		animation.move_down(players.at(0)->sprite);
		y += 4;
		SendBytes(sock, DOWN);
		break;
		}
	case UP: {
		players.at(0)->move(0, -4);
		animation.move_up(players.at(0)->sprite);
		y -= 4;
		SendBytes(sock, UP);
		break;
		}
	}
}