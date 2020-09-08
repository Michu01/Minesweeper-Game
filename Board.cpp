#include "Board.h"

Board::Board(const Vector2f& pos) 
	: isFilled(false), pos(pos), size(10)
{
	Field field(Vector2f(40, 40));

	for (int n = 0; n < size; ++n)
		for (int m = 0; m < size; ++m)
		{
			field.setPos(Vector2f(pos.x + m * 40, pos.y + n * 40));
			fields.push_back(field);
		}

	random_device rd;
	random.seed(rd());
}

void Board::restart()
{
	for(auto& field : fields)
		field.restart();

	isFilled = false;
}

bool Board::clickField(const Vector2i& mouse)
{
	int index{ getFieldIndex(mouse) };

	if (index != -1)
	{
		if (!isFilled) fill(index);
		
		floodReveal(index);

		if (fields[index].getIsBomb())
		{
			revealBombs();
			return true;
		}
	}

	return false;
}

void Board::setFlag(const Vector2i& mouse)
{
	int index{ getFieldIndex(mouse) };
	if (isFilled && index != -1) fields[index].setFlag();
}

int Board::getFlagCount() const
{
	int flagCount{ 0 };
	for (const auto& field : fields)
		if (field.getIsFlag())
			++flagCount;
	return flagCount;
}

int Board::getBombCount() const
{
	return size;
}

int Board::getRevealedCount() const
{
	int revealedCount{ 0 };
	for (const auto& field : fields)
		if (field.getIsRevealed())
			++revealedCount;
	return revealedCount;
}

bool Board::checkIfWin() const
{
	return size * size - getRevealedCount() == size;
}

void Board::fill(const int& index)
{
	uniform_int_distribution<int> dist(0, size * size - 1);
	int bombs{ 0 };
	while (bombs < size)
	{
		int n{ dist(random) };
		if (!fields[n].getIsBomb() && n != index)
		{
			++bombs;
			fields[n].setBomb();
		}
	}

	for (int n = 0; n < size * size; ++n)
	{
		if (fields[n].getIsBomb())
		{
			int lineNum{ n / size };

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

	isFilled = true;
}

void Board::floodReveal(const int& index)
{
	stack<int> indices;
	indices.push(index);

	while (!indices.empty())
	{
		int index{ indices.top() };
		indices.pop();

		if (fields[index].getValue() == 0 && !fields[index].getIsBomb() && !fields[index].getIsRevealed())
		{
			int lineNum{ index / size };

			if (index - 1 >= lineNum * size && !fields[index - 1].getIsRevealed())
					indices.push(index - 1);

			if (index + 1 < (lineNum + 1) * size && !fields[index + 1].getIsRevealed())
					indices.push(index + 1);

			if (index - size >= 0 && !fields[index - size].getIsRevealed())
					indices.push(index - size);

			if (index + size < size * size && !fields[index + size].getIsRevealed())
					indices.push(index + size);

			if (index - size - 1 >= 0 && index - 1 >= lineNum * size && !fields[index - size - 1].getIsRevealed())
					indices.push(index - size - 1);

			if (index - size + 1 >= 0 && index + 1 < (lineNum + 1) * size && !fields[index - size + 1].getIsRevealed())
					indices.push(index - size + 1);

			if (index + size - 1 < size * size && index - 1 >= lineNum * size && !fields[index + size - 1].getIsRevealed())
					indices.push(index + size - 1);

			if (index + size + 1 < size * size && index + 1 < (lineNum + 1) * size && !fields[index + size + 1].getIsRevealed())
					indices.push(index + size + 1);
		}
		fields[index].reveal();
	}
}

void Board::revealBombs()
{
	for (auto& field : fields)
		if (field.getIsBomb())
			field.reveal();
}

int Board::getFieldIndex(const Vector2i& mouse) const
{
	for (int n = 0; n < (int)fields.size(); ++n)
		if (fields[n].getIsClicked(mouse))
			return n;
	return -1;
}

void Board::draw(RenderTarget& target, const Font& font, const Texture& tex) const
{
	for (const auto& field : fields)
		field.draw(target, font, tex);
}