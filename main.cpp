#include "Board.h"
#include "Button.h"

#include <iostream>

int main()
{
	srand(unsigned(time(NULL)));

	Font font;
	if(!font.loadFromFile("arial.ttf")) {};

	Texture tex;
	if(!tex.loadFromFile("bomb_flag.png")) {};

	bool lmbPressed{ 0 }, rmbPressed{ 0 };

	bool isBoard{ 0 };
	bool dead{ 0 };

	Board board;
	board.setPos(Vector2f(100, 100));
	board.create();

	Button startButton;
	startButton.setPos(Vector2f(240, 20));
	startButton.setSize(Vector2f(120, 40));
	startButton.setString("START");

	Text timeText;
	timeText.setPosition(Vector2f(400, 20));
	timeText.setCharacterSize(30);
	timeText.setFillColor(Color::Black);
	timeText.setFont(font);

	Text flagText;
	flagText.setPosition(Vector2f(160, 20));
	flagText.setCharacterSize(30);
	flagText.setFillColor(Color::Black);
	flagText.setFont(font);

	Clock clock;
	int minutes{ 0 };

	RenderWindow window(VideoMode(600, 600), "Saper");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
					lmbPressed = true;

				if (event.mouseButton.button == Mouse::Right)
					rmbPressed = true;
			}
		}

		Vector2i mouse(Mouse::getPosition(window));

		Field* fieldPtr = board.getFieldPointer(mouse);

		if (lmbPressed)
		{
			if (startButton.checkIfClicked(mouse))
			{
				board.clear();
				board.create();
				isBoard = false;
				dead = false;
				clock.restart();
				minutes = 0;
			}

			if (fieldPtr != nullptr && !dead)
			{
				if (isBoard)
				{
					board.floodReveal(board.getIndex(fieldPtr));
					if (fieldPtr->checkIfBomb())
					{
						dead = true;
						board.revealBombs();
						cout << "BOOM!" << endl;
					}
				}
				else
				{
					board.fill(Mouse::getPosition(window));
					board.floodReveal(board.getIndex(fieldPtr));
					isBoard = true;
				}
			}

			lmbPressed = false;
		}

		if (rmbPressed)
		{
			if (isBoard && fieldPtr != nullptr && !dead)
				fieldPtr->setFlag();

			rmbPressed = false;
		}

		if (!dead)
		{
			int seconds = (int)clock.getElapsedTime().asSeconds();
			if (seconds >= 60)
			{
				clock.restart();
				minutes++;
				seconds = 0;
			}
			string timeStr = to_string(minutes) + ":";
			if (seconds < 10)
				timeStr += "0";
			timeStr += to_string(seconds);
			timeText.setString(timeStr);

			int flagCount = board.getFlagCount();
			int bombCount = board.getBombCount();
			flagText.setString(to_string(bombCount - flagCount));

			if (board.checkIfWin())
			{
				cout << "WIN!" << endl;
				dead = true;
			}
		}

		window.clear(Color::White);

		board.draw(&window, &font, &tex);
		startButton.draw(&window, &font);

		window.draw(timeText);
		window.draw(flagText);

		window.display();
	}
	return 0;
}