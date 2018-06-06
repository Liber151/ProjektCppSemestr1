#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <C:\Projects\Project1\Keyboard.hpp>
#include <fstream>
using namespace std;

int main()
{
	ifstream plik;//read
	plik.open("wyniki.txt");
	string pliktymaczasowy;
	string temp;

	cout << pliktymaczasowy;
	int predkoscgracza = 7;
	int width = 1100;
	int height = 900;
	int globalx = 0;
	int globaly = 0;
	int plikzapisany = 0;
	int z=0;
	int y=0;
	string temp2;
	int tempx=803;
	int tempy=0;
	int playerflag = 1;
	int predkosc = 48;
	int predkoscstrzalu = 400;
	int wielkosctile = 50;
	int ilosc = 20;
	int a = 0;
	int b = 0;
	int click = 0;
	float predkoscpociskux=0;
	float predkoscpociskuy=0;
	/////////////////////////////////////////////////////////////////////
	sf::RenderWindow window(sf::VideoMode(width, height), "Gierka");
	vector<sf::RectangleShape> tile(ilosc*ilosc);
	vector<sf::RectangleShape> pociski(1);
	vector<sf::RectangleShape> przeciwnicy(1);
	vector<sf::Texture> ds(74);
	vector<sf::Vector2f> wlasciwoscipociskow(1);
	vector<sf::Vector2f> wlasciwosciprzeciwnikow(1);
	sf::Texture player;
	sf::RectangleShape gracz;
	sf::RectangleShape pocisk;
	pocisk.setPosition(100000, 10000000);
	sf::Texture enemy;
	sf::Texture arena;
	sf::Texture lit;
	sf::Texture end;
	sf::Text czas;
	sf::Text tabela;
	sf::Font font;
	sf::Texture tlo;
	tlo.loadFromFile("C:/Projects/tlo.png");
	font.loadFromFile("C:/Projects/arial.ttf");
	czas.setFont(font);
	czas.setCharacterSize(54);
	czas.setString("0.000");
	czas.setOrigin(floor(czas.getLocalBounds().width/2),floor(czas.getLocalBounds().height/2));
	czas.setPosition(sf::Vector2f(width / 2, 20));
	tabela.setFont(font);
	tabela.setCharacterSize(30);
	tabela.setString("0.000");
	tabela.setOrigin(floor(tabela.getLocalBounds().width / 2), floor(tabela.getLocalBounds().height / 2));
	tabela.setPosition(width / 2, 10);
	sf::RectangleShape telo;
	telo.setSize(sf::Vector2f(width, height));
	telo.setTexture(&tlo);
	end.loadFromFile("C:/Projects/end.png");
	lit.loadFromFile("C:/Projects/lit.png");
	double licznik = 0;
	sf::RectangleShape load;
	sf::Texture loade;
	loade.loadFromFile("C:/Projects/loading.png");
	load.setTexture(&loade);
	load.setSize(sf::Vector2f(width, height));
	while (!plik.eof()) {
		plik >> temp;
		pliktymaczasowy += temp + "\n";
	}
	a = 0;
	window.draw(load);
	window.display();
	for (licznik = 0; licznik <= 73; licznik++) {
		ds[licznik].loadFromFile("C:/Projects/youdied/Dark Souls You Died Green Screen (30fps1080p)"+ to_string(int(licznik))+".jpg");
	}
	//////////////////////////////////////////////////////////////////////
	licznik = 0;
	arena.loadFromFile("C:/Projects/dirt.png");

	player.loadFromFile("C:/Projects/cat.png");

	enemy.loadFromFile("C:/Projects/enemy.png");
	gracz.setSize(sf::Vector2f(50, 50));									//tymczasowe, do posprzatania
	gracz.setOrigin(25, 25);
	gracz.setPosition(width / 2, height / 2);
	gracz.setTexture(&player);
	//////////////////////////////////////////////////////////////////////
	for (a = 0; a < ilosc; a++) {
		for (b = 0; b < ilosc; b++) {
			tile[licznik].setSize(sf::Vector2f(wielkosctile, wielkosctile));
			if (a == 0 || b == 0 || a == ilosc - 1 || b == ilosc - 1) {
				tile[licznik].setTexture(&end);
			}
			else {
				tile[licznik].setTexture(&arena);
			}
			tile[licznik].setPosition((width / 2) - (ilosc*wielkosctile / 2) + b*wielkosctile, height / 2 - ilosc*wielkosctile / 2 + a*wielkosctile);
			licznik++;
		}
	}
	sf::Clock timer;
	sf::Clock spawner;
	sf::Clock cooldown;
	int spawncounter = 0;
	licznik = 0;
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Time spawntime = spawner.getElapsedTime();
		float spawntimer = spawntime.asSeconds();
		if (spawntimer > spawncounter) {
			przeciwnicy.push_back(sf::RectangleShape());//spawn przeciwnikow
			przeciwnicy[spawncounter].setTexture(&enemy);
			przeciwnicy[spawncounter].setSize(sf::Vector2f(100, 100));
			przeciwnicy[spawncounter].setOrigin(50, 50);
			int randy = rand() % 4;
			if (randy == 0) {
				//float randomx = rand() % width * 4 - width * 2;
				float randomy = rand() % height * 4 - width * 2;
				przeciwnicy[spawncounter].setPosition(0, randomy);
				spawncounter++;
			}
			else if (randy == 1) {
				float randomx = rand() % width * 4 - width * 2;
				//float randomy = rand() % height * 4 - width * 2;
				przeciwnicy[spawncounter].setPosition(randomx, 0);
				spawncounter++;
			}
		else if (randy == 2) {
			//float randomx = rand() % width * 4 - width * 2;
			float randomy = rand() % height * 4 - width * 2;
			przeciwnicy[spawncounter].setPosition(width, randomy);
			spawncounter++;
		}
		else if (randy == 3) {
			float randomx = rand() % width * 4 - width * 2;
			//float randomy = rand() % height * 4 - width * 2;
			przeciwnicy[spawncounter].setPosition(randomx, height);
			spawncounter++;
		}

		}
		globalx = 0;
		globaly = 0;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			globaly = predkoscgracza;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { globalx = predkoscgracza; }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { globalx = -predkoscgracza; }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			globalx = predkoscgracza;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			globalx = -predkoscgracza;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			globaly = -predkoscgracza;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Time elapsed = cooldown.getElapsedTime();
			float czasz = elapsed.asSeconds();
			if (czasz>0.1) {
				cooldown.restart();
				click++;
				sf::Vector2i position = sf::Mouse::getPosition(window);
				float xb = position.x;
				float yb = position.y;
				xb -= width / 2;
				yb -= height / 2;
				yb *= (-1);
				float prosta = yb / xb;
				predkoscpociskux = sqrt((predkoscstrzalu ^ 2) / (1 + prosta*prosta));
				predkoscpociskuy = predkoscpociskux*prosta;
				predkoscpociskuy *= (-1);
				if (position.x < width / 2) {
					predkoscpociskux *= (-1);
					predkoscpociskuy *= (-1);
				}
				wlasciwoscipociskow.push_back(sf::Vector2f(predkoscpociskux, predkoscpociskuy));
				wlasciwoscipociskow[click].x = predkoscpociskux;
				wlasciwoscipociskow[click].y = predkoscpociskuy;
				pociski.push_back(sf::RectangleShape());
				pociski[click].setTexture(&lit);
				pociski[click].setSize(sf::Vector2f(30, 30));
				pociski[click].setPosition(width / 2, height / 2);
			}
		}
		window.clear(sf::Color::Black);
		window.draw(telo);
		/*To do list:
		dodatkowi przeciwnicy
		spawn pod
		leaderboard*/
		if (playerflag == 1) {

			licznik = 0;
			pocisk.setPosition(pocisk.getPosition().x + predkoscpociskux+globalx, pocisk.getPosition().y + predkoscpociskuy+globaly);
			for (a = 0; a < (ilosc*ilosc); a++) {
				tile[a].setPosition(tile[a].getPosition().x + globalx, tile[a].getPosition().y + globaly);
				window.draw(tile[a]);
			}
			for (a = 0; a < przeciwnicy.size(); a++) {
				float xa = przeciwnicy[a].getPosition().x - (width / 2);
				float ya = przeciwnicy[a].getPosition().y - (height / 2);
				if (xa == 0) {
					xa = -1;
				}
				ya *= (-1);
				float prosta = ya / xa;
				float przeciwnikx = sqrt((predkosc ^ 2) / (1 + prosta*prosta));
				float przeciwniky = przeciwnikx*prosta;
				przeciwniky *= (-1);
				if (przeciwnicy[a].getPosition().x > width / 2) {
					przeciwnikx *= (-1);
					przeciwniky *= (-1);
				}
				przeciwnicy[a].setPosition(przeciwnicy[a].getPosition().x + przeciwnikx + globalx, przeciwnicy[a].getPosition().y + przeciwniky + globaly);
				window.draw(przeciwnicy[a]);
			}
			window.draw(gracz);
			window.draw(pocisk);
			for (a = 0; a < pociski.size(); a++) {
				pociski[a].setPosition(pociski[a].getPosition().x + wlasciwoscipociskow[a].x + globalx, pociski[a].getPosition().y + wlasciwoscipociskow[a].y + globaly);
				window.draw(pociski[a]);//strzelanie
			}
			//warunki przegranej//////////////////////////////////////////////////////////////
			for (a = 0; a < pociski.size(); a++) {
				for (b = 0; b < przeciwnicy.size();b++) {
					if (przeciwnicy[b].getPosition().x<pociski[a].getPosition().x + 20 && przeciwnicy[b].getPosition().x>pociski[a].getPosition().x - 20 && przeciwnicy[b].getPosition().y<pociski[a].getPosition().y + 20 && przeciwnicy[b].getPosition().y>pociski[a].getPosition().y - 20) {
						int randy = rand() % 4;
						if (randy == 0) {
							//float randomx = rand() % width * 4 - width * 2;
							float randomy = rand() % height * 4 - width * 2;
							przeciwnicy[b].setPosition(0, randomy);
						}
						else if (randy == 1) {
							float randomx = rand() % width * 4 - width * 2;
							//float randomy = rand() % height * 4 - width * 2;
							przeciwnicy[b].setPosition(randomx, 0);
						}
						else if (randy == 2) {
							//float randomx = rand() % width * 4 - width * 2;
							float randomy = rand() % height * 4 - width * 2;
							przeciwnicy[b].setPosition(width, randomy);
						}
						else if (randy == 3) {
							float randomx = rand() % width * 4 - width * 2;
							//float randomy = rand() % height * 4 - width * 2;
							przeciwnicy[b].setPosition(randomx, height);
						}
					}
				}
			}
				if (tile[ilosc-1].getPosition().x<width/2-1.1*wielkosctile || tile[0].getPosition().y>height/2+0.5*wielkosctile || tile[ilosc].getPosition().x>width / 2 || tile[ilosc*ilosc-1].getPosition().y<height/2-0.8*wielkosctile){
					playerflag = 0;
				}//odpowiada za spadanie z areny
				for(a=0;a<przeciwnicy.size();a++){
					if (przeciwnicy[a].getPosition().x<(width / 2) + 10 && przeciwnicy[a].getPosition().x>(width / 2) - 10 && przeciwnicy[a].getPosition().y<(height / 2) + 10 && przeciwnicy[a].getPosition().y >(height / 2) - 10) {
						playerflag = 0;
					}
				}//odpowiada za smierc od przeciwnika
			////wynik////
			sf::Time czasik = timer.getElapsedTime();
			float temp = czasik.asSeconds();
			temp2 = to_string(temp);
			temp2 = temp2.substr(0, 5);
			czas.setString(temp2);
			window.draw(czas);
			////////////
		}
		else {
			if (plikzapisany==0) {
				ofstream wyniki;
				wyniki.open("wyniki.txt");
				wyniki << pliktymaczasowy << temp2;
				wyniki.close();
				plikzapisany = 1;
				tabela.setString("Historia Wynikow:\n" + pliktymaczasowy);
			}
			licznik += 0.25;
			if (licznik < 74) {
				sf::RectangleShape youdied;
				youdied.setSize(sf::Vector2f(width, height));
				youdied.setPosition(0, 0);					////koncowa wiadomosc
				youdied.setTexture(&ds[floor(licznik)]);
				window.draw(youdied);
			}
			else {
				window.draw(tabela);
				//window.close();
			}
		}
		window.display();
	}
	return 0;
}