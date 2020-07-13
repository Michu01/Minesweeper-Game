#include "Button.h"

Button::Button()
{
	pos = { 0,0 };
	size = { 0,0 };
	str = "";
	clickCooldown = 0;
}

Button::~Button()
{

}

void Button::setPos(Vector2f m_pos)
{
	pos = m_pos;
}

void Button::setSize(Vector2f m_size)
{
	size = m_size;
}

void Button::setString(string m_str)
{
	str = m_str;
}

bool Button::checkIfClicked(Vector2i mouse)
{
	if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y)
	{
		clickCooldown = 10;
		return true;
	}
	else return false;
}

void Button::draw(RenderTarget* target, Font* font)
{
	RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(Color::Black);
	if (clickCooldown > 0)
	{
		rect.setFillColor(Color(153, 204, 255));
		clickCooldown--;
	}
	else rect.setFillColor(Color::White);

	target->draw(rect);

	Text text;
	text.setFont(*font);
	text.setPosition(Vector2f(pos.x+10,pos.y));
	text.setCharacterSize(30);
	text.setFillColor(Color::Black);
	text.setString(str);

	target->draw(text);
}
