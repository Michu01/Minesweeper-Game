#include "Field.h"

Field::Field()
{
	pos = { 0,0 };
	size = { 0,0 };

	value = 0;

	isBomb = false;
	isRevealed = false;
	isFlag = false;
}

Field::~Field()
{

}

void Field::setPos(Vector2f m_pos)
{
	pos = m_pos;
}

void Field::setSize(Vector2f m_size)
{
	size = m_size;
}

void Field::addValue()
{
	value++;
}

int Field::getValue()
{
	return value;
}

void Field::reveal()
{
	isRevealed = true;
}

void Field::setFlag()
{
	isFlag = !isFlag;
}

bool Field::checkIfFlag()
{
	return isFlag;
}

bool Field::checkIfRevealed()
{
	return isRevealed;
}

bool Field::checkIfClicked(Vector2i mouse)
{
	if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y)
		return true;
	else return false;
}

Field* Field::getPointer()
{
	return this;
}

bool Field::checkIfBomb()
{
	return isBomb;
}

void Field::setBomb()
{
	isBomb = true;
}

void Field::draw(RenderTarget* target, Font* font, Texture* tex)
{
	RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setOutlineThickness(-1.0f);
	rect.setOutlineColor(Color::Black);

	if (isFlag && !isRevealed)
	{
		rect.setFillColor(Color(160, 160, 160));
		target->draw(rect);

		RectangleShape flag;
		flag.setPosition(pos);
		flag.setSize(size);

		flag.setTexture(tex);
		IntRect texRect;
		texRect.left = 40;
		texRect.top = 0;
		texRect.width = (int)size.x;
		texRect.height = (int)size.y;
		flag.setTextureRect(texRect);

		target->draw(flag);
	}
	else if (isRevealed && !isBomb)
	{
		rect.setFillColor(Color(220, 220, 220));
		target->draw(rect);

		Text text;
		text.setPosition(Vector2f(pos.x+14,pos.y+10));
		text.setCharacterSize(16);
		text.setFont(*font);

		if (value == 1)
			text.setFillColor(Color::Blue);
		else if (value == 2)
			text.setFillColor(Color::Green);
		else if (value >= 3)
			text.setFillColor(Color::Red);

		text.setString(std::to_string(value));

		if(value != 0)
			target->draw(text);
	}
	else if (isRevealed && isBomb)
	{
		rect.setFillColor(Color(220, 220, 220));
		target->draw(rect);

		RectangleShape bomb;
		bomb.setPosition(pos);
		bomb.setSize(size);

		bomb.setTexture(tex);
		IntRect texRect;
		texRect.left = 0;
		texRect.top = 0;
		texRect.width = (int)size.x;
		texRect.height = (int)size.y;
		bomb.setTextureRect(texRect);

		target->draw(bomb);
	}
	else
	{
		rect.setFillColor(Color(160, 160, 160));
		target->draw(rect);
	}

	
}