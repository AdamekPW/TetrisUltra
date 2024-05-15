#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <sstream>

#include "Board.h"
#include "Shapes.h"
#include "MyMusic.h"
#include "Menu.h"


#define SPEED 50

using namespace std;

void PrintMatrix(vector<vector<int>>& Matrix) {
	for (int i = 0; i < Matrix.size(); i++) {
		for (int j = 0; j < Matrix[i].size(); j++) {
			cout << Matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void GetKeyboardData(sf::RenderWindow& window, Board& Plansza, Shapes* (&Shape), Shapes* (&NextShape)) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down)
				Plansza.IsFit(Shape, 1, 0);

			if (event.key.code == sf::Keyboard::Left)
				Plansza.IsFit(Shape, 0, -1);

			if (event.key.code == sf::Keyboard::Right)
				Plansza.IsFit(Shape, 0, 1);

			if (event.key.code == sf::Keyboard::D)
				if (Plansza.IsRightRotationFit(Shape)) {}

			if (event.key.code == sf::Keyboard::A)
				if (Plansza.IsLeftRotationFit(Shape)) {}

			if (event.key.code == sf::Keyboard::W) {
				// Block change size

				if (Shape->GetId() == 2) {
					(Shape->PowerLevel)--;
					Plansza.RemoveShape(Shape);
					Shape->SuperPower(Plansza);
					if (!Plansza.IsThatFit(Shape)) {
						(Shape->PowerLevel)++;
						Shape->SuperPower(Plansza);
					}
					Plansza.DrawShape(Shape);
				}
				// TBlock shoot
				else if (Shape->GetId() == 3) {
					Shape->SuperPower(Plansza);
				}
				// JBlock shape change
				else if (Shape->GetId() == 4) {
					Shape->SuperPower(Plansza);
				}
				// LBlock anti solid shape 
				else if (Shape->GetId() == 5) {
					Shape->SuperPower(Plansza);
				}
				// Line shoot
				else if (Shape->GetId() == 8) {
					Shape->SuperPower(Plansza);
				}
				// ZBlock tnt
				else if (Shape->GetId() == 7) {

					Shape->SuperPower(Plansza);
					delete Shape;
					Shape = NextShape;

					NextShape = Plansza.RandomShape();

				}
				//Sblock tnt
				else if (Shape->GetId() == 6) {

					Shape->SuperPower(Plansza);
					delete Shape;
					Shape = NextShape;

					NextShape = Plansza.RandomShape();

				}

			}
			if (event.key.code == sf::Keyboard::S) {
				if (Shape->GetId() == 2) {
					(Shape->PowerLevel)++;
					Plansza.RemoveShape(Shape);
					Shape->SuperPower(Plansza);
					if (!Plansza.IsThatFit(Shape)) {
						(Shape->PowerLevel)--;
						Shape->SuperPower(Plansza);
					}
					Plansza.DrawShape(Shape);
				}
			}
		}
	}
}

int Check(Board& Plansza, sf::RenderWindow& window) {
	int w = (int)((float)Plansza.GetSqSize() * 0.9);
	int Mnoznik = 0;
	for (int i = 0; i < Plansza.GetHeight(); i++) {
		int LicznikLini = 0;
		for (int j = 0; j < Plansza.GetWidth(); j++) {
			if (Plansza.BoardInfo[i][j] != 0) LicznikLini++;
		}
		if (LicznikLini == Plansza.GetWidth()) {
			sf::RectangleShape square(sf::Vector2f(w, w));
			square.setFillColor(sf::Color::Black);
			for (int indeks = 0; indeks < Plansza.GetWidth(); indeks++) {
				unsigned int x = i * Plansza.GetSqSize();
				unsigned int y = indeks * Plansza.GetSqSize();
				square.setPosition(y, x);
				window.draw(square);
				Plansza.BoardInfo[i][indeks] = 0;

			}
			Plansza.MoveLevels(i);
			Mnoznik++;
		}
	}

	if (Mnoznik == 1) return 90;
	if (Mnoznik == 2) return 200;
	if (Mnoznik == 3) return 400;
	if (Mnoznik == 4) return 800;
	return 0;
}

sf::Color RandomColor() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 255);
	int Red = distribution(generator);
	int Green = distribution(generator);
	int Blue = distribution(generator);
	sf::Color Kolor(Red, Green, Blue);
	return Kolor;
}


int main()
{



	unsigned int Punkty = 0;
	bool ShowShadowContest = false;
	sf::Color Orange(255, 165, 0);
	sf::Color Pink(255, 105, 180);

	sf::Text Pkt;
	sf::Font font;
	font.loadFromFile("ARIAL.ttf");
	Pkt.setFont(font);
	Pkt.setFillColor(sf::Color::White);
	Pkt.setCharacterSize(40);
	sf::Text ScoreText;
	ScoreText.setFont(font);
	ScoreText.setFillColor(sf::Color::Green);
	ScoreText.setCharacterSize(40);
	ScoreText.setString("Score:");

	sf::Texture PlayAgainImage;
	if (!PlayAgainImage.loadFromFile("MenuImages/PlayAgainButton.png")) {}
	sf::Sprite PlayAgain;
	PlayAgain.setTexture(PlayAgainImage);
	

	Board Plansza;
	Plansza.SetWidth(13);
	Plansza.SetHeight(21);
	Shapes* Shape = Plansza.RandomShape();
	Shapes* NextShape = Plansza.RandomShape();


	Plansza.DrawShape(Shape);



	//Up bar config ------------------------------------------------------
	unsigned int X_Up_Board = 160;
	unsigned int Y_Board = Plansza.GetWidth() * Plansza.GetSqSize();

	sf::Texture Image;
	if (!Image.loadFromFile("tetris-logo.png")) { //cout << "Loading Error";
	}
	sf::Sprite Sprite;
	Sprite.setTexture(Image);


	std::vector<sf::Color> ColorsUp;
	for (int i = 0; i < Plansza.GetWidth(); i++) {
		sf::Color NewColor = RandomColor();
		ColorsUp.push_back(NewColor);
	}

	//Down bar config ----------------------------------------------------
	unsigned int X_Down_Board = 160;
	std::vector<sf::Color> ColorsDown;
	for (int i = 0; i < Plansza.GetWidth(); i++) {
		sf::Color NewColor = sf::Color::Green;
		ColorsDown.push_back(NewColor);
	}
	//Squares config ------------------------------------------------------
	int w = (int)Plansza.GetSqSize() * 0.9f;
	float CornerOffSet = 0.05f;
	sf::RectangleShape square(sf::Vector2f(w, w));

	sf::RectangleShape AntiSquare(sf::Vector2f(w, w));
	sf::RectangleShape TopAntiSquare(sf::Vector2f(0.7f * Plansza.GetSqSize(), 0.7f * Plansza.GetSqSize()));
	AntiSquare.setFillColor(sf::Color::White);
	TopAntiSquare.setFillColor(sf::Color::Black);

	//Window config -------------------------------------------------------
	const int W_X = Plansza.GetWidth() * Plansza.GetSqSize();
	const int W_Y = Plansza.GetHeight() * Plansza.GetSqSize() + X_Up_Board + X_Down_Board;
	sf::RenderWindow window(sf::VideoMode(W_X,W_Y), "Tetris");




	int GameOrMenu = 0;
	MyMusic MyMusic;


	sf::RectangleShape button(sf::Vector2f(200, 130)); // Rozmiar przycisku
	button.setFillColor(sf::Color::White); // Kolor przycisku
	button.setPosition(0, 250); // Pozycja przycisku
	while (window.isOpen()) {
		if (GameOrMenu == 0) {
			Menu Menu;
			Menu.MenuLoop(&GameOrMenu, window);
			ShowShadowContest = Menu.ShowShadowContest;
			MyMusic.SetVolume(Menu.Volume);
		}
		else if (GameOrMenu == 1) {
			MyMusic.PlayNextSong();
			GameOrMenu = 2;
		}
		else if (GameOrMenu == 2) {



			GetKeyboardData(window, Plansza, Shape, NextShape);

			window.clear();
			window.draw(Sprite);

			//Up Bar loop -------------------------------------
			int x_line = X_Up_Board - Plansza.GetSqSize();
			for (int i = 0; i < Plansza.GetWidth(); i++) {
				square.setPosition((i + CornerOffSet) * Plansza.GetSqSize(),
					CornerOffSet * Plansza.GetSqSize() + x_line);
				square.setFillColor(ColorsUp[i]);
				window.draw(square);
			}


			//Down Bar loop -----------------------------------
			x_line = Plansza.GetSqSize() * Plansza.GetHeight() + X_Up_Board;
			for (int i = 0; i < Plansza.GetWidth(); i++) {
				square.setPosition(i * Plansza.GetSqSize() + CornerOffSet * Plansza.GetSqSize(),
					x_line + CornerOffSet * Plansza.GetSqSize());
				square.setFillColor(ColorsDown[i]);
				window.draw(square);
			}
	
			std::stringstream ss;
			ss << Punkty;
			std::string PunktyStr = ss.str();
			Pkt.setString(PunktyStr);
			Pkt.setPosition(0, x_line + Plansza.GetSqSize());
			window.draw(Pkt);

			int id = NextShape->GetId();
			if (id == 2) square.setFillColor(sf::Color::Yellow);
			if (id == 3) square.setFillColor(sf::Color::Magenta);
			if (id == 4) square.setFillColor(Pink);
			if (id == 5) square.setFillColor(Orange);
			if (id == 6) square.setFillColor(sf::Color::Red);
			if (id == 7) square.setFillColor(sf::Color::Green);
			if (id == 8) square.setFillColor(sf::Color::Cyan);
			for (int i = 0; i < NextShape->Points.size(); i++) {
				int Px = NextShape->Points[i][0];
				int Py = NextShape->Points[i][1];
				square.setPosition((9 + Py + CornerOffSet) * Plansza.GetSqSize(),
					x_line + (Px + 2 + CornerOffSet) * Plansza.GetSqSize());
				window.draw(square);
			}

			//Game loop ---------------------------------------
			Plansza.UpdateBullets();
			if (ShowShadowContest) Shape->ShowContest(Plansza);

			for (int i = 0; i < Plansza.BoardInfo.size(); i++) {

				for (int j = 0; j < Plansza.BoardInfo[i].size(); j++) {
					if (Plansza.BoardInfo[i][j] != 0) {
						int id = Plansza.BoardInfo[i][j];
						unsigned int x = i * Plansza.GetSqSize();
						unsigned int y = j * Plansza.GetSqSize();

						if (id == 2) square.setFillColor(sf::Color::Yellow);
						else if (id == 3) square.setFillColor(sf::Color::Magenta);
						else if (id == 4) square.setFillColor(Pink);
						else if (id == 5) square.setFillColor(Orange);
						else if (id == 6) square.setFillColor(sf::Color::Red);
						else if (id == 7) square.setFillColor(sf::Color::Green);
						else if (id == 8) square.setFillColor(sf::Color::Cyan);
						else if (id < 0) {

							AntiSquare.setPosition(y + CornerOffSet * Plansza.GetSqSize(),
								x + X_Up_Board + CornerOffSet * Plansza.GetSqSize());
							window.draw(AntiSquare);
							Plansza.BoardInfo[i][j] = 0;

							TopAntiSquare.setPosition(y + 0.15f * Plansza.GetSqSize(),
								x + X_Up_Board + 0.15f * Plansza.GetSqSize());
							window.draw(TopAntiSquare);
						}
						if (id > 0) {
							square.setPosition(y + CornerOffSet * Plansza.GetSqSize(),
								x + X_Up_Board + CornerOffSet * Plansza.GetSqSize());
							window.draw(square);
						}



					}
				}

			}


			if (!Plansza.IsFit(Shape, 1, 0) && Plansza.Bullets.size() == 0) {

				delete Shape;
				Shape = NextShape;
				NextShape = Plansza.RandomShape();
				//NextShape = new LBlock;
				Punkty += Check(Plansza, window);

				for (int i = 0; i < Shape->Points.size(); i++) {
					int x = Shape->GetX() + Shape->Points[i][0];
					int y = Shape->GetY() + Shape->Points[i][1];
					if (Plansza.BoardInfo[x][y] != 0) {
						delete Shape;
						delete NextShape;
						GameOrMenu = 3;
						//cout << "You lost | Score: " << Punkty << "\n";
						//return 0;
					}
				}
			}





			window.display();
			if (Shape->GetId() == 3 || Shape->GetId() == 8) Plansza.UpdateBullets();

			sf::sleep(sf::milliseconds(SPEED));
			GetKeyboardData(window, Plansza, Shape, NextShape);
			sf::sleep(sf::milliseconds(SPEED));
			GetKeyboardData(window, Plansza, Shape, NextShape);
			sf::sleep(sf::milliseconds(SPEED));


			MyMusic.IsSongFinished();
		}


		else if (GameOrMenu == 3) {
			sf::Event event;

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::FloatRect PlayAgainButton = PlayAgain.getGlobalBounds();
					if (PlayAgainButton.contains(static_cast<sf::Vector2f>(mousePosition)))
					{
						GameOrMenu = 2;
						for (int i = 0; i < Plansza.BoardInfo.size(); i++) {
							for (int j = 0; j < Plansza.BoardInfo[i].size(); j++) {
								Plansza.BoardInfo[i][j] = 0;
							}
						}
						Shape = Plansza.RandomShape();
						NextShape = Plansza.RandomShape();
						Plansza.DrawShape(Shape);
						Punkty = 0;
					}
				}
			}
			window.clear();
			Pkt.setPosition(window.getSize().x / 2-Pkt.getGlobalBounds().width/2, window.getSize().y / 2);
			ScoreText.setPosition(window.getSize().x / 2-ScoreText.getGlobalBounds().width/2, window.getSize().y / 2 - 50);
			PlayAgain.setPosition(window.getSize().x / 2-PlayAgain.getGlobalBounds().width/2, window.getSize().y / 2 + 100);
			window.draw(Pkt);
			window.draw(ScoreText);
			window.draw(PlayAgain);
			window.display();
		}

	}



	return 0;
}
