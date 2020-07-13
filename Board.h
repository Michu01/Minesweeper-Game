#pragma once

#include "Field.h"

#include <vector>

class Board
{
private:
	Vector2f pos;

	std::vector<Field> fields;

	int size;
	int bombCount;

public:
	Board();

	~Board();

	void setPos(Vector2f m_pos);

	int getFlagCount();

	int getBombCount();

	int getRevealedCount();
	
	bool checkIfWin();

	void create();

	void fill(Vector2i mouse);

	void clear();

	void floodReveal(int n);

	void revealBombs();

	Field* getFieldPointer(Vector2i mouse);

	int getIndex(Field* fieldPtr);

	void draw(RenderTarget* target, Font* font, Texture* tex);

};

