#include "SudokuCell.h"
#include <iostream>

//Default constructor, works but should not be used.
SudokuCell::SudokuCell()
{
	for (short i = 0; i < 3; i++)
		for (short j = 0; j < 3; j++)
			cells[i][j] = Cell(0);
	resetPossibleValues();
}
//Instaniates the cell with the values passed to it for its child cells.
SudokuCell::SudokuCell(Cell Cells[3][3])
{
	for (short i = 0; i < 3; i++)
		for (short j = 0; j < 3; j++)
			cells[i][j] = Cells[i][j];
	resetPossibleValues();
}

void SudokuCell::resetPossibleValues()
{
	for (short i = 0; i < 9; i++)
		possibleValues[i] = false;
}

void SudokuCell::determinePossibleValues()
{
	resetPossibleValues();
	for (short row = 0; row < 3; row++) {//Rows in 3x3
		for (short col = 0; col < 3; col++) {//Cols in 3x3
			if (cells[row][col].isset()) //Cell has a value > 0
			{
				possibleValues[cells[row][col].getValue() - 1] = true;
				for (short i = 0; i < 3; i++) //Rows in 3x3
					for (short j = 0; j < 3; j++) //cols in 3x3
						cells[i][j].addPossibleValue(cells[row][col].getValue());
				//add the value  > 0 to each of the possible numbers array
			}
		}
	}
}

void SudokuCell::setValueAt(short row, short column, short value)
{
		cells[row][column].setValue(value);
}
short SudokuCell::getValueAt(short row, short column)
{
	return cells[row][column].getValue();
}

bool * SudokuCell::getPossibleValuesAt(short row, short column)
{
	return cells[row][column].getPossibleValues();
}
void SudokuCell::setPossibleValuesAt(short row, short column, bool newPossibleValues[])
{
	cells[row][column].setPossibleValues(newPossibleValues);
}
void SudokuCell::addPossibleValueAt(short row, short column, short value)
{
	cells[row][column].addPossibleValue(value);
}

bool * SudokuCell::getPossibleValues()
{
	return possibleValues;
}

bool SudokuCell::isCellSetAt(short row, short column)
{
	return cells[row][column].isset();
}
bool SudokuCell::isCellInitialAt(short row, short column)
{
	return cells[row][column].isInitial();
}
void SudokuCell::cellIsNotInitialAt(short row, short column)
{
	cells[row][column].notInitial();
}