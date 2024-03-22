Certainly! Below is a formatted version of the readme file:

---

# Mind Games: A Haunting Escape

Welcome to **Mind Games: A Haunting Escape**, a text-based adventure game where you find yourself trapped in an ancient, haunted mansion. Your only chance of escape lies in unraveling the secrets of the mansion and helping the restless spirits find peace.

## Gameplay Overview

- **Objective**: Navigate through the mansion's dark corridors, solve puzzles, and confront the ghosts of its past to break the curse and escape the mansion.
- **Character Creation**: Choose your character's name, race, and sex to begin your journey.
- **Exploration**: Move through different rooms, where you may encounter items or ghosts.
- **Combat**: Engage in turn-based combat with ghosts using various options like attack, block, use items, or attempt to run away.
- **Inventory**: Manage your inventory to store essential items collected during your exploration.
- **Leveling Up**: Gain experience points (XP) by defeating ghosts to level up and increase your health and abilities.
- **Game End**: Escape the mansion by defeating all the ghosts or meet your demise if your health reaches zero.

## Data Structures Used

- **Structs**: Utilized for representing entities like ghosts and their attributes such as name, health, damage, dialogue, and associated items.
- **Vectors**: Employed for storing lists of ghosts, available player races, items, and ghosts encountered.
- **Map**: Used for mapping JSON data to ghost structures during initialization.
- **Linked List**: Used to implement the inventory system, allowing for efficient insertion and removal of items.

## Example from the Code

```cpp
struct Ghost {
    std::string name;
    int health;
    int damage;
    std::string dialogue;
    std::string item;
};

std::vector<Ghost> ghosts;
std::vector<std::string> playerRace = { "elf", "dwarf", "goblin", "human" };
std::vector<std::string> itemsAvailable = { "Candle", "Soldier Badge", "Teddy Bear", "Cat Pendant", "Torn Page" };
```

This snippet defines the `Ghost` struct and initializes vectors for storing ghosts, player races, and available items.

Here's a crucial snippet from the inventory header, focusing on the declaration of the `Inventory` class along with its public member functions:

```cpp
class Inventory {
private:
    class Item {
    public:
        std::string itemName;
        Item* _pNext;
    };

    Item* first;
    Item* last;

public:
    Inventory& addItem(std::string item);
    void removeItem(std::string item);
    void showInventory();
    bool isEmpty();
    bool hasItem(std::string);
};
```

In this snippet:

- `Inventory` is a class representing the player's inventory.
- It contains a private nested class `Item`, representing individual items stored in the inventory.
- The `Inventory` class provides public member functions:
  - `addItem`: Adds an item to the inventory.
  - `removeItem`: Removes an item from the inventory.
  - `showInventory`: Displays the contents of the inventory.
  - `isEmpty`: Checks if the inventory is empty.
  - `hasItem`: Checks if a specific item is present in the inventory.

This snippet encapsulates the functionality of the inventory system, allowing for manipulation and management of items within the game.

## Gameplay Example

**Character Creation:**

```
Enter Character's Name: Alice
Enter Character's race
elf
dwarf
goblin
human
Type your race below: 
elf

Enter Character's Sex: Female
```

In this example, the player creates a character named "Alice" belonging to the "elf" race and identified as female.

**Encounter a Ghost:**

```
You start moving forwards...
A Spirit of Shadows! Prepare to fight!

Name: Alice		| Ghost Name: Spirit of Shadows
Health:  100	| Ghost Health: 80
Level: 1	| Ghost Level: 2

1.Attack
2.Block
3.Run
4.Use Candle
```

Upon moving forward, the player encounters a ghost named "Spirit of Shadows" with health 80. The player has options to attack, block, run, or use an item.

**Combat:**

```
1. Attack
2. Block
3. Run
1

Attacking...You did 3000 to the Spirit of Shadows

Name: Alice		| Ghost Name: Spirit of Shadows
Health:  100	| Ghost Health: 50
Level: 1	| Ghost Level: 2

Ghost is Attacking you...
You suffered (-30 points) 70
```

The player chooses to attack, dealing 3000 damage to the ghost. The ghost retaliates, reducing the player's health.

## Instructions to Run the Game

1. Clone the repository containing the game code.
2. Compile the code using a C++ compiler such as g++.
3. Execute the compiled binary to start playing the game.


Enjoy your adventure in the haunted mansion!
