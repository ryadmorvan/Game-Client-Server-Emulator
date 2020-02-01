
//Libraries
#include <iostream>
#include <SFML\Graphics.hpp>
#include <string>
#include <thread>
#include <time.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>
#include <memory>
#include <sstream>




//Assessts
#include "Player.h"
#include "Map.h"
#include "Functions.h"
#include "Movements.h"
#include "UI.h"


void SendBytes(SOCKET &sock, switches S);
void npc_movement(sf::Sprite &sprite, animation_right &animation);



#pragma comment(lib, "ws2_32.lib")

bool Game_Start = false;

int main() {
	srand(unsigned(NULL));
	sf::RenderWindow window(sf::VideoMode(595, 595), "Game Learn", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	InitConnection();
	SOCKET sock = CreateSocket();
	std::unique_ptr<Map> map = std::make_unique<Map>("Maps/Forest.png");
	std::unique_ptr<GameInterface> Menu = std::make_unique<GameInterface>("UI/main-menu.png");
	ConnectSocket(sock, "127.0.0.1", 5400);
///////////////////////////////////////////////////////////////Initialzation
	//Player
	while (true) {
		std::vector<std::shared_ptr<Player>> players;
		std::shared_ptr<Player> player = std::make_unique<Player>("Sprites/Character3.png");
		float x{ 0 }, y{ 0 };
		players.push_back(player);
		////////////

		char buf[4096];
		std::string command;
		while (window.isOpen()) {
			sf::Event evnt;
			Game_menu(window, Game_Start, evnt, Menu.get());
			ZeroMemory(buf, 4096);
			int bytesRecieved;
			bytesRecieved = recv(sock, buf, 4096, NULL);
			if (bytesRecieved > 0) {
				command = std::string(buf);
				std::cout << std::string(buf, 0, bytesRecieved) << std::endl;
				bytesCommand(players, command);
			}

			while (window.pollEvent(evnt)) {

				if (evnt.type == evnt.Closed) {
					window.close();
				}

				if (GetAsyncKeyState(VK_LEFT)) {
					movements(players, LEFT, sock);
				}
				else if (GetAsyncKeyState(VK_RIGHT)) {
					movements(players, RIGHT, sock);
				}
				else if (GetAsyncKeyState(VK_DOWN)) {
					movements(players, DOWN, sock);
				}
				else if (GetAsyncKeyState(VK_UP)) {
					movements(players, UP, sock);
				}
			}

			if (GetAsyncKeyState(VK_ESCAPE)) {
				Game_Start = false;
				break;
			}


			window.clear();
			window.draw(map->sprite);
			////////////////////////////////////
			for (auto &player : players) {
				window.draw(player->sprite);
			}
			window.display();
			std::cout << "X[" << players.at(0)->get_x() << "]" << " Y[" << players.at(0)->get_y() << "]" << std::endl;
			Sleep(50);
		}
	}
	system("pause");
	return 0;
}