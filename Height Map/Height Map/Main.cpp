/*
Student ID: G20713365

*/


// Resolves conflict between iomanip and iostream
#define NOMINMAX

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include <windows.h>


// Stores map size
const int kMapSize = 9;
// Stores half of the map size
const int kMapSizeHalf = (kMapSize / 2);
// Used for multiplication when we need the negative variant of the int. EG: 10 * kIntergerFlip = -10
const int kIntergerFlip = -1;
//Used to store 0
const int kZero = 0;
// Used for minus array mathematics when needing to get the last element of an array. EG: ArraySize - kFlipArrayPadding = Last Array Element Index
const int kFlipArrayPadding = 1;
// Used to define the range of the children checking scan. MUST be odd number larger then 1
const int kCheckChildrenSize = 3;

//////////////////////// Colors ////////////////////////
// Color used for the cursor in the console
const int kConsoleCursorColor = 3;
// Color used for reseting the console back to its default color
const int kConsoleDefaultColor = 7;
// Color used for the mountain pass highlighting
const int kMountanPassColor = 128;
// Color used for setting the water color
const int kWaterColor = 48;

// Minimum value that can be typed into the mountain pass page
const int kMountanPassMinimumInputValue = 0;
// Maximum value that can be typed into the mountain pass page
const int kMountanPassMaximumInputValue = 9;
// Used for minus array mathematics when needing to get the last element of an array. EG: ArraySize - kFlipArrayPadding = Last Array Element Index
const int kArrayMinusPadding = 1;
// Used for working out if the next element will be out of range
const int kArrayPlusPadding = 2;
// To how many places should numbers be displayed in the map output
const int kNumberPlaceSize = 3;
// How many elements need outputted when the main menu is loaded
const int kMainMenuSize = 10;
// Minimum value allowed to be typed by the user on the main menu page
const int kMainMenuMinimumRange = 1;
// Maximum value allowed to be typed by the user on the main menu page
const int kMainMenuMaximumRange = 9;
// The default depth that tge lake fill will use
const int kDefaultLakeDepth = 300;
// The max value a user can input for the lake depth
const int kDefaultLakeMaxDepth = 500;


// Lines of text to be outputted to the screen for the user to see in the menu
const char* kMainMenuStrings[] = {
	"1. Read in map file",
	"2. Display the map",
	"3. Mountain Pass",
	"4. Rotate the map by 90 degrees clockwise",
	"5. Reflect the map vertically",
	"6. Transpose Map",
	"7. Create Lake",
	"8. Climb hill",
	"9. Quit",
	"Enter please select a option by entering [1] - [9]"
};

// Maps to be used for all major menu options
const char* kDefaultMap = "map1.txt";
// The map to be used as default for the lake fill option
const char* kDefaultLakeMap = "map2.txt";
// The default map the be used in the hill climbing menu option
const char* kDefaultHillClimbMap = "map3.txt";
// The cursor symbol for the menu that will be placed before a user input field
const char* kPreInputCursor = "> ";
// The symbol used to divide two integers
const char* kValueDevider = "-";
// Error message when a value is not in range
const char* kCinIntergerNotInRageMessage = "Value not in range, expecting: ";
// Error message to be displayed when a input was not a integer
const char* kCinNotIntegerMessage = "Please enter a valid integer";
// Message that will ask the user for a new map file name
const char* kNewMapFileMessage = "Please enter a new map file path.";
// Error message for when a file is not found
const char* kFileDoseNotExist = "File not found, please try again.";
// Menu options available to the user
const char* kGenerateMapRouteInputOptionsMessage = "Enter [0] - [8] to select a new starting index";
// Menu option available to the user to return to the main menu
const char* kGenerateMapRouteInputReturnMessage = "Enter [9] to return to main menu";
// The message to be outputted before the walkers path is appended to the end of the message
const char* kWalkersPathMessage = "Walkers Path: ";
// Message to output what current map is loaded int the system
const char* kMainMenuLoadedMapMessage = "Currently Loaded Map: ";
// A char array containing all valid number characters. '-' is not included as we will never need a minus number inputed
const char* kAllRegexNumbers = "0123456789";
// Used to split two integers in the system
const char* kSpace = " ";
// message output for entering a new map file
const char* kEnterMapNameMessage = "Please Enter A Map File, EG: map1.txt";
// File loading success message
const char* kMapLoadedMessage = "Map Loaded Successfully";
// Error message for when a invalid file location has been entered
const char* kInvalidFileLocationMessage = "Please Enter A Valid File Location";
// Output message for a user to type a position
const char* kEnterStartingLocationMessage = "Please Enter The Starting Position on the map, EG: 4 4";
// Error message for when the suer enters too many arguments into the console
const char* kTooManyArgumentsMessage = "Too many arguments, please try again.";
// Error message for when the user types too few arguments into the console
const char* kTooFewArgumentsMessage = "Too few arguments, please try again.";
// Output message for when the user fits 
const char* kPositionSetMessage = "Position Set";
// Message to enter the lake depth 
const char* kEnterDepthMessage = "Please enter the required depth, EG:300, in range of ";
// A message to prompt the user to press enter to use the default value
const char* kUseDefaultMessage = "Press [Enter] to use default, ";
// Error message for when a invalid number has been entered
const char* kNotANumberMessage = "Invalid numbers, please try again.";


// A structure to store a 2D vector into.
struct vec2
{
	// Defining the two required variables for the structure
	int x, y;
	// A default constructor to initilize the structure varables
	vec2()
	{
		x = kZero;
		y = kZero;
	}
	// A constructor to initilize the varables with defined values
	vec2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	// A constructor to initialize the variables of the structure with another structures values
	vec2(const vec2& vec)
	{
		x = vec.x;
		y = vec.y;
	}
	//Operator to handle comparison logic between two structures
	bool const operator!=(const vec2& vec)
	{
		return x != vec.x || y != vec.y;
	}
	//Operator to handle comparison logic between two structures
	bool const operator==(const vec2& vec)
	{
		return x == vec.x && y == vec.y;
	}
	//Operator to handle comparison logic between two structures
	bool const operator<(const vec2 &vec)
	{
		return x < vec.x || (x == vec.x && y < vec.y);
	}
};
// Used to store the starting location of the hill climbing menu option
const vec2 kHillClimbPosition(0, 4);
// Used to store the starting point of the lake Position menu
const vec2 kDefaultLakePosition(4, 4);

// A namespace to wrap all general logical functions such as variable conversion
namespace Util
{
	// Here this is used to append extra 0's to the beginning of a number if it is below the required size
	std::string intToStringWithLeadingZeros(int i)
	{
		std::stringstream ss;
		ss << std::setw(kNumberPlaceSize) << std::setfill('0') << i;
		return ss.str();
	}
	// Splits any string into a vector of smaller strings brassed on the search parameter.
	std::vector<std::string> split(std::string dec, std::string str)
	{
		std::vector<std::string> parts;
		// Loop through until its split the string in all posible locations
		while (true)
		{
			int index = str.find(dec);
			// Break once at end of the string
			if (index == std::string::npos) break;
			// Add the vector
			parts.push_back(str.substr(kZero, index));
			str.replace(kZero, index + dec.length(), "");
		}
		parts.push_back(str);
		// Remove whitespace elements from the array
		parts.erase(std::remove_if(parts.begin(), parts.end(),
			[](std::string s) { return s == ""; }), parts.end());
		return parts;
	}
	// REturns a bool value based on if the string is a number
	bool isNumber(std::string str)
	{
		return str.find_first_not_of(kAllRegexNumbers) == std::string::npos && str.size() > kZero;
	}
	// Converts a string into a integer
	int stringToInt(std::string str)
	{
		return std::stoi(str);
	}
	// Checks to see if a file exists and returns a bool response
	bool fileExist(const char* loc)
	{
		std::ifstream file(loc);
		return file.good();
	}
}
// A namespace to store all the console functionality
namespace Console
{
	// Clear the console of all data
	void cClear()
	{
		system("cls");
	}
	// Moved the consoles output onto a new line
	void cNewLine()
	{
		std::cout << std::endl;
	}
	// Writes message onto current line
	void cWrite(const char* consoleMessage)
	{
		std::cout << consoleMessage;
	}
	// Wright a new line into the console
	void cWriteLine(const char* consoleMessage)
	{
		cWrite(consoleMessage);
		cNewLine();
	}
	// Wright output to the console and set a color for the message
	void cWrite(int color, const char* consoleMessage)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		std::cout << consoleMessage;
		SetConsoleTextAttribute(hConsole, kConsoleDefaultColor);
	}
	// Write a new line to the console and set its color of the message
	void cWriteLine(int color, const char* consoleMessage)
	{
		cWrite(color, consoleMessage);
		std::cout << std::endl;
	}
	// Output the cursor
	void preInputCursor()
	{
		cWrite(kPreInputCursor);
	}
	// Read in any string from the console
	std::string cRead()
	{
		std::string val;
		preInputCursor();
		std::getline(std::cin, val);
		return val.c_str();
	}
	// Pause the system using the system pause
	void cPause()
	{
		system("pause");
	}
	// Reads in a int and checks to see if its in range, if it is a valid number
	int cReadInt(bool& isValid)
	{
		std::string line;
		preInputCursor();
		// is the input a valid number
		if (std::getline(std::cin, line) && !Util::isNumber(line))
		{
			cClear();
			// Output error message
			if (line.size() > kZero)
			{
				cWriteLine(kCinNotIntegerMessage);
			}
			isValid = false;
			return NULL;
		}
		isValid = true;
		return Util::stringToInt(line);
	}
	// Reads in a integer from the console and checks to see if its in the range spesified
	int cReadInt(bool& isValid, int min, int max)
	{
		int val = cReadInt(isValid);
		if (!isValid) return val; // Checks the validity of the input
		if (val < min || val > max)
		{
			cClear();
			std::stringstream ss;
			ss << kCinIntergerNotInRageMessage << min << kValueDevider << max;
			cWriteLine(ss.str().c_str());
			isValid = false;
			return NULL;
		}
		return val;
	}
}
// Class to hold all Map Table Data and functions
class MapTable
{
public:
	// MapTable Constructors
	MapTable();
	MapTable(std::string filePath);
	// De-constructor that will handle the memory management of the class
	~MapTable();
	void loadMap(std::string filePath);
	void clear();
	void flipHorizontaly();
	void flipVerticaly();
	void rotateClockwise();
	void rotateAnticlockwise();
	void transpose();
	int getSize();
	std::string getFilePath();
	// Overload operator allows the user to use the square brackets to access the map data
	int* operator[](int i)
	{
		return map[i];
	}
private:
	std::string filePath; // Map file location
	int** reserveMapMemory(); // used to reserve Map memory in the ram
	void destroyMemory(int** data); // Used to destroy the map memory
	int** map; // Used to store the map data
};
// Constructor to populate the class with default data
MapTable::MapTable()
{
	reserveMapMemory();
	clear();
}
// Constructor to populate the class with data from the specified map
MapTable::MapTable(std::string filePath)
{
	reserveMapMemory();
	loadMap(filePath);
}
// Class deconstructions used to clear up memory
MapTable::~MapTable()
{
	destroyMemory(map);
}
// Used to load the map from file into memory
void MapTable::loadMap(std::string _filePath)
{
	filePath = _filePath; // Sets the current map
	std::ifstream infile(filePath); // Creats a input stream
	std::string line;
	int iteration = kMapSize - kArrayMinusPadding;
	// Loop through the y axis backwards
	while (std::getline(infile, line) && iteration < kMapSize)
	{
		if (iteration < kZero) return;
		std::istringstream inStream(line);
		int tempMapHeightStorage;
		// Loop through the x axis
		for (int i = kZero; i < kMapSize; i++)
		{
			if (inStream >> tempMapHeightStorage)
			{
				// Save the value into the array
				map[i][iteration] = tempMapHeightStorage;
			}
		}
		iteration--;
	}
}
// Clears the map with 0's in every slot
void MapTable::clear()
{
	for (int i = kZero; i < kMapSize*kMapSize; i++)
	{
		int x = (i % kMapSize);
		int y = (i / kMapSize);
		map[x][y] = kZero;
	}
}
// Flips the maps data horizontally
void MapTable::flipHorizontaly()
{
	int* tempStorage;
	int halfOfSize = kMapSize / 2;
	for (int i = kZero; i < halfOfSize; i++)
	{
		int toFlip = kMapSize - (i + kFlipArrayPadding);
		tempStorage = map[i];
		map[i] = map[toFlip];
		map[toFlip] = tempStorage;
	}
}
// Flips the map contents vertically
void MapTable::flipVerticaly()
{
	for (int x = kZero; x < kMapSize; x++)
	{
		for (int y = kZero; y < kMapSize / 2; y++)
		{
			int toFlip = kMapSize - (y + kFlipArrayPadding);
			std::swap(map[x][y], map[x][toFlip]);
		}
	}
}
// Rotates the map clockwise
void MapTable::rotateClockwise()
{
	// Initialize Temp storage
	int** temp = new int*[kMapSize];
	// Loop through temp storage and append new array into each array element
	for (int i = kZero; i < kMapSize; i++)
		temp[i] = new int[kMapSize];

	for (int i = kZero; i < kMapSize*kMapSize; i++)
	{
		int x = (i % kMapSize);
		int y = (i / kMapSize);
		//temp[size - kArrayMinusPadding - y][x] = map[x][y];
		temp[x][y] = map[kMapSize - kArrayMinusPadding - y][x];
	}
	for (int i = kZero; i < kMapSize*kMapSize; i++)
	{
		int x = (i % kMapSize);
		int y = (i / kMapSize);
		map[x][y] = temp[x][y];
	}
	destroyMemory(temp);
}
// Rotates the map Anticlockwise
void MapTable::rotateAnticlockwise()
{
	// Initialize Temp storage
	int** temp = new int*[kMapSize];
	// Loop through temp storage and append new array into each array element
	for (int i = kZero; i < kMapSize; i++)
		temp[i] = new int[kMapSize];

	for (int i = kZero; i < kMapSize*kMapSize; i++)
	{
		int x = (i % kMapSize);
		int y = (i / kMapSize);
		//temp[x][y] = map[size - kArrayMinusPadding - y][x];
		temp[kMapSize - kArrayMinusPadding - y][x] = map[x][y];
	}
	for (int i = kZero; i < kMapSize*kMapSize; i++)
	{
		int x = (i % kMapSize);
		int y = (i / kMapSize);
		map[x][y] = temp[x][y];
	}
	destroyMemory(temp);
}
// Transposes the map from quardanate 0, 8 to 8, 0
void MapTable::transpose()
{
	flipVerticaly();
	for (int i = kZero; i < kMapSize; i++)
	{
		for (int j = i + 1; j < kMapSize; j++)
		{
			std::swap(map[j][i], map[i][j]);
		}
	}
	flipVerticaly();
}
// Get the map size in int
int MapTable::getSize()
{
	return kMapSize;
}
// Returns the maps file lcoation
std::string MapTable::getFilePath()
{
	return filePath;
}
// Reserved the maps memory int the ram for alter use
int** MapTable::reserveMapMemory()
{
	map = new int*[kMapSize];
	for (int i = kZero; i < kMapSize; i++)
	{
		map[i] = new int[kMapSize];
	}
	return map;
}
// Destroys the maps memory by using the delete function
void MapTable::destroyMemory(int** data)
{
	for (int i = kZero; i < kMapSize; i++)
	{
		delete data[i];
	}
	delete data;
}
// A class to hold all data regarding the tree branch
class TreeBranch
{
public:
	// Default constructor for the class
	TreeBranch();
	void addChild(TreeBranch& child);
	vec2 getPosition();
	void setPosition(vec2 pos);
	int getValue();
	void setValue(int val);
	std::vector<TreeBranch*> getChildren();
private:
	// Current posiiton of the branch
	vec2 position;
	// Value of the branch
	int value;
	// Chldren surrounding the branch
	std::vector<TreeBranch*> childrenPositions;
};
// No data needs to be saved in the constructor, we just need it to exist
TreeBranch::TreeBranch()
{

}
// This is used to add a child branch the this branch
void TreeBranch::addChild(TreeBranch& child)
{
	childrenPositions.push_back(&child);
}
// Gets the branches positon as a vec2
vec2 TreeBranch::getPosition()
{
	return position;
}
// Sets the branches positon
void TreeBranch::setPosition(vec2 pos)
{
	position = pos;
}
// Gets the branches value
int TreeBranch::getValue()
{
	return value;
}
// Sets the branches value
void TreeBranch::setValue(int val)
{
	value = val;
}
// Returns the children branches in a vector
std::vector<TreeBranch*> TreeBranch::getChildren()
{
	return childrenPositions;
}
// Tree search class sued to look through the map and generate a path
class TreeSearch
{
public:
	TreeSearch(MapTable& treeMap);
	void startMapping(MapTable& treeMap, vec2*& startPosition, vec2& highestPoint);
private:
	void generateSearch(MapTable& treeMap);
	TreeBranch branches[kMapSize][kMapSize];
};
// Drfault Tree search construcotor used to initlize the generation of the tree children
TreeSearch::TreeSearch(MapTable& treeMap)
{
	generateSearch(treeMap);
}
// Used to find all children to the current positon being looked at
void TreeSearch::generateSearch(MapTable& treeMap)
{
	// Loop through the x axis for the map
	for (int x = 0; x < kMapSize; x++)
	{
		// Loop through the y axis for the map
		for (int y = 0; y < kMapSize; y++)
		{
			// Sets the branches values such as posiiton
			branches[x][y].setPosition(vec2(x, y));
			branches[x][y].setValue(treeMap[x][y]);

			// Works out the children y positions reletive to the current branch
			for (int i = (x - kArrayMinusPadding < kZero ? kZero : x - kArrayMinusPadding);
				i <= (x + kArrayMinusPadding > kMapSize - kArrayMinusPadding ? kMapSize - kArrayMinusPadding : x + kArrayMinusPadding);
				i++)
			{
				// Works out the children y positions reletive to the current branch
				for (int j = (y - kArrayMinusPadding < kZero ? kZero : y - kArrayMinusPadding);
					j <= (y + kArrayMinusPadding > kMapSize - kArrayMinusPadding ? kMapSize - kArrayMinusPadding : y + kArrayMinusPadding);
					j++)
				{
					// If the child is not itself, push it into the branch
					if (!(x == i&&y == j)) branches[x][y].addChild(branches[i][j]);
				}
			}
		}
	}
}
// Maps out the whole route and outputs it once its done
void TreeSearch::startMapping(MapTable& treeMap, vec2*& startPosition, vec2& highestPoint)
{
	// Creats a vector to store the route in
	std::vector<TreeBranch> branchOrder;
	MapTable usedBranches;
	// Adds the first position into the route
	branchOrder.push_back(branches[startPosition->x][startPosition->y]);
	usedBranches[startPosition->x][startPosition->y]++;

	bool found = true;// Checks to see if a new branch has been found
	while (branchOrder[branchOrder.size() - kArrayMinusPadding].getPosition() != highestPoint/* && found*/)
	{
		found = false;
		TreeBranch currentBranch = branchOrder[branchOrder.size() - kArrayMinusPadding];
		TreeBranch newBranch;
		// Loop through all current branch children and evaluate them
		for (int i = 0; i < currentBranch.getChildren().size(); i++)
		{
			// Checks to see if the current child has not been checked, and that it is the largest
			if (usedBranches[currentBranch.getChildren()[i]->getPosition().x][currentBranch.getChildren()[i]->getPosition().y] == 0 && // Checks this tile has not been visited
				(!found || newBranch.getValue() < currentBranch.getChildren()[i]->getValue()))
			{
				newBranch = *currentBranch.getChildren()[i];
				found = true;
			}
		}
		// if a valid child was found append it to the list otherwise delete the last child
		if (found)
		{
			branchOrder.push_back(newBranch);
			usedBranches[newBranch.getPosition().x][newBranch.getPosition().y]++;
		}
		else
		{
			branchOrder.pop_back();
		}
	}
	Console::cClear();
	MapTable finalPath;
	for (int i = 0; i < branchOrder.size(); i++)
	{
		finalPath[branchOrder[i].getPosition().x][branchOrder[i].getPosition().y]++;
	}
	// Output the while map with the route highlighted
	for (int y = 8; y >= 0; y--)
	{
		for (int x = 0; x < 9; x++)
		{
			Console::cWrite(finalPath[x][y] > 0 ? kMountanPassColor : kConsoleDefaultColor, Util::intToStringWithLeadingZeros(treeMap[x][y]).c_str());
			Console::cWrite(kSpace);
		}
		std::cout << std::endl;
	}

}
// Storage for the main menu function
void mainMenu();
// Displays the current map being passed to it
void displayMap(MapTable& map)
{
	int size = map.getSize();
	for (int i = kZero; i < size*size; i++)
	{
		// Works out the x axis
		int x = (i % size);
		// Works out the y axis
		int y = (map.getSize() - kArrayMinusPadding) - (i / size);
		if (x == kZero && y < map.getSize() - kArrayMinusPadding)Console::cNewLine();
		int toDisplay = map[x][y];
		// Outputs the current positon, if it is 0 then make it blue as it is water
		Console::cWrite(
			toDisplay == kZero ? kWaterColor : kConsoleDefaultColor,
			Util::intToStringWithLeadingZeros(toDisplay).c_str());
		Console::cWrite(kSpace);
	}
	Console::cNewLine();
}
// Load file into map function 
void loadFileTOMapTable(MapTable& map, const char* defaultIfNoMap)
{
	Console::cWriteLine(kEnterMapNameMessage);
	Console::cWrite(kUseDefaultMessage);
	Console::cWriteLine(defaultIfNoMap);
	std::string preposedFileLocation = Console::cRead();
	// Reads the console untill a valid file is found
	while (preposedFileLocation.size() > kZero && !Util::fileExist(preposedFileLocation.c_str()))
	{
		Console::cWriteLine(kInvalidFileLocationMessage);
		preposedFileLocation = Console::cRead();
	}
	if (preposedFileLocation.size() > kZero)
	{
		map.loadMap(preposedFileLocation.c_str());
	}
	else
	{
		// Passes the map name to the load function
		map.loadMap(defaultIfNoMap);
	}
	Console::cClear();
	Console::cWriteLine(kMapLoadedMessage);
}
// Gets unser inout about where the map search should start 
void loadMapCursorPositon(vec2*& position, int size, const vec2& defaultPosition)
{
	Console::cWriteLine(kEnterStartingLocationMessage);
	Console::cWrite(kUseDefaultMessage);
	std::stringstream ss;
	ss << defaultPosition.x << kSpace << defaultPosition.y;
	Console::cWriteLine(ss.str().c_str());
	std::vector<std::string> startingPosiitonParts;
	// Loop through untill the user types in a correctly formated value in range of 0-8
	do
	{
		startingPosiitonParts.clear();
		std::string preposedStartingLocation = Console::cRead();
		startingPosiitonParts = Util::split(kSpace, preposedStartingLocation);
		if (startingPosiitonParts.size() == kZero)
		{
			/* Used to break out of loop and use default values */
		}
		else if (startingPosiitonParts.size() > 2)// Too many args
		{
			Console::cWriteLine(kTooManyArgumentsMessage);
		}
		else if (startingPosiitonParts.size() < 2) // Too few args
		{
			Console::cWriteLine(kTooFewArgumentsMessage);
		}
		else
		{
			bool allNumbers = true;
			bool numbersInRange = true;
			// Loop though the args to see if they are all valid numbers
			for (int i = kZero; i < startingPosiitonParts.size(); i++)
			{
				if (!Util::isNumber(startingPosiitonParts[i]))
				{
					allNumbers = false;
				}
				else
				{
					int number = Util::stringToInt(startingPosiitonParts[i]);
					if (number > size - kArrayMinusPadding || number < kZero)
					{
						numbersInRange = false;
					}
				}

			}
			if (!allNumbers) // Not numbers
			{
				Console::cWriteLine(kNotANumberMessage);
			}
			else if (!numbersInRange) // Numbers inputed not in range
			{
				Console::cWrite(kCinIntergerNotInRageMessage);
				Console::cWrite(std::to_string(kZero).c_str());
				Console::cWrite(kValueDevider);
				Console::cWriteLine(std::to_string(size - kArrayMinusPadding).c_str());
			}
			else
			{
				// If done correctly the users values will be converted and stored into position
				position = new vec2(Util::stringToInt(startingPosiitonParts[0]), Util::stringToInt(startingPosiitonParts[1]));
			}
		}
	} while (startingPosiitonParts.size() > kZero && position == NULL);
	if (position == NULL)
	{
		position = new vec2(defaultPosition);
	}
	Console::cClear();
	Console::cWriteLine(kPositionSetMessage);
}
// Only Global Variable as it is unavoidable with the function loading setup I have adopted
MapTable currentMap;
// Read in the map file
void readMapFile()
{
	loadFileTOMapTable(currentMap, kDefaultMap);
	Console::cClear();
	mainMenu(); // Returns to the main menu
}
// Used to display the map menu
void displayMapMenu()
{
	displayMap(currentMap);
	Console::cPause();
	Console::cClear();
	mainMenu(); // Returns to the main menu
}
// Runs the mountan pass menu option
void mountanPass()
{
	// Load index value 4 into the starting position
	int val = kMapSizeHalf;
	// Temp storage to check if the users input was in a valid range
	bool isNumberPassed;
	do
	{
		// Create a int array the size of the maps width
		int route[kMapSize];
		// Set the starting position to the current value index typed in by the user
		route[kZero] = val;
		//Calculate Route by looping through the last 8 columns of the table
		for (int x = 1; x < kMapSize; x++)
		{
			// Work out the smallest index to be checked in the next column and store it
			int lowerLimit = route[x - kArrayMinusPadding] - kArrayMinusPadding < kZero ? kZero : route[x - kArrayMinusPadding] - kArrayMinusPadding;
			// Calculate the actual minimum index on the y axis to be check as if its below 0 we need to set it to 0
			int smallestCurrentIndex = lowerLimit;
			// Get the upper index limit on the y axis and if it is greater then 8 then set it to 8
			int limitCap = route[x - kArrayMinusPadding] + 2 <= kMapSize ? route[x - kArrayMinusPadding] + 2 : kMapSize;
			// Loop through the 2-3 index's and find the lowest valued index
			for (int y = lowerLimit; y < limitCap; y++)
			{
				// Check to see if the current lowest index is larger then the one currently being checked
				if (currentMap[x][y] < currentMap[x][smallestCurrentIndex])
				{
					// Define the new smallest index
					smallestCurrentIndex = y;
				}
			}
			// Add the smallest index to the route
			route[x] = smallestCurrentIndex;

		}
		// Output Walkers path inline
		Console::cWrite(kWalkersPathMessage);
		for (int i = kZero; i < kMapSize; i++)
		{
			Console::cWrite(std::to_string(currentMap[i][route[i]]).c_str());
			Console::cWrite(kSpace);
		}
		// Adds 2 spaces between logical path and visual map
		Console::cNewLine();
		Console::cNewLine();
		// Loop through and output walkers path
		for (int y = kMapSize - kArrayMinusPadding; y >= kZero; y--)
		{
			for (int x = kZero; x < kMapSize; x++)
			{
				// Current map tile
				int toDisplay = currentMap[x][y];
				// Output the current map tile and if it is the path that the walker took, change its color to visually represent its path
				Console::cWrite(route[x] == y ? kMountanPassColor : kConsoleDefaultColor, Util::intToStringWithLeadingZeros(toDisplay).c_str());
				Console::cWrite(kSpace);

			}
			Console::cNewLine();
		}
		// Output instructional messages to the user
		Console::cWriteLine(kGenerateMapRouteInputOptionsMessage);
		Console::cWriteLine(kGenerateMapRouteInputReturnMessage);
		// Get the users next input choice in range, if it is 9 then return them to the main menu.
		int tempVal = Console::cReadInt(isNumberPassed, kMountanPassMinimumInputValue, kMountanPassMaximumInputValue);
		if (isNumberPassed) val = tempVal;
		Console::cClear();

	} while (val != kMountanPassMaximumInputValue);
	mainMenu(); // Returns to the main menu
}
// This rotates the map clockwise
void rotateMapClockwise()
{
	currentMap.rotateClockwise();
	mainMenu(); // Returns to the main menu
}
// This rotates the map verticaly
void flipMapVerticaly()
{
	currentMap.flipVerticaly();
	mainMenu(); // Returns to the main menu
}
// This transposes the map
void transposeMap()
{
	currentMap.transpose();
	mainMenu(); // Returns to the main menu
}
// This functon is sued to see if the chuldren to the current positon should be water
void setChildrenWater(MapTable& map, MapTable& waterTable, vec2& pos, int depth)
{
	int padding = kCheckChildrenSize / 2;
	int paddingMod = (kCheckChildrenSize % 2) + padding;
	//Loops through the possible children x axis
	for (int x = pos.x - padding; x < pos.x + paddingMod; x++)
	{
		//Loops through the possible children y axis
		for (int y = pos.y - padding; y < pos.y + paddingMod; y++)
		{
			// if is valid x and y posiitons
			if (x < kZero ||
				y < kZero ||
				x >= waterTable.getSize() ||
				y >= waterTable.getSize())
				continue;
			// if the posiiton is not water and is less then depth, set it ot water
			if (waterTable[x][y] == kZero && map[x][y] < depth)
			{
				waterTable[x][y]++;
				vec2 childPos(x, y);
				setChildrenWater(map, waterTable, childPos, depth);
			}
		}
	}
}
// Initilizes the creat lake menu option
void createLake(MapTable& map, vec2& startingPos, int depth)
{
	MapTable waterTable;
	// Initilizes the creation of the lake
	setChildrenWater(map, waterTable, startingPos, depth);
	// Loops through the map and sets all water posiitons to 0
	for (int x = kZero; x < waterTable.getSize(); x++)
	{
		for (int y = kZero; y < waterTable.getSize(); y++)
		{
			if (waterTable[x][y] > kZero)
				map[x][y] = kZero;

		}
	}
}
// Used to find the largest point on a map
void findLargestPoint(MapTable& map, vec2& position, int& highestValue)
{
	int size = map.getSize();
	for (int i = 0; i < size * size; i++)
	{
		// Calculates the x value
		int x = (i % size);
		int y = (i / size);
		// Calculates the y value
		int val = map[x][y];
		// if the new value is larger then the old, overwirde the old with new
		if (val > highestValue)
		{
			highestValue = val;
			position = vec2(x, y);
		}
	}
}
// This functon is sued to see if the chuldren to the current positon should be water
void createLakeMenu()
{
	MapTable lakeMap;
	// Load Map
	loadFileTOMapTable(lakeMap, kDefaultLakeMap);
	// Gets the starting posiiton
	vec2* startingPos = NULL;
	loadMapCursorPositon(startingPos, lakeMap.getSize(), kDefaultLakePosition);
	//Output
	Console::cWrite(kEnterDepthMessage);
	Console::cWrite(std::to_string(kZero).c_str());
	Console::cWrite(kValueDevider);
	Console::cWriteLine(std::to_string(kDefaultLakeMaxDepth).c_str());


	Console::cWrite(kUseDefaultMessage);
	std::stringstream ss;
	ss << kDefaultLakeDepth;
	Console::cWriteLine(ss.str().c_str());

	int depth = kZero;
	std::string preposedDepth = Console::cRead();
	// Lopps through untill a valid depth is inputed by the user and that it is a number
	while (preposedDepth.size() > kZero && (!Util::isNumber(preposedDepth) || Util::stringToInt(preposedDepth) > kDefaultLakeMaxDepth || Util::stringToInt(preposedDepth) < kZero))
	{
		Console::cWrite(kCinIntergerNotInRageMessage);
		Console::cWrite(std::to_string(kZero).c_str());
		Console::cWrite(kValueDevider);
		Console::cWriteLine(std::to_string(kDefaultLakeMaxDepth).c_str());
		preposedDepth = Console::cRead();
	}
	if (preposedDepth.size() > kZero)
	{
		depth = Util::stringToInt(preposedDepth);
	}
	else
	{
		depth = kDefaultLakeDepth;
	}
	// Calls the create lake function
	createLake(lakeMap, *startingPos, depth);

	Console::cClear();
	displayMap(lakeMap); // REturns to the menu
	Console::cPause();
	Console::cClear();
	mainMenu();
}
// This is used to start the hill climbing menu option
void climbHill()
{
	MapTable hillMap;
	// Load Map
	loadFileTOMapTable(hillMap, kDefaultHillClimbMap);
	// Gets the starting posiiton
	vec2* startingPos = NULL;
	loadMapCursorPositon(startingPos, hillMap.getSize(), kHillClimbPosition);
	// Calculates the highest map posiiton
	vec2 highestPointCoord;
	int highestValue;
	findLargestPoint(hillMap, highestPointCoord, highestValue);
	// Starts a instance of the tree search and runs it
	TreeSearch search(hillMap);
	search.startMapping(hillMap, startingPos, highestPointCoord);
	Console::cPause();
	Console::cClear();
	mainMenu();// Returns to main menu
}
// Used to quit the application
void quit()
{
	exit(kZero);
}
// The main menu is used to output the main options the user is allowed to use
void mainMenu()
{
	//Stores pointers to all the function pointers
	void(*mainMenuFunctions[])() = { readMapFile,displayMapMenu ,mountanPass, rotateMapClockwise, flipMapVerticaly, transposeMap ,createLakeMenu,climbHill,quit };
	int userInput;
	// Keep looping untill the user types a valid console input in the requested range
	bool isValid;
	do
	{
		Console::cWrite(kMainMenuLoadedMapMessage);
		Console::cWriteLine(currentMap.getFilePath().c_str());
		Console::cNewLine();
		for (int i = kZero; i < kMainMenuSize; i++)
		{
			Console::cWriteLine(kMainMenuStrings[i]);
		}
		userInput = Console::cReadInt(isValid, kMainMenuMinimumRange, kMainMenuMaximumRange);
	} while (!isValid);
	Console::cClear();
	// Call the function at index x
	mainMenuFunctions[userInput - kArrayMinusPadding]();
}
// Used to start the aplication
int main()
{
	// Loads the map
	currentMap.loadMap(kDefaultMap);
	mainMenu(); // Opens the main menu
}