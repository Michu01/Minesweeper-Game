#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Field
{
private:
	Vector2f pos;
	Vector2f size;

	int value;

	bool isRevealed;
	bool isBomb;
	bool isFlag;

public:
	Field();

	~Field();

	void setPos(Vector2f m_pos);

	void setSize(Vector2f m_size);

	void addValue();

	int getValue();

	void reveal();

	void setFlag();

	bool checkIfFlag();

	bool checkIfRevealed();

	bool checkIfClicked(Vector2i mouse);

	Field* getPointer();

	bool checkIfBomb();

	void setBomb();

	void draw(RenderTarget* target, Font* font, Texture* tex);
};

