#pragma once
//Defines a 3x3 cell containing 9 numbers

#include "cell.h"

class SudokuCell
{
private:
	//Defines a set of individual cells for the 3x3 area of this particular sudoku cell.
	Cell cells[3][3];
	bool possibleValues [9];
	//Maybe make some fields here that determine the size of each cell on the board.
	void resetPossibleValues();
public:
	SudokuCell(); // Defualt constructor. Should NEVER be used.
	SudokuCell(Cell Cells[3][3]); // Correct constructor. Attains the value of each cell on creation.


	void determinePossibleValues(); // Determines all possible values of each cell, relative ONLY to what is in the cell.
	void setValueAt(short row, short column, short value); // Sets the possible values of a cell.
	short getValueAt(short row, short column); // Returns the value of a cell.

	bool * getPossibleValuesAt(short row, short column); // Returns the possible values of the cell
	void setPossibleValuesAt(short row, short column, bool newPossibleValues[]); // Sets the possible values of the cell.
	void addPossibleValueAt(short row, short column, short value);

	bool * getPossibleValues();

	bool isCellSetAt(short row, short colomn);
	bool isCellInitialAt(short row, short column);
	void cellIsNotInitialAt(short row, short column);
};

/*
Methods:
	SudokuCell() / Default constructor
	SudokuCell(Cell cells[][]) / takes the values of each cell that should exist in this sudoku cell. 
	
	+determinePossibleValues() : void / Determines the possible values of each cell in this sudoku cell. 
	+setValueAt(short row, short column) : void / Sets the value of the cell at the row and column
		Takes arguments on a zero based index system. (Starts at 0)
	+getValueAt(short row, short column) : short / returns the value of the cell in this cell. (0 - 9)

	+getPossibleValuesAt(short row, short colummn) : bool* / Returns the array of possible values for that cell
	+setPossibleValuesAt(short row, short columns, bool newPossibleValues[9]) : void / Sets the array of possible values for that cell

Fields: 
	Cell cells[3][3] / Defines the set of cells within this sudoku cell.
	*/