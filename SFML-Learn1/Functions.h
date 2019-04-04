#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include "Movements.h"
#include "UI.h"


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

void bytesCommand(std::vector<std::shared_ptr<Player>> &players, std::string &command) {
	if (command == "connected") {
		players.emplace_back(std::make_unique<Player>("Sprites/Character3.png"));
	}
	if (command == " Disconnected") {
		players.pop_back();
	}
	if (command == "Down") {
		players.at(1)->move(0, 4, DOWN_A);
	}
	if (command == "Left") {
		players.at(1)->move(-4, 0, LEFT_A);
	}
	if (command == "Right") {
		players.at(1)->move(4, 0, RIGHT_A);
	}
	if (command == "Up") {
		players.at(1)->move(0, -4, UP_A);
	}
}


void movements(std::vector<std::shared_ptr<Player>> &players, switches S, SOCKET &sock) {
	switch (S) {
	case LEFT: {
		players.at(0)->move(-4, 0, LEFT_A);
		SendBytes(sock, LEFT);
		break;
		}
	case RIGHT: {
		players.at(0)->move(4, 0, RIGHT_A);
		SendBytes(sock, RIGHT);
		break;
		}
	case DOWN: {
		players.at(0)->move(0, 4, DOWN_A);
		SendBytes(sock, DOWN);
		break;
		}
	case UP: {
		players.at(0)->move(0, -4, UP_A);
		SendBytes(sock, UP);
		break;
		}
	}
}

void Game_menu(sf::RenderWindow &window, bool &Game_Start, sf::Event &evnt, GameInterface &Menu) {
	if (Game_Start != true) {
		for (;;) {
			window.pollEvent(evnt);
			if (evnt.type == evnt.Closed) {
				window.close();
			}
			if (GetAsyncKeyState(VK_UP)) {
				Menu.move_up();
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				Menu.move_down();
			}
			if (GetAsyncKeyState(VK_RETURN)) {
				if (Menu.animation.getIterator() == 0) {
					Game_Start = true;
					break;
				}
				if (Menu.animation.getIterator() == 2) {
					window.close();
				}
			}
			window.clear();
			window.draw(Menu.sprite);
			window.display();
			Sleep(200);
		}
	}
}