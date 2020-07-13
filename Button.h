#pragma once

#include <SFML\Graphics.hpp>

using namespace std;

using namespace sf;

class Button
{
private:
	Vector2f pos;
	Vector2f size;
	string str;

	int clickCooldown;

public:
	Button();

	~Button();

	void setPos(Vector2f m_pos);

	void setSize(Vector2f m_size);

	void setString(string m_str);

	bool checkIfClicked(Vector2i mouse);

	void draw(RenderTarget* target, Font* font);
};

