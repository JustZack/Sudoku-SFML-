#pragma once
//An individual cell for the sudoku board. One of 81 cells on the baord. Used in the SudokuCell class

class Cell
{
private:
	short value;
	bool possibleValues [9];
	bool _isInitial;
public:
	Cell(); //Default constructor, Not used but required.
	Cell(short Value); //Overloaded constructor, takes the value of the cell, 0 up to 9.

	bool isset(); // Returns wether or not this cell has a value.
	bool isInitial();
	void notInitial();
	short getValue(); //Returns the value of the cell, 0 through (inclusive) 9.
	void setValue(short Value); //Sets the value of the cell.

	bool * getPossibleValues(); //Returns the boolean array of possible values.
	void setPossibleValues(bool newPossibleValues[]); //Sets the value of the possible values array
	void addPossibleValue(short value);
};

/*
Methods:
	Cell(short Value) / Sets the value of the cell, and initializes the array of possible values to false.

	+getValue() : short / Returns the value of the cell. Cank be 0 through 9. only 0 if it has no determined value.
	+setValue(short Value) : void / Sets the value of the array.

	+getPossibleValues() : short[] / Returns the array of possible values for the cell
	+setPossibleValues(bool & newPossibleValues) : void / Sets the possible values array.
Fields:
	short value : Defines the value of the cell. 0 if it has no value, 1 - 9 if it does.
	short possibleValues : Contains the possible values of the cell. 
		Each index can be true or false, true if the number (represented by the index) is a possible value, false otherwise.
*/