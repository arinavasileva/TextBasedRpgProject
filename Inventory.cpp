#include "Inventory.h"
#include <iostream>
#include <string>


//improvement idea: check for duplicates
Inventory& Inventory::addItem(std::string item)
{
	Item* newItem = new Item;
	newItem->itemName = item;
	newItem->_pNext = nullptr;

	if (first == nullptr) {
		first = newItem;
		last = newItem;
	}
	else {
		last->_pNext = newItem;
		last = newItem;
	}

	return *this;
}

void Inventory::removeItem(std::string item)
{
    if (first == nullptr) {
        cout << "Nothing to remove.";
        return;
    }

    if (first->itemName == item) {
        Item* temp = first;
        first = first->_pNext;
        delete temp;
        cout << "Removed " << item << ".";
        return;
    }

    Item* current = first;
    Item* prev = nullptr;
    while (current != nullptr) {
        if (current->itemName == item)
        {
            cout << "Removed " << item << ".";
            if (current == last) {
                last = prev;
            }
            if (prev != nullptr) {
                prev->_pNext = current->_pNext;
            }
            else {
                first = current->_pNext;
            }
            delete current;
            return;
        }
        else {
            prev = current;
            current = current->_pNext;
        }
    }
}

void Inventory::showInventory()
{
	cout << "| ";
	Item* current = first;
	while (current != nullptr) {
		cout << current->itemName << " | ";
		current = current->_pNext;
	}
	cout << endl;
}

bool Inventory::isEmpty()
{
	return first == nullptr;
}

//Inventory::Item::Item()

//Inventory::Item::~Item()
