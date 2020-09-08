#include "Button.h"

Button::Button(const Vector2f& pos, const Vector2f& size, const string& str)
	: pos(pos), size(size), str(str), delay(0.1f) {}

void Button::setString(const string& str)
{
	this->str = str;
}

bool Button::checkIfClicked(const Vector2i& mouse)
{
	if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y)
	{
		clock.restart();
		return true;
	}
	else return false;
}

void Button::draw(RenderTarget& target, const Font& font) const
{
	RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(Color::Black);
	if (clock.getElapsedTime().asSeconds() < delay)
		rect.setFillColor(Color(153, 204, 255));
	else rect.setFillColor(Color::White);
	target.draw(rect);

	Text text;
	text.setFont(font);
	text.setPosition(Vector2f(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f));
	text.setCharacterSize(30);
	text.setFillColor(Color::Black);
	text.setString(str);
	FloatRect textRect(text.getLocalBounds());
	text.setOrigin(Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
	target.draw(text);
}
