#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Field
{
	friend class Board;
private:
	Vector2f pos;
	Vector2f size;

	int value;

	bool isRevealed;
	bool isBomb;
	bool isFlag;

private:
	Field(const Vector2f& size);

	void restart();

	void setPos(const Vector2f& pos);

	void addValue();

	void reveal();

	void setFlag();

	void setBomb();

	int getValue() const;

	bool getIsFlag() const;

	bool getIsBomb() const;

	bool getIsRevealed() const;

	bool getIsClicked(const Vector2i& mouse) const;

	void draw(RenderTarget& target, const Font& font, const Texture& tex) const;
};

