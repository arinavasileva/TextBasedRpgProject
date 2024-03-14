#include <iostream>
#include <string>

class Inventory {
private:
	class Item {
	public:
		std::string itemName;
		Item* _pNext;
		//Item();
		//~Item();
	};

	Item* first;
	Item* last;

public:	
	Inventory& addItem(std::string item);
	void removeItem(std::string item);
	void showInventory();
	bool isEmpty();
};

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
        std::cout << "Nothing to remove." << std::endl;
        return;
    }

    if (first->itemName == item) {
        Item* temp = first;
        first = first->_pNext;
        delete temp;
        std::cout << "Removed " << item << "." << std::endl;
        return;
    }

    Item* current = first;
    Item* prev = nullptr;
    while (current != nullptr) {
        if (current->itemName == item)
        {
            std::cout << "Removed " << item << ".";
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
    std::cout << "| ";
    Item* current = first;
    while (current != nullptr) {
        std::cout << current->itemName << " | ";
        current = current->_pNext;
    }
    std::cout << std::endl;
}

bool Inventory::isEmpty()
{
    return first == nullptr;
}

//Inventory::Item::Item()

//Inventory::Item::~Item()
