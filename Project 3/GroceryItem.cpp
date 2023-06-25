#include "GroceryItem.h"

// Constructor for Grocery Item with only name.
// @param name The name for the grocery item.
GroceryItem::GroceryItem(std::string& name) {
	this->name = name;
	this->quantity = 0;
}

// Constructor for Grocery Item with only name.
// @param name The name for the grocery item.
// @param quantity The quantity for the grocery item.
GroceryItem::GroceryItem(std::string& name, int quantity) {
	this->name = name;
	this->quantity = quantity;
}

// Getter for the GroceryItem name.
// @returns The name for the grocery item.
std::string GroceryItem::getName() const {
	return this->name;
}

// Getter for the GroceryItem quantity.
// @returns The quantity for the grocery item.
int GroceryItem::getQuantity() const {
	return this->quantity;
}

// Adds one to the quantity for the grocery item.
void GroceryItem::addItem() {
	this->quantity++;
}

// Removes one from the quantity for the grocery item.
void GroceryItem::removeItem() {
	this->quantity--;
}

// Overloads the < operator to perform set operations
// @param other A pointer to a GroceryItem to compare against.
// @returns A boolean comparison for the other grocery item.
bool GroceryItem::operator<(const GroceryItem& other) const {
	return name.compare(other.getName()) < 0;
}