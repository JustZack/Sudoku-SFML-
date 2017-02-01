#include "Sudoku.h"
#include <iostream>
#include <fstream>

Sudoku::Sudoku(float width, float height, std::string filePath)
{
	//Sets up the data for the sodoku solver window.
	sudokuWindow.create(sf::VideoMode(width, height), "Sodoku Solver");
	//sudokuWindow.setFramerateLimit(5);
	//Determine the size of the cells, and the size of the borders.
	borderSize = width / 50.f;
	cellSize = (width - borderSize * 2) / 9.f;
	
	//Setup the cellShape as much as possible.
	cellShape.setSize(sf::Vector2f(cellSize, cellSize));
	cellShape.setFillColor(sf::Color::White);
	cellShape.setOutlineThickness(cellSize / 18.f);
	cellShape.setOutlineColor(sf::Color::Black);

	numbersShape.setFillColor(sf::Color::Black);
	numbersShape.setStyle(sf::Text::Regular);
	numbersShape.setCharacterSize(cellSize);
	font.loadFromFile("arial.ttf");
	numbersShape.setFont(font);

	//Determine if we must generate a new sodoku board,
	//Or if we must read a file into our sodoku memory cells.
	if (filePath == "No File")
	{
		//generateNewGame();
	}
	else
	{
		if (!readFile(filePath))
		{
			std::cout << "File was unreadable or invalid" << std::endl;
			system("PAUSE");
			return;
		}
	}

	//Starts up the ENTIRE GAME!
	readFile(filePath);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			initialCells[i][j] = cells[i][j];

	run();
}

void Sudoku::run()
{	
	sf::Event event;

	sudokuWindow.clear(sf::Color::Black);
	draw();
	sudokuWindow.display();

	while (sudokuWindow.isOpen())
	{
		while (sudokuWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				sudokuWindow.close();
			}
		}

		if (sudokuWindow.hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceReleased)
			{
				spaceReleased = false;
				if (!boardSolved)
				{
					/*if (!firstFrame)
					{
						start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
						firstFrame = true;
					}*/
					update();
				}
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				spaceReleased = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && rReleased)
			{
				rReleased = false;
				reset();
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				rReleased = true;
		}
		sudokuWindow.clear(sf::Color::Black);
		draw();
		sudokuWindow.display();
	}
}

void Sudoku::reset()
{
	steps = 0;
	boardSolved = false;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j] = initialCells[i][j];
	std::cout << "Reset" << std::endl;
}
//TODO: Draw numbers that were initialy there with black, and new numbers with another color
void Sudoku::draw()
{
	//X and y values that clean up the code a bit.
	float x = 0, y = 0;

	//Cycle through each cell, 
	//Draw each cell to the screen
	//Draw each number ontop of each cell
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 3; j++) {
			for (short k = 0; k < 3; k++) {
				for (short l = 0; l < 3; l++) {
					x = (j * cellSize * 3) + (k * cellSize) + (j * borderSize);
					y = (i * cellSize * 3) + (l * cellSize) + (i * borderSize);
					cellShape.setPosition(sf::Vector2f(x, y));
					sudokuWindow.draw(cellShape);
					if (cells[i][j].getValueAt(l, k) > 0)
					{
						numbersShape.setString(std::to_string(cells[i][j].getValueAt(l, k)));
						numbersShape.setPosition(sf::Vector2f(x + (cellSize / 5), y - (cellSize / 7)));
						if (cells[i][j].isCellInitialAt(l, k))
							numbersShape.setFillColor(numberColors[0]);
						else
							numbersShape.setFillColor(numberColors[1]);
						sudokuWindow.draw(numbersShape);
					}
				}
			}
		}
	}
}

//Update the board
void Sudoku::update()
{
	//Save all of the current board into the next version
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j].determinePossibleValues();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			nextCells[i][j] = cells[i][j];

	for (int groupRow = 0; groupRow < 3; groupRow++)
	{
		for (int groupCol = 0; groupCol < 3; groupCol++)
		{
			//At this point we are down to an individual group of 3x3 cells.

			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					//At this pont we are down to an individual cell.

					if (cells[groupRow][groupCol].isCellSetAt(row, col))
					{
						//Cell contains a value > 0.
						//We do not want these cells
					}
					else
					{
						//Cells value is 0.

						//Create and initialize 9 element boolean array to store possible values of this cell.
						bool tempPossible[9];
						for (int i = 0; i < 9; i++)
							tempPossible[i] = cells[groupRow][groupCol].getPossibleValuesAt(row, col)[i];

						//Check for all values in the cells row, and add them to the possible values array.
						short val;
						for (int cellCol = 0; cellCol < 9; cellCol++)
						{
							val = cells[groupRow][cellCol / 3].getValueAt(row, cellCol % 3);
							if(val > 0)
								tempPossible[val - 1] = true;
						}

						//Check for all calues in the cells column, and add them to the possible values array.
						for (int cellRow = 0; cellRow < 9; cellRow++)
						{
							val = cells[cellRow / 3][groupCol].getValueAt(cellRow % 3, col);
							if (val > 0)
								tempPossible[val - 1] = true;
						}

						//Check how many possible values there are for this cell.
						short possibleCount = 0;
						for (int i = 0; i < 9; i++) {
							if (tempPossible[i] == 0) {
								possibleCount++;
								val = i + 1;
							}
						}

						//add the current temp values to the cell
						nextCells[groupRow][groupCol].setPossibleValuesAt(row, col, tempPossible);
							
						//If there is only one possible value
						if (possibleCount == 1)
						{
							//std::cout << "Found a number at " << groupRow << " , " << groupCol << " / " << row << " , " << col << " : " << val << std::endl;
							nextCells[groupRow][groupCol].setValueAt(row, col, val);
							nextCells[groupRow][groupCol].cellIsNotInitialAt(row, col);
						}
					}

				}
			}

		}
	}

	//Save the next board to the current boards
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cells[i][j] = nextCells[i][j];

	//Count up how many cells are currently set.
	int setCount = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for(int k = 0;k < 3;k++)
				for(int l = 0;l < 3;l++)
					if(cells[i][j].isCellSetAt(k,l))
						setCount++;
	if (!boardSolved)
	{
		steps++;
		if (setCount == 81 && !boardSolved)
		{
			boardSolved = true;
			std::cout << "Puzzle solved in " << steps << " steps" << std::endl;
			/*end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			std::cout << end.count() - start.count() << "ms to solve puzzle." << std::endl;*/
		}
	}
}

//To update the board when there are times when you must guess, 
//	Try that path with that guess until you decide it cannot be solved.
//	Then revert back to before you started that path and try the next guess.

//Read a sudoku from a file.
bool Sudoku::readFile(std::string filePath)
{
	Cell tempCellGroup[3][3];
	int currentLocationInString = 0;
	//Open up a file reader object, and give it my sudoku file.
	std::ifstream fileReader(filePath);
	if (!fileReader.good()) //Ensure the file was correctly 
	{
		//Let me know that the file was bad, and then return false, meaning the file was unreadable.
		std::cout << "File at " << filePath << " could not be loaded." << std::endl;
		return false;
	}
	else
	{
		//Read the files contents into a string object
		std::string contents((std::istreambuf_iterator<char>(fileReader)), std::istreambuf_iterator<char>());

		//Split the string up into an array of sudoku groups as strings?
		for (int groups = 0; groups < 9; groups++)
		{
			for (int i = 0; i < 3;i++)
			{
				for (int j = 0; j < 3;j++)
				{
					//Number is between 0 and 
					if((int)contents[currentLocationInString] - 48 > -1 && (int)contents[currentLocationInString] - 48 < 10)
						tempCellGroup[i][j] = Cell((int)contents[currentLocationInString] - 48);
					else j--; //We still needt to add a value to this location, so do not increment j.
			
					//Always incremement the location we are in the string
					currentLocationInString++;
				}
			}
			//Save the cells read from the file to the cells array.
			cells[groups / 3][groups % 3] = SudokuCell(tempCellGroup);
			initialCells[groups / 3][groups % 3] = SudokuCell(tempCellGroup);
		}
	}
	//Everything went well,so return true.
	return true;
}

//Has a hardcoded sudoku that i know works incase something goes wrong. (Or i want to show it off)
void Sudoku::hardCoded()
{
	Cell cellsOne[3][3] = { { Cell(5),Cell(3),Cell(0) },{ Cell(6),Cell(0),Cell(0) },{ Cell(0),Cell(9),Cell(8) } };
	Cell cellsTwo[3][3] = { { Cell(0),Cell(7),Cell(0) },{ Cell(1),Cell(9),Cell(5) },{ Cell(0),Cell(0),Cell(0) } };
	Cell cellsThree[3][3] = { { Cell(0),Cell(0),Cell(0) },{ Cell(0),Cell(0),Cell(0) },{ Cell(0),Cell(6),Cell(0) } };
	Cell cellsFour[3][3] = { { Cell(8),Cell(0),Cell(0) },{ Cell(4),Cell(0),Cell(0) },{ Cell(7),Cell(0),Cell(0) } };
	Cell cellsFive[3][3] = { { Cell(0),Cell(6),Cell(0) },{ Cell(8),Cell(0),Cell(3) },{ Cell(0),Cell(2),Cell(0) } };
	Cell cellsSix[3][3] = { { Cell(0),Cell(0),Cell(3) },{ Cell(0),Cell(0),Cell(1) },{ Cell(0),Cell(0),Cell(6) } };
	Cell cellsSeven[3][3] = { { Cell(0),Cell(6),Cell(0) },{ Cell(0),Cell(0),Cell(0) },{ Cell(0),Cell(0),Cell(0) } };
	Cell cellsEight[3][3] = { { Cell(0),Cell(0),Cell(0) },{ Cell(4),Cell(1),Cell(9) },{ Cell(0),Cell(8),Cell(0) } };
	Cell cellsNine[3][3] = { { Cell(2),Cell(8),Cell(0) },{ Cell(0),Cell(0),Cell(5) },{ Cell(0),Cell(7),Cell(9) } };

	cells[0][0] = SudokuCell(cellsOne);
	cells[0][1] = SudokuCell(cellsTwo);
	cells[0][2] = SudokuCell(cellsThree);
	cells[1][0] = SudokuCell(cellsFour);
	cells[1][1] = SudokuCell(cellsFive);
	cells[1][2] = SudokuCell(cellsSix);
	cells[2][0] = SudokuCell(cellsSeven);
	cells[2][1] = SudokuCell(cellsEight);
	cells[2][2] = SudokuCell(cellsNine);
}