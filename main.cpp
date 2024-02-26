#include <iostream>
#include <windows.h>
#include <string>


void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateGhost();

std::string name = "", race = "", sex = "";
int level = 0, xp = 0, health = 0, totalHealth = 0, maxHealth = 0, nextLevel, heal = 0;
int ghostHp = 0;
int ghostXp = 0;
int ghostLevel = 0;

std::string ghostName[] = { "Ghastly Gale", "Soul Shroud", "Wandering Wight" }; // subject to change
std::string currentghost = "";

int main() {
	level = 1;
	xp = 0;
	nextLevel = 10;
	health = 100;
	totalHealth = health;
	maxHealth = totalHealth;

	// character creation 

	std::cout << "Enter Character's Name: ";
	std::cin >> name;

	std::cout << "Enter Character's Race: ";
	std::cin >> race;

	std::cout << "Enter Character's Sex: ";
	std::cin >> sex;

	std::cout << "Character Creation is in Progress.\n ";
	Sleep(1000);
	system("cls");

	std::cout << "Character Creation is in Progress..\n ";
	Sleep(1500);
	system("cls");

	std::cout << "Character Creation is in Progress...\n ";
	Sleep(1900);
	system("cls");

	HUD();
	Moving();

	system("pause");

	return 0;

}

void HUD() {
	Sleep(500);
	system("cls");
	std::cout << "Name: " << name << "      Health:  " << totalHealth << "\nRace:  " << race
		<< "\nSex: " << sex << "\nLevel: " << xp << "\nXP: " << xp << "\nXP to Level: " << nextLevel << std::endl;
}

void Moving() {

	int choice;

	std::cout << "1. Move Forward \n";
	std::cout << "2. Move Backwards \n";
	std::cout << "3. Move Right \n";
	std::cout << "4. Move Left \n";
	std::cout << "5. Rest \n";
	std::cout << "\n\n";

	std::cin >> choice;

	if (choice == 1) {

	}
	else if (choice == 2) {

	}
	else if (choice == 3) {

	}
	else if (choice == 4) {

	}
	else if (choice == 5) {

	}
	else {
		std::cout << "Invalid Input\n";
		Sleep(700);
		Moving();
	}
}