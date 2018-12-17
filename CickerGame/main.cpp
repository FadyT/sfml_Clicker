#include<stdio.h>
#include<string>
#include<iostream>
#include <SFML\Graphics.hpp>
#include <time.h>
#include <ctime>

using namespace std;

#define WIDTH 920
#define HEIGHT 500
#define RED 0
#define GREEN 1
#define BLUE 2
#define scoreChange 10

#define nextWaveTime 5000

//----------------------------------------------------------------
// player class //

class Player
{
	
	
	// player shape 
	sf::CircleShape circle;
	// player color
	int color ;
	int score ;
	sf::Vector2i playerPosition;
	bool GameOver = false ;
	int bestScore =0 ;


public:

	Player()
	{
		score = 0;
		color = 0;
		circle = sf::CircleShape(10, 10);
		circle.setFillColor(sf::Color(255, 255, 0, 255));
		circle.setOrigin(5, 5);
	}

	sf::CircleShape CreatePlayer(sf::RenderWindow window)
	{
		//my shapes
		window.draw(circle);
		return circle;
	}

	void MovePlayer(int x, int y)
	{
		playerPosition.x = x;
		playerPosition.y = y;

		circle.setPosition(x, y);
	}

	void Attack()
	{
		color = rand() % 3;
		
		switch (color)
		{
		case RED:
			circle.setFillColor(sf::Color::Red);
			break;
		case GREEN:
			circle.setFillColor(sf::Color::Green);
			break;
		case BLUE:
			circle.setFillColor(sf::Color::Blue);
			break;
		}
	}

	sf::CircleShape GetPlayer()
	{
		return circle;
	}

	int GetColor()
	{
		return color;
	}

	sf::Vector2i GetPlayerPosition()
	{
		return playerPosition;
	}

	string GetScore()
	{
		std::string s = std::to_string(score);
		return s;
	}

	void IncreaseScore(int n)
	{
		score = score + n;
	}

	void DecreaseScore(int n)
	{
		if (bestScore < score)
		{
			bestScore = score;
		}

		score = score - n;
		if (score <= 0) {
			GameOver = true;
		}
	}

	bool GetGameOverState()
	{
		return GameOver;
	}

	string GetBestScore()
	{
		std::string s = std::to_string(bestScore);

		return s;
	}
	void SetGameOverState(bool state)
	{
		GameOver = state;
	}

};


//----------------------------------------------------------------
// enemy class 
class Enemy {
	sf::RectangleShape rectangle;
	int enemyColor;
	sf::Vector2f position;
	float speed;
	int lives;
	bool hasMoreLives = true;


public:
	Enemy()
	{
	
		lives = 5;
		speed = 0.25;
		position.x = rand() % (WIDTH - 50  );
		position.y = rand() % (HEIGHT - 50 );

		// define a 120x50 rectangle
		rectangle = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
		rectangle.setPosition(position.x , position.y);
		rectangle.setFillColor(sf::Color::Green);
	}
	
	sf::RectangleShape GetRectangle()
	{
		return rectangle;
	}

	void Destroy()
	{
		enemyColor = rand() % 3;
		position.x =  rand() % (HEIGHT - 50);
		position.y = 0;

		switch (enemyColor)
		{
		case RED:
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(position.x, position.y);
			break;
		case GREEN:
			rectangle.setFillColor(sf::Color::Green);
			rectangle.setPosition(position.x, position.y);
			break;
		case BLUE:
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(position.x, position.y);
			break;

		}
	}

	void UpdatePosition()
	{
		position.y = position.y + speed + 0.01;
		rectangle.setPosition(position.x, position.y);

		if (position.y > HEIGHT)
		{
			DecreaseLives();
			position.x = rand() % (WIDTH - 50);
			position.y = 0;
		}
	}

	sf::Vector2f GetEnemyPosition()
	{
		return position;
	}

	int GetEnemyColor()
	{
		return enemyColor;
	}

	void IncreaseSpeed()
	{
		speed = speed + 0.01;
	}

	void DecreaseLives()
	{
		lives = lives - 1;
		if (lives <= 0)
		{
			hasMoreLives = false;
		}
	}

	string GetLives()
	{
		std::string s = std::to_string(lives);
		return s;
	}

	bool GetHasMoreLives()
	{
		return hasMoreLives;
	}

};
//----------------------------------------------------------------

/*
void delay(int time) {
	sf::Time z;
	auto x = z.asMilliseconds();
	while (x-- > 0);
}
*/

void main() {

	//init window
	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Grapher");

	//data variable
	sf::Event e;
	sf::Vector2i cPos;//mouse pos

	Player player;
	


	sf::Text text;
	sf::Text lives;
	sf::Font font;

	if (font.loadFromFile("D:/iti/Metal Ink.ttf"))
		cout << "text loaded ";

	text.setFont(font);
	text.setString("Score : 0");
	text.setCharacterSize(32); // in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(WIDTH / 2, 10);


	lives.setFont(font);
	lives.setString("lives : 0");
	lives.setCharacterSize(32); // in pixels, not points!
	lives.setFillColor(sf::Color::White);
	lives.setStyle(sf::Text::Bold);
	lives.setPosition(25, 25);


	Enemy enemy1;
	//Enemy enemy2;
	//Enemy enemy3;

	int differenceX;
	int differenceY;

	while (window.isOpen())
	{

		for (int i = nextWaveTime; i > 0; i--)
		{
			window.clear();

			cPos = sf::Mouse::getPosition(window);

			int  playerColor = player.GetColor();
			int  enemyColor = enemy1.GetEnemyColor();

			//handle event "input"
			while (window.pollEvent(e)) {
				lives.setString(enemy1.GetLives());

				switch (e.type)
				{
				case sf::Event::MouseButtonPressed:

					differenceX = player.GetPlayerPosition().x - enemy1.GetEnemyPosition().x;
					differenceY = player.GetPlayerPosition().y - enemy1.GetEnemyPosition().y;


					playerColor = player.GetColor();

					player.Attack();

					if (differenceX < 50 && differenceX > 0 && differenceY < 50 && differenceY > 0)
					{

						cout << player.GetColor();
						cout << "  ,  ";
						cout << enemy1.GetEnemyColor();
						cout << "      ";

						enemy1.Destroy();
						if (playerColor == enemyColor)
						{
							player.IncreaseScore(scoreChange);
						}
						else
						{
							player.DecreaseScore(scoreChange);
						}

						cout << player.GetColor();
						cout << "  ,  ";
						cout << enemy1.GetEnemyColor();
						cout << "      ";

						text.setString(player.GetScore());


					}

					break;

				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
				}//switch
			}

			player.MovePlayer(cPos.x, cPos.y);
			sf::CircleShape c = player.GetPlayer();
			sf::RectangleShape r1 = enemy1.GetRectangle();
			//sf::RectangleShape r2 = enemy2.GetRectangle();
			//sf::RectangleShape r3 = enemy3.GetRectangle();

			enemy1.UpdatePosition();
			window.draw(r1);
			//window.draw(r2);
			//window.draw(r3);
			window.draw(text);
			window.draw(lives);

			window.draw(c);

			if (!enemy1.GetHasMoreLives())
			{
				player.SetGameOverState(true);
			}


			//player.draw(window);
			// inside the main loop, between window.clear() and window.display()
			window.display();
			
			while (	player.GetGameOverState())
			{
				sf::Text gameOverText;
				sf::Font font;

				if (font.loadFromFile("D:/iti/Metal Ink.ttf"))
					cout << "text loaded ";

				gameOverText.setFont(font);
				// set the string to display
				string s = "Game Over ! \ n your Score is ";
				gameOverText.setString(player.GetBestScore());
				// set the character size
				gameOverText.setCharacterSize(32); // in pixels, not points!
				// set the color
				gameOverText.setFillColor(sf::Color::White);
				// set the text style
				gameOverText.setStyle(sf::Text::Bold);
				gameOverText.setPosition(WIDTH / 2, HEIGHT/2);


				sf::RectangleShape rec(sf::Vector2f(WIDTH, HEIGHT));
				rec.setFillColor(sf::Color::Blue);
				window.draw(rec);
				window.draw(gameOverText);
				window.display();

			}

		}
		enemy1.IncreaseSpeed();
	}
}

//----------------------------------------------------------------
// abanoub hani //