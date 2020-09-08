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

	float delay;

	Clock clock;

public:
	Button(const Vector2f& pos, const Vector2f& size, const string& str);

	void setString(const string& str);

	bool checkIfClicked(const Vector2i& mouse);

	void draw(RenderTarget& target, const Font& font) const;
};

