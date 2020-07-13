#include "Board.h"

Board::Board()
{
	size = 10;
	bombCount = 10;
}

Board::~Board()
{

}

void Board::setPos(Vector2f m_pos)
{
	pos = m_pos;
}

int Board::getFlagCount()
{
	int flagCount{ 0 };
	for (auto field : fields)
		if (field.checkIfFlag())
			flagCount++;
	return flagCount;
}

int Board::getBombCount()
{
	return bombCount;
}

int Board::getRevealedCount()
{
	int revealedCount{ 0 };
	for (auto field : fields)
		if (field.checkIfRevealed())
			revealedCount++;
	return revealedCount;
}

bool Board::checkIfWin()
{
	if (powf((float)size, 2) - getRevealedCount() == bombCount)
		return true;
	else return false;
}

void Board::create()
{
	Field field;
	field.setSize(Vector2f(40, 40));

	for (int n = 0; n < size; n++)
		for (int m = 0; m < size; m++)
		{
			field.setPos(Vector2f(pos.x + m * 40, pos.y + n * 40));
			fields.push_back(field);
		}
}

void Board::fill(Vector2i mouse)
{
	int clickedNum{ 0 };
	for (int n = 0; n < size * size; n++)
		if (fields[n].checkIfClicked(mouse))
		{
			clickedNum = n;
			break;
		}

	int bombs{ 0 };
	while (bombs < bombCount)
	{
		int random = rand() % (size * size);
		if (!fields[random].checkIfBomb() && random != clickedNum)
		{
			bombs++;
			fields[random].setBomb();
		}
	}

	for (int n = 0; n < size * size; n++)
	{
		if (fields[n].checkIfBomb())
		{
			int lineNum = n / size;

			if (n - 1 >= lineNum * size)
				fields[n - 1].addValue();

			if (n + 1 < (lineNum + 1) * size)
				fields[n + 1].addValue();

			if (n - size >= 0)
				fields[n - size].addValue();

			if (n + size < size * size)
				fields[n + size].addValue();

			if (n - size - 1 >= 0 && n - 1 >= lineNum * size)
				fields[n - size - 1].addValue();

			if (n - size + 1 >= 0 && n + 1 < (lineNum + 1) * size)
				fields[n - size + 1].addValue();

			if (n + size - 1 < size * size && n - 1 >= lineNum * size)
				fields[n + size - 1].addValue();

			if (n + size + 1 < size * size && n + 1 < (lineNum + 1) * size)
				fields[n + size + 1].addValue();
		}
	}
}

void Board::clear()
{
	fields.clear();
}

void Board::floodReveal(int n)
{
	fields[n].reveal();

	if (fields[n].getValue() == 0 && !fields[n].checkIfBomb())
	{
		int lineNum = n / size;

		if (n - 1 >= lineNum * size)
			if (!fields[n - 1].checkIfBomb() && !fields[n - 1].checkIfRevealed())
				floodReveal(n - 1);

		if (n + 1 < (lineNum + 1) * size)
			if (!fields[n + 1].checkIfBomb() && !fields[n + 1].checkIfRevealed())
				floodReveal(n + 1);

		if (n - size >= 0)
			if (!fields[n - size].checkIfBomb() && !fields[n - size].checkIfRevealed())
				floodReveal(n - size);

		if (n + size < size * size)
			if (!fields[n + size].checkIfBomb() && !fields[n + size].checkIfRevealed())
				floodReveal(n + size);

		if (n - size - 1 >= 0 && n - 1 >= lineNum * size)
			if (!fields[n - size - 1].checkIfBomb() && !fields[n - size - 1].checkIfRevealed())
				floodReveal(n - size - 1);

		if (n - size + 1 >= 0 && n + 1 < (lineNum + 1) * size)
			if (!fields[n - size + 1].checkIfBomb() && !fields[n - size + 1].checkIfRevealed())
				floodReveal(n - size + 1);

		if (n + size - 1 < size * size && n - 1 >= lineNum * size)
			if (!fields[n + size - 1].checkIfBomb() && !fields[n + size - 1].checkIfRevealed())
				floodReveal(n + size - 1);

		if (n + size + 1 < size * size && n + 1 < (lineNum + 1) * size)
			if (!fields[n + size + 1].checkIfBomb() && !fields[n + size + 1].checkIfRevealed())
				floodReveal(n + size + 1);
	}
}

void Board::revealBombs()
{
	for (auto& field : fields)
		if (field.checkIfBomb())
			field.reveal();
}

Field* Board::getFieldPointer(Vector2i mouse)
{
	for (auto& field : fields)
		if (field.checkIfClicked(mouse))
			return field.getPointer();
	return nullptr;
}

int Board::getIndex(Field* fieldPtr)
{
	return fieldPtr - &fields[0];
}

void Board::draw(RenderTarget* target, Font* font, Texture* tex)
{
	for (auto field : fields)
		field.draw(target, font, tex);
}