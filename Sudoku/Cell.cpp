#include "Cell.h"
Cell::Cell()
{
	//Set the value of the cell.
	value = 0;

	//Set the values of the possible values array
	for (short i = 0; i < 9; i++)
		possibleValues[i] = 0;
}

Cell::Cell(short Value)
{
	//Set the value of the cell.
	value = Value;
	if (value > 0)
		_isInitial = true;
	//Set the values of the possible values array
	for (short i = 0; i < 9; i++)
			possibleValues[i] = false;
}

bool Cell::isset()
{
	return value != 0;
}
bool Cell::isInitial()
{
	return _isInitial;
}
void Cell::notInitial()
{
	_isInitial = false;
}

short Cell::getValue()
{
	return value;
}
void Cell::setValue(short Value)
{
	if (Value >= 0 && Value <= 9) value = Value;
}

bool * Cell::getPossibleValues()
{
	return possibleValues;
}
void Cell::setPossibleValues(bool newPossibleValues[])
{
	for(short i = 0;i < 9;i++)
			possibleValues[i] = newPossibleValues[i];
}

void Cell::addPossibleValue(short value)
{
	possibleValues[value - 1] = true;
}