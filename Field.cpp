#include "Field.h"

Field::Field(const Vector2f& size)
	: isRevealed(false), isBomb(false), isFlag(false), value(0), size(size) {}

void Field::restart()
{
	value = 0;
	isRevealed = false;
	isBomb = false;
	isFlag = false;
}

void Field::setPos(const Vector2f& pos)
{
	this->pos = pos;
}

void Field::addValue()
{
	++value;
}

int Field::getValue() const
{
	return value;
}

void Field::reveal()
{
	isFlag = false;
	isRevealed = true;
}

void Field::setFlag()
{
	if (!isRevealed) isFlag = !isFlag;
}

bool Field::getIsFlag() const
{
	return isFlag;
}

bool Field::getIsRevealed() const
{
	return isRevealed;
}

bool Field::getIsClicked(const Vector2i& mouse) const
{
	return (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y);
}

bool Field::getIsBomb() const
{
	return isBomb;
}

void Field::setBomb()
{
	isBomb = true;
}

void Field::draw(RenderTarget& target, const Font& font, const Texture& tex) const
{
	RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setOutlineThickness(-1.0f);
	rect.setOutlineColor(Color::Black);

	if (isFlag && !isRevealed)
	{
		rect.setFillColor(Color(160, 160, 160));
		target.draw(rect);

		RectangleShape flag;
		flag.setPosition(pos);
		flag.setSize(size);

		flag.setTexture(&tex);
		IntRect texRect;
		texRect.left = 40;
		texRect.top = 0;
		texRect.width = (int)size.x;
		texRect.height = (int)size.y;
		flag.setTextureRect(texRect);

		target.draw(flag);
	}
	else if (isRevealed && !isBomb)
	{
		rect.setFillColor(Color(220, 220, 220));
		target.draw(rect);

		Text text;
		text.setPosition(Vector2f(pos.x+14,pos.y+10));
		text.setCharacterSize(16);
		text.setFont(font);

		if (value == 1)
			text.setFillColor(Color::Blue);
		else if (value == 2)
			text.setFillColor(Color::Green);
		else if (value >= 3)
			text.setFillColor(Color::Red);

		text.setString(std::to_string(value));

		if(value != 0)
			target.draw(text);
	}
	else if (isRevealed && isBomb)
	{
		rect.setFillColor(Color(220, 220, 220));
		target.draw(rect);

		RectangleShape bomb;
		bomb.setPosition(pos);
		bomb.setSize(size);

		bomb.setTexture(&tex);
		IntRect texRect;
		texRect.left = 0;
		texRect.top = 0;
		texRect.width = (int)size.x;
		texRect.height = (int)size.y;
		bomb.setTextureRect(texRect);

		target.draw(bomb);
	}
	else
	{
		rect.setFillColor(Color(160, 160, 160));
		target.draw(rect);
	}
}