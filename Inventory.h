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