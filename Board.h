#pragma once
#include "Field.h"

#include <stack>
#include <vector>
#include <random>

using namespace std;

class Board
{
private:
	Vector2f pos;

	vector<Field> fields;

	int size;

	bool isFilled;
	
	mt19937 random;

private:
	void fill(const int& index);

	void floodReveal(const int& index);

	int getFieldIndex(const Vector2i& mouse) const;

	int getRevealedCount() const;

	void revealBombs();

public:
	Board(const Vector2f& pos);

	void restart();

	bool clickField(const Vector2i& mouse);

	void setFlag(const Vector2i& mouse);

	int getFlagCount() const;

	int getBombCount() const;
	
	bool checkIfWin() const;

	void draw(RenderTarget& target, const Font& font, const Texture& tex) const;

};

