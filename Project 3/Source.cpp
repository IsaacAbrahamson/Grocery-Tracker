#include <fstream>
#include <set>
#include "GroceryItem.h"
#include <iostream>

std::string INPUT_FILE = "input.txt";
std::string OUTPUT_FILE = "frequency.txt";

void createBackup(std::set<GroceryItem> items);
std::set<GroceryItem> readData();
void printMenu();
void printError();
std::string printHistogram(GroceryItem item);

// Program entry point
int main() {
	// Loop until user exits program
	bool run = true;
	while (run) {
		printMenu();

		try {
			std::cin.exceptions(std::istream::failbit);
			int inputChoice;
			std::cin >> inputChoice;

			// Handle invalid integer input
			if (inputChoice < 1 || inputChoice > 4) {
				printError();
				continue;
			}

			// Search item frequency
			if (inputChoice == 1) {
				std::set<GroceryItem> items = readData();

				std::cout << "Enter the item to find:" << std::endl;
				std::string itemInput;
				std::cin >> itemInput;

				// Find the matching item
				for (GroceryItem item : items) {
					if (item.getName() == itemInput) {
						std::cout << std::endl;
						std::cout << "==- Search Results ----------==" << std::endl;
						std::cout << item.getName() << " " << item.getQuantity() << std::endl;
						std::cout << "==---------------------------==" << std::endl;
						std::cout << std::endl;
					}
				}
			}
			
			// All item frequencies
			else if (inputChoice == 2) {
				std::set<GroceryItem> items = readData();

				std::cout << std::endl;
				std::cout << "==- Item Frequencies --------==" << std::endl;
				for (GroceryItem item : items) {
					std::cout << item.getName() << " " << item.getQuantity() << std::endl;
				}
				std::cout << "==---------------------------==" << std::endl;
				std::cout << std::endl;
			}

			// Frequency Histogram
			else if (inputChoice == 3) {
				std::set<GroceryItem> items = readData();

				std::cout << std::endl;
				std::cout << "==- Frequency Histogram -----==" << std::endl;
				for (GroceryItem item : items) {
					std::cout << printHistogram(item) << std::endl;
				}
				std::cout << "==---------------------------==" << std::endl;
				std::cout << std::endl;
			}

			// Exit program
			else if (inputChoice == 4) {
				run = false;
				std::cout << "Goodbye!";
			}
		}
		// Handle non-integer input
		catch (std::ios_base::failure& e) {
			printError();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
}

// Creates a backup of the accumulated grocery item data.
// @param items A set of grocery items to backup.
void createBackup(std::set<GroceryItem> items) {
	std::ofstream outFS;
	outFS.open(OUTPUT_FILE);

	// Ensure that file is open
	if (!outFS.is_open()) {
		throw new std::runtime_error("Could not open file: " + OUTPUT_FILE);
	}

	// Output each item
	for (GroceryItem item : items) {
		outFS << item.getName() << " " << item.getQuantity() << std::endl;
	}

	outFS.close();
}

// Reads the input data and outputs a backup.
// @returns A set of grocery items with the correct quantity.
std::set<GroceryItem> readData() {
	std::ifstream inFS;
	inFS.open(INPUT_FILE);

	// Ensure that file is open
	if (!inFS.is_open()) {
		throw new std::runtime_error("Could not open file: " + INPUT_FILE);
	}

	// Read until end of file
	std::set<GroceryItem> items;
	while (!inFS.eof()) {
		// Create new grocery item from name
		std::string itemName;
		inFS >> itemName;
		GroceryItem* currentItem = new GroceryItem(itemName);

		// Check if grocery item is in set already
		std::set<GroceryItem>::iterator existingItem = items.find(*currentItem);
		if (existingItem != items.end()) {
			// Copy the values from the existing item
			GroceryItem groceryItem = *existingItem;
			std::string existingName = groceryItem.getName();
			int existingQty = groceryItem.getQuantity();
			
			// Erase existing item from set
			items.erase(existingItem);

			// Re-assign current item
			currentItem = new GroceryItem(existingName, existingQty);
		}

		currentItem->addItem();
		items.insert(*currentItem);
		delete currentItem;
	}

	// Output a backup of the frequencies
	createBackup(items);

	inFS.close();
	return items;
}

// Prints the menu to run the program.
void printMenu() {
	std::cout << "==- Program Menu ------------==" << std::endl;
	std::cout << std::endl;
	std::cout << "1: Search for frequency of item" << std::endl;
	std::cout << "2: View frequency for all items" << std::endl;
	std::cout << "3: View frequency histogram" << std::endl;
	std::cout << "4: Exit Program" << std::endl;
	std::cout << std::endl;
	std::cout << "==---------------------------==" << std::endl;
	std::cout << std::endl;
}

// Prints a warning about invalid input.
void printError() {
	std::cout << std::endl;
	std::cout << "==- Error -------------------==" << std::endl;
	std::cout << "You must enter a value from 1-4" << std::endl;
	std::cout << "==---------------------------==" << std::endl;
	std::cout << std::endl;
}

// Prints a nicely formatted histogram entry for a grocery item.
// @param item The grocery item to create a histogram for.
// @returns A formatted histogram entry string.
std::string printHistogram(GroceryItem item) {
	// Convert number to stars
	std::string stars = "";
	for (int i = 0; i < item.getQuantity(); i++) {
		stars += "*";
	}

	// Pad stars to have fixed width of 15 characters
	// This would need to be modified if an item can
	// have more than 15 quantity.
	std::string paddedStars = stars;
	while (paddedStars.length() < 15) {
		paddedStars = " " + paddedStars;
	}

	std::string output = paddedStars + " " + item.getName();
	return output;
}