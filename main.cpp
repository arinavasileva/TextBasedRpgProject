#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "struct_mapping/struct_mapping.h"
#include "Inventory.h"

void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateGhost();
void CreateItem();
void LevelUp();
void InventoryHUD();
void LoadGhosts();
void NewRoom();
void GameEnd();

struct Ghost
{
	std::string name;
	int health;
	int damage;
	std::string dialogue;
	std::string item;
};

struct GhostsData
{
	std::vector<Ghost> ghosts;
};

std::vector<Ghost> ghosts;
std::string currentGhost;
int ghostHp = 0;
int ghostXp = 0;
int ghostLevel = 0;
std::string ghostDialogue;
std::string ghostItem;
int ghostId;

bool isItemsLeft = true; //false if all 5 items are in the player's inventory

std::string name = "", race = "", sex = "";
int level = 0, xp = 0, health = 0, totalHealth = 0, maxHealth = 0, nextLevel, heal = 0;
Inventory inventory;

std::vector<std::string> playerRace = { "elf", "dwarf", "goblin", "human" }; 
std::vector<std::string> itemsAvailable = { "Candle", "Soldier Badge", "Teddy Bear", "Cat Pendant", "Torn Page"};
std::vector<std::string> ghostsAvailable = { "Spirit of Shadows" , "Evil Echo", "Phantom", "Witch", "Demon"};

int main() {
	level = 1;
	xp = 0;
	nextLevel = 76;

	srand(time(NULL));

	LoadGhosts();

	// intro
	std::cout << "\033[1;31mMind Games: A Haunting Escape\033[0m\n\n";
	std::cout << "You wake up in the ancient, haunted mansion nestled deep within the forest.Looking around after a while, you start realizing you are trapped inside by a mysterious force.The only hope of escape lies in unraveling the secrets of the mansion and helping the restless spirits find peace.\n\n";
	std::cout << "Now you must navigate through the mansion's dark corridors, solving puzzles and confronting the ghosts of its past. To break the curse and escape the mansion, you must use the key items they find along the way.\n\n";

	// character creation 
	std::cout << "Enter Character's Name: ";
	std::cin >> name;

	std::cout << "Enter Character's race\n";
	for (const auto& raceOption : playerRace) {
		std::cout << raceOption << "\n";
	}
	std::cout << "Type your race below: \n\n";
	std::cin >> race;

	std::transform(race.begin(), race.end(), race.begin(), ::tolower);

	health = 100; // Default health value
	auto it = std::find(playerRace.begin(), playerRace.end(), race);
	if (it != playerRace.end()) {
		switch (it - playerRace.begin()) {
		case 0:
			health = 80;
			break;
		case 1:
			health = 120;
			break;
		case 2:
			health = 110;
			break;
		case 3:
			health = 90;
			break;
		}
	}

	std::cout << "\n";
	std::cout << "Enter Character's Sex: ";
	std::cin >> sex;

	for (int i = 0; i < 3; i++) {
		if (i == 0)
			std::cout << "Character Creation is in Progress.\n ";
		if (i == 1)
			std::cout << "Character Creation is in Progress..\n ";
		if (i == 2)
			std::cout << "Character Creation is in Progress...\n ";

		Sleep(1000);
		system("cls");
	}

	name[0] = toupper(name[0]);
	race[0] = toupper(race[0]);
	sex[0] = toupper(sex[0]);

	//health = 100;
	totalHealth = health;
	maxHealth = totalHealth;

	inventory.addItem("Sword");
	
	HUD();
	Moving();

	system("pause");

	return 0;

}

void LoadGhosts() {
	struct_mapping::reg(&Ghost::name, "name");
	struct_mapping::reg(&Ghost::health, "health");
	struct_mapping::reg(&Ghost::damage, "damage");
	struct_mapping::reg(&Ghost::dialogue, "dialogue");
	struct_mapping::reg(&Ghost::item, "item");
	struct_mapping::reg(&GhostsData::ghosts, "ghosts");

	std::ifstream json_data("ghosts.json");

	if (json_data)
	{
		GhostsData data;

		struct_mapping::map_json_to_struct(data, json_data);
		ghosts = data.ghosts;

		json_data.close();
	}
}

void HUD() {
	Sleep(500);
	system("cls");
	std::cout << "Name: " << name << "      Health: " << totalHealth << "\nRace: " << race
		<< "\nSex: " << sex << "\nLevel: " << level << "\nXP: " << xp << "\nXP to Level: " << nextLevel << std::endl;
	InventoryHUD();

	if (ghostsAvailable.empty()) {
		GameEnd();
	}
	Moving();
}

void CombatHUD() {
	Sleep(500);
	system("cls");
	std::cout << "Name: " << name << "		| Ghost Name: " << currentGhost << "\nHealth:  " << totalHealth << "	| Ghost Health: " <<
		ghostHp << "\nLevel: " << level << "	| Ghost Level: " << ghostLevel << std::endl;
	InventoryHUD();
	std::cout << "\n";
	std::cout << ghostDialogue << "\n\n";
}

void Combat() {

	CombatHUD();
	int playerAttack;
	//int playerDamage = 8 * level / 2;
	int playerDamage = 3000;
	int ghostAttack = 6 * ghostLevel / 2;

	if (totalHealth >= 1 && ghostHp >= 1) {	
		std::cout << "\n";
		std::cout << "1.Attack\n";
		std::cout << "2.Block\n";
		std::cout << "3.Run\n";
		if (inventory.hasItem(ghostItem)) { // not called every time it should be
			std::cout << "4.Use " << ghostItem << std::endl;
		}
		std::cout << "\n";
		std::cin >> playerAttack;

		//Attack
		if (playerAttack == 1) {
			std::cout << "Attacking...You did " << playerDamage << " to the " << currentGhost << std::endl;
			ghostHp = ghostHp - playerDamage;
			Sleep(1000);
			CombatHUD();
			if (ghostHp >= 1) {
				std::cout << "\n";
				std::cout << "Ghost is Attacking you...\n";
				totalHealth = totalHealth - ghostAttack;
				std::cout << "You suffered (-" << ghostAttack << " points) " << totalHealth << std::endl;
				//change to function
				if (totalHealth <= 0) {
					totalHealth = 0; 
					system("cls");
					std::cout << "You died\nYou were level: " << level << "you got killed by" << currentGhost << std::endl;
					Sleep(2000);
					exit(0);

				}
			}
			else if (ghostHp <= 0) {
				ghostHp = 0;
		
				LevelUp();
				std::cout << "\n";
				std::cout << "You fought off the " << currentGhost << ". You have been rewarded with " << ghostXp << "XP.\nGood job!";
				Sleep(3000);
				HUD();
			} 
			Sleep(3000);
			Combat();

		}
		//Block
		else if (playerAttack == 2) {
			std::cout << "Blocking\n";
			int i = rand() % 100 + 1;
			if (i >= 50) {
				std::cout << "You blocked the incoming attack\n";
				heal = level * 10 / 2;
				std::cout << "You have been healed (+ " << heal << " points)" << std::endl;
				totalHealth += heal;
				Sleep(3000);
				Combat();
			}
			else {
				std::cout << "You failed to block the upcoming attack\n";
				totalHealth -= ghostAttack;
				std::cout << "The ghost put a magic curse on you! (- " << ghostAttack << " points). Current hp now is " << totalHealth << std::endl;
				Sleep(3000);
				Combat();
			}
		}

		//Run
		else if (playerAttack == 3) {
			std::cout << "You are trying to escape...\n";
			int x = rand() % 100 + 1;
			if (x >= 50) {
				std::cout << "You ran away!\n";
				HUD();
			}
			else {
				std::cout << "You failed to escape!\n";
				std::cout << "Ghost is attacking you!\n";
				totalHealth -= ghostAttack + 10;
				std::cout << "You suffered (- " << ghostAttack + 10 << " points). Your current health is " << totalHealth << std::endl;
				Sleep(5000);
				Combat();
			}
		}
		//Item
		else if (playerAttack == 4) {
			std::cout << "You use the " << ghostItem << ".\n";
			inventory.removeItem(ghostItem);
			std::cout << "The ghost thanks you. \n";

			LevelUp();
			std::cout << "\n";
			std::cout << "You freed the " << currentGhost << ". You have been rewarded with " << ghostXp << "XP.\nGood job!";
			ghostsAvailable.erase(std::next(ghostsAvailable.begin(), ghostId));
			Sleep(3000);
			HUD();
		}

		if (totalHealth <= 1) {
			system("cls");
			std::cout << "You died\nYou were level: " << level << ". You got killed by" << currentGhost << std::endl;
			Sleep(3000);
			exit(0);

		}

		else {
			std::cout << "Invalid Input\n";
			Sleep(700);
			Combat();
		}

	}
	if (ghostHp <= 1) {
		HUD();
		LevelUp();
		std::cout << "\n";
		std::cout << "You fought off " << currentGhost << ". You have been rewarded with " << ghostXp << " XP.\nGood job!";
		Sleep(3000);
	}
	
}

void Moving() {

	int choice;
	std::cout << "\n\n";
	std::cout << "1. Move Forward \n";
	std::cout << "2. Move Backwards \n";
	std::cout << "3. Move Right \n";
	std::cout << "4. Move Left \n";
	std::cout << "5. Rest \n";
	std::cout << "\n\n";

	std::cin >> choice;

	if (choice == 1) {
		std::cout << "You start moving forwards...\n";
		NewRoom();

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();
	}
	else if (choice == 2) {
		std::cout << "You start moving backwards...\n";
		NewRoom();

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();
	}
	else if (choice == 3) {
		std::cout << "You start moving to the right...\n";
		NewRoom();

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();
	}
	else if (choice == 4) {
		std::cout << "You start moving to the left...\n";
		NewRoom();

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();
	}
	else if (choice == 5) {
		std::cout << "It is time to rest in the closest corner.\n";
		if (totalHealth <= 99) {
			totalHealth += 10 * level;
		}
		std::cout << "You healed by resting. Your health is now " << totalHealth << std::endl;
		Sleep(2000);
		HUD();
	}
	else {
		std::cout << "Invalid Input\n";
		Sleep(700);
		Moving();
	}
}

void LevelUp() {
	xp = xp + ghostXp;

	if (xp >= nextLevel) {
		level++;
		nextLevel = nextLevel * 3 / 2;
		totalHealth = totalHealth + 20;
		maxHealth = totalHealth;
		std::cout << "Level Up! You are now level " << level << std::endl;
		std::cout << "Your total health increased by 20 points. Total health now is " << totalHealth << std::endl;
		Sleep(1500);
		HUD();
	}
}

void CreateGhost() {
	int ghostId = rand() % ghosts.size();
	Ghost ghost = ghosts[ghostId];

	currentGhost = ghost.name;
	ghostLevel = (rand() % 3) + level;
	ghostHp = ghost.health;
	ghostXp = ghost.damage;
	ghostDialogue = ghost.dialogue;
	ghostItem = ghost.item;
}

void InventoryHUD() {

	inventory.showInventory();
}

void CreateItem() {
	if (itemsAvailable.empty()) {
		isItemsLeft = false;
		return;
	}
	int itemID = rand() % itemsAvailable.size();

	std::string roomItem = itemsAvailable[itemID];
	std::cout << "You find a " << roomItem << ". Do you want to pick it up?"<< std::endl;

	int choice;
	std::cout << "\n\n";
	std::cout << "1. Pick up the item \n";
	std::cout << "2. Leave the item \n";
	std::cout << "\n\n";
	Sleep(500);

	std::cin >> choice;
	if (choice == 1) {
		inventory.addItem(roomItem);
		std::cout << "You pick up the " << roomItem << std::endl;
		itemsAvailable.erase(std::next(itemsAvailable.begin(), itemID));
	}
	HUD();
}

void NewRoom() {
	int temp = rand() % 100 + 1;
	if (isItemsLeft) {
		if (temp <= 30) {
			// Find Item
			CreateItem();
		}
		if (temp >= 60) {
			// Encounter a Ghost
			CreateGhost();
			std::cout << "A " << currentGhost << "! Prepare to fight!\n";
			Sleep(1000);
			Combat();
		}
	}
	else {
		if (temp >= 50) {
			// Encounter a Ghost
			CreateGhost();
			std::cout << "A " << currentGhost << "! Prepare to fight!\n";
			Sleep(1000);
			Combat();
		}
	}

}

void GameEnd() {
	//text here
}