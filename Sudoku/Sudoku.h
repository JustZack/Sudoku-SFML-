#pragma once
//Defines the 3x3 set of cells on a sudoku game
//Also handles the drawing, solving, and updating of the board.
//The main method of this program should only contain a run method for sudoku
#include <SFML\Graphics.hpp>
#include "SudokuCell.h"
#include <chrono>

class Sudoku
{
private:
	std::chrono::milliseconds start;
	std::chrono::milliseconds end;
	bool firstFrame = false;


	//Window used to render the sodoku game visualy
	sf::RenderWindow sudokuWindow;
	//Represents the 3x3 cell grid of a sodoku board
	SudokuCell cells[3][3];
	SudokuCell nextCells[3][3];

	//Saves the initial state of the board.
	SudokuCell initialCells[3][3];

	float cellSize;
	float borderSize;

	//Stores how many times update was called on an unsolved board.
	int steps = 0;
	//True if when the board is solved, used a bit
	bool boardSolved = false;
	//Used to allow unlimeted framerate and precise space mashing
	bool spaceReleased = true;
	bool rReleased = true;

	sf::Color numberColors[4] = { sf::Color::Black, sf::Color::Cyan, sf::Color::Red, sf::Color::Magenta };

	sf::RectangleShape cellShape;

	sf::Text numbersShape;

	sf::Font font;
public:
	//width = pixel width of window
	//height = pixel height of window
	//filePath = path to file containing a sodoku game in plain text.
	Sudoku(float width, float height, std::string filePath = "No File");

	//Starts the cylce for updating the sodoku window, and waiting for input.
	//Also calls the draw and update methods for the sodoku game.
	void run();

	//Reset the board to when it was initialy created.
	void reset();
private:
	void draw(); //Draw all objects to the window
	void update();

	void generateNewGame(); // Instantiate cells array here
	bool readFile(std::string filePath); // Instantiate cells array here
	
	//A haed coded sudoku
	void hardCoded();
};

/*
Methods & helper methods for each method:

	+run : void / Starts the never ending cycle of running, Calls the update, and draw method
	-update : void / Updates the boar
	-draw : void  / Draws the sodoku game to the render window
	-determinePossibilities : void / Determines all of the numberical possibilities for each cell.
	-generateNewGame() : void / Generates a new (valid) sodoku game
	-readFile(String fileName) : bool / Reads a file containing a sodoku game.

Fields:
	SudokuCell[][] actualCells :2D array containing all 9 cells on the sudoku board
		Each cell contains data about each cell within its 3x3 area, including if it has a number, and what the number is.	
	float cellSize / Defines the width and height of each cell
				/ relative to the size of the window
	float borderSize / Defines the size of the border
				  / which goes between each 3x3 "clump"
	sf::RectangleShape cellShape / Used to draw each cell onto the board
								/ Subject to be changed to a texture so i can show nice images with numbers on them
*/