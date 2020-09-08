#include "Board.h"
#include "Button.h"
#include "Timer.h"

int main()
{
	Font font;
	if(!font.loadFromFile("arial.ttf")) {};

	Texture tex;
	if(!tex.loadFromFile("bomb_flag.png")) {};

	bool lmbPressed{ 0 }, rmbPressed{ 0 };

	bool dead{ 0 };
	bool win{ 0 };

	Board board(Vector2f(100, 100));

	Button startButton(Vector2f(220, 20), Vector2f(160, 40), "START");

	Text timeText;
	timeText.setPosition(Vector2f(420, 20));
	timeText.setCharacterSize(30);
	timeText.setFillColor(Color::Black);
	timeText.setFont(font);

	Text flagText;
	flagText.setPosition(Vector2f(140, 20));
	flagText.setCharacterSize(30);
	flagText.setFillColor(Color::Black);
	flagText.setFont(font);

	Text endText;
	endText.setPosition(Vector2f(300, 540));
	endText.setCharacterSize(30);
	endText.setFillColor(Color::Black);
	endText.setFont(font);

	Timer timer;

	RenderWindow window(VideoMode(600, 600), "Saper");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case Mouse::Left:
					lmbPressed = true;
					break;
				case Mouse::Right:
					rmbPressed = true;
					break;
				}
				break;
			}
		}

		const Vector2i mouse(Mouse::getPosition(window));

		if (lmbPressed)
		{
			if (startButton.checkIfClicked(mouse))
			{
				board.restart();
				timer.restart();
				endText.setString("");
				dead = false;
				win = false;
			}

			if (!dead) dead = board.clickField(mouse);

			if (dead && !win)
			{
				endText.setString("GAME OVER!");
				FloatRect textRect(endText.getLocalBounds());
				endText.setOrigin(Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
			}

			lmbPressed = false;
		}

		if (rmbPressed)
		{
			if (!dead) board.setFlag(mouse);
			rmbPressed = false;
		}

		if (!dead)
		{
			timer.update();
			timeText.setString(timer.getTimeStr());

			int flagCount{ board.getFlagCount() };
			int bombCount{ board.getBombCount() };

			flagText.setString(to_string(bombCount - flagCount));
			
			if (board.checkIfWin())
			{
				win = true;
				dead = true;
				endText.setString("YOU WIN!");
				FloatRect textRect(endText.getLocalBounds());
				endText.setOrigin(Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
			}
		}

		window.clear(Color::White);

		board.draw(window, font, tex);
		startButton.draw(window,font);

		window.draw(timeText);
		window.draw(flagText);
		window.draw(endText);

		window.display();
	}
	return 0;
}