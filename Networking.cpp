#include <iostream>
#include <SFML\Graphics.hpp>
#include <string>
#include <conio.h>
#include <thread>
#include <time.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>




enum switches {
	LEFT, RIGHT, UP, DOWN
};

#pragma comment(lib, "ws2_32.lib")


struct animation_right {
	int iterator{ 0 };
	int iterator2{ 0 };
	int iterator3{ 0 };
	int iterator4{ 0 };
	void move_down(sf::Sprite &sprite) {
		iterator2 = 0;
		iterator3 = 0;
		iterator4 = 0;
		if (iterator > 3) {
			iterator = 0;
		}
		if (iterator == 0) {
			sprite.setTextureRect(sf::IntRect(0, 0, 30, 43));
		}
		if (iterator == 1) {
			sprite.setTextureRect(sf::IntRect(32, 0, 30, 43));
		}
		if (iterator == 2) {
			sprite.setTextureRect(sf::IntRect(64, 0, 30, 43));
		}
		if (iterator == 3) {
			sprite.setTextureRect(sf::IntRect(96, 0, 30, 43));
		}
		++iterator;
	}
	void move_left(sf::Sprite &sprite) {
		iterator = 0;
		iterator3 = 0;
		iterator4 = 0;
		if (iterator2 > 3) {
			iterator2 = 0;
		}
		if (iterator2 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 49, 30, 43));
		}
		if (iterator2 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 49, 30, 43));
		}
		if (iterator2 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 49, 30, 43));
		}
		if (iterator2 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 49, 30, 43));
		}
		++iterator2;
	}

	void move_right(sf::Sprite &sprite) {
		iterator = 0;
		iterator2 = 0;
		iterator4 = 0;
		if (iterator3 > 3) {
			iterator3 = 0;
		}
		if (iterator3 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 98, 30, 45));
		}
		if (iterator3 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 98, 30, 45));
		}
		if (iterator3 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 98, 30, 45));
		}
		if (iterator3 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 98, 30, 45));
		}
		++iterator3;
	}

	void move_up(sf::Sprite &sprite) {
		iterator = 0;
		iterator2 = 0;
		iterator3 = 0;
		if (iterator4 > 3) {
			iterator4 = 0;
		}
		if (iterator4 == 0) {
			sprite.setTextureRect(sf::IntRect(0, 147, 30, 45));
		}
		if (iterator4 == 1) {
			sprite.setTextureRect(sf::IntRect(32, 147, 30, 45));
		}
		if (iterator4 == 2) {
			sprite.setTextureRect(sf::IntRect(64, 147, 30, 45));
		}
		if (iterator4 == 3) {
			sprite.setTextureRect(sf::IntRect(96, 147, 30, 45));
		}
		++iterator4;
	}
};

void npc_movement(sf::Sprite &sprite, animation_right &animation) {
	int random = rand() % 100 + 1;
	if (random == 1) {
		sprite.move(sf::Vector2f(-4, 0));
		animation.move_left(sprite);
		animation.move_left(sprite);
	}
	if (random == 2) {
		sprite.move(sf::Vector2f(4, 0));
		animation.move_right(sprite);
		animation.move_right(sprite);
	}
	if (random == 3) {
		sprite.move(sf::Vector2f(0, 4));
		animation.move_down(sprite);
		animation.move_down(sprite);
	}
	if (random == 4) {
		sprite.move(sf::Vector2f(0, -4));
		animation.move_up(sprite);
		animation.move_up(sprite);
	}
}



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



void game_start(SOCKET &sock) {
	srand(unsigned(NULL));
	sf::RenderWindow window(sf::VideoMode(595, 595), "Game Learn", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);


	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/Character3.png")) {
		std::cout << "Load Failed" << std::endl;
		system("pause");
	}
	sf::Texture texture2;
	if (!texture2.loadFromFile("Sprites/Character2.png")) {
		std::cout << "Load Failed" << std::endl;
		system("pause");
	}

	sf::Texture map1;
	if (!map1.loadFromFile("Maps/Forest.png")) {
		std::cout << "Load Failed" << std::endl;
		system("pause");
	}
	///////////////////////////
	sf::Sprite map;
	map.setTexture(map1);
	///////////////////////////////////
	sf::Sprite sprite;
	sprite.setTexture(texture);
	///////////////////////////////////
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);

	std::vector<sf::Sprite> sprites;
	sprites.push_back(map);
	sprites.push_back(sprite);
	sprites.push_back(sprite2);

	sprite2.move(sf::Vector2f(50, 40));

	animation_right animation1;
	sprites.at(1).setTextureRect(sf::IntRect(0, 0, 30, 43));
	sprites.at(2).setTextureRect(sf::IntRect(0, 0, 30, 43));

	int x{ 0 }, y{ 0 };

	while (window.isOpen()) {
		sf::Event evnt;
		char buf[4096];
		//npc_movement(sprites.at(2), animation1);
		while (window.pollEvent(evnt)) {

			if (evnt.type == evnt.Closed) {
				window.close();
			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				if (x >= 0) {
					x -= 4;
					std::cout << "CORD: X:" << x << " Y:" << y << std::endl;
					sprites.at(1).move(sf::Vector2f(-4, 0));
					SendBytes(sock, LEFT);
				}
				animation1.move_left(sprites.at(1));
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				if (x <= 564) {
					x += 4;
					std::cout << "CORD: X:" << x << " Y:" << y << std::endl;
					sprites.at(1).move(sf::Vector2f(4, 0));
					SendBytes(sock, RIGHT);
				}
				animation1.move_right(sprites.at(1));
			}
			else if (GetAsyncKeyState(VK_DOWN)) {
				if (y <= 552) {
					y += 4;
					std::cout << "CORD: X:" << x << " Y:" << y << std::endl;
					sprites.at(1).move(sf::Vector2f(0, 4));
					SendBytes(sock, DOWN);
				}
				animation1.move_down(sprites.at(1));
			}
			else if (GetAsyncKeyState(VK_UP)) {
				if (y >= 0) {
					y -= 4;
					std::cout << "CORD: X:" << x << " Y:" << y << std::endl;
					sprites.at(1).move(sf::Vector2f(0, -4));
					SendBytes(sock, UP);
				}
				animation1.move_up(sprites.at(1));
			}

		}


		window.clear();
		for (auto &sprite : sprites) {
			window.draw(sprite);
		}


		window.display();
		int bytesRecieved = recv(sock, buf, 4096, NULL);
		Sleep(50);
	}
}

int main() {
	std::string ipAddress = "127.0.0.1";
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		std::cerr << "Error while Initializing" << std::endl;
	}
//Create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Error while Creating a Socket" << std::endl;
	}
//Fill in hint
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(5400);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
//Connect to the server
	int connectResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectResult != SOCKET_ERROR) {
		std::thread sendm(game_start, std::ref(sock));
		sendm.detach();
		while (true) {
			char buf[4096];
			int bytesRecieved = recv(sock, buf, 4096, NULL);
			if (bytesRecieved > 0) {
			}
		}
	}



	system("pause");
	return 0;
}