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
int currentGhostNames = 2;
std::string currentghost = " ";

int main() {
	level = 1;
	xp = 0;
	nextLevel = 76;
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
		<< "\nSex: " << sex << "\nLevel: " << level << "\nXP: " << xp << "\nXP to Level: " << nextLevel << std::endl;
	Moving();
}

void CombatHUD() {
	Sleep(500);
	system("cls");
	std::cout << "Name: " << name << "		| Ghost Name: " << currentghost << "\nHealth:  " << totalHealth << "	| Ghost Health: " <<
		ghostHp << "\nLevel: " << level << "	| Ghost Level: " << ghostLevel << std::endl;
	Moving();
}

void Combat() {

	CombatHUD();
	int playerAttack;
	int playerDamage = 8 * level / 2;
	int ghostAttack = 6 * ghostLevel / 2;

	if (totalHealth >= 1 && ghostHp >= 1) {	
		std::cout << "\n";
		std::cout << "1.Attack\n";
		std::cout << "2.Block\n";
		std::cout << "3.Run\n";
		std::cout << "\n";
		std::cin >> playerAttack;

		//Attack
		if (playerAttack == 1) {
			std::cout << "Attacking...You did " << playerDamage << " to the " << currentghost << std::endl;
			ghostHp = ghostHp - playerDamage;
			Sleep(1000);
			CombatHUD();
			if (ghostHp >= 1) {
				std::cout << "\n";
				std::cout << "Ghost is Attacking you...\n";
				totalHealth = totalHealth - ghostAttack;
				std::cout << "You suffered " << ghostAttack << " hp " << totalHealth << std::endl;
				//change to function
				if (totalHealth <= 0) {
					totalHealth = 0;
				}
			}
			else if (ghostHp <= 0) {
				ghostHp = 0;
			}
			Sleep(1000);
			Combat();

		}
		//Block
		else if (playerAttack == 2) {
			std::cout << "Blocking\n";
			int i = rand() % 100 + 1;
			if (i >= 50) {
				std::cout << "You blocked the incoming attack\n";
				heal = level * 10 / 2;
				std::cout << "You have been healed for " << heal << std::endl;
				totalHealth += heal;
				Sleep(1000);
				Combat();
			}
			else {
				std::cout << "You failed to block the upcoming attack\n";
				totalHealth -= ghostAttack;
				std::cout << "The ghost put a magic curse on you " << ghostAttack << " current hp " << totalHealth << std::endl;
				Sleep(1000);
				Combat();
			}
		}

		//Run
		else if (playerAttack == 3) {
			std::cout << "You are trying to escape\n";
			int x = rand() % 100 + 1;
			if (x >= 50) {
				std::cout << "You ran away\n";
				HUD();
			}
			else {
				std::cout << "You failed to escape\n";
				std::cout << "Ghost is attacking you!\n";
				totalHealth -= ghostAttack + 10;
				std::cout << "You suffered " << ghostAttack + 10 << "Your current helath is " << totalHealth << std::endl;
				Sleep(1000);
				Combat();
			}
		}

		else {
			std::cout << "Invalid Input\n";
			Sleep(700);
			Combat();
		}

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
		int temp = rand() % 100 + 1;
		std::cout << "You start moving forward...\n";
		if (temp >= 50) {
			// Encounter a Ghost
			CreateGhost();
			std::string tempName = ghostName[rand() % currentGhostNames];
			std::cout << "A " << tempName << "! Prepare to fight!\n";
			currentghost = tempName;
			Sleep(1000);
			Combat();

		}

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();

	}
	else if (choice == 2) {
		int temp = rand() % 100 + 1;
		std::cout << "You start moving backwards...\n";
		if (temp >= 50) {
			// Encounter a Ghost
			CreateGhost();
			std::string tempName = ghostName[rand() % currentGhostNames];
			std::cout << "A " << tempName << "! Prepare to fight!\n";
			currentghost = tempName;
			Sleep(1000);
			Combat();
		}

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();

	}
	else if (choice == 3) {
		int temp = rand() % 100 + 1;
		std::cout << "You start moving to the right...\n";
		if (temp >= 50) {
			// Encounter a Ghost
			CreateGhost();
			std::string tempName = ghostName[rand() % currentGhostNames];
			std::cout << "A " << tempName << "! Prepare to fight!\n";
			currentghost = tempName;
			Sleep(1000);
			Combat();
		}

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();

	}
	else if (choice == 4) {

		int temp = rand() % 100 + 1;
		std::cout << "You start moving to the left...\n";
		if (temp >= 50) {
			// Encounter a Ghost
			CreateGhost();
			std::string tempName = ghostName[rand() % currentGhostNames];
			std::cout << "A " << tempName << "! Prepare to fight!\n";
			currentghost = tempName;
			Sleep(1000);
			Combat();
		}

		std::cout << "You found nothing\n";
		Sleep(1000);
		HUD();

	}
	else if (choice == 5) {
		std::cout << "It is time to rest in the closest corner\n";
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

void CreateGhost() {

	int ghostHp = 30;
	int ghostLevel = (rand() % 3) + level;

	//if (ghostLevel == 0) {
	//	ghostLevel = (rand() % 3) + level;
	//}

	// The value will be modified later 
	ghostHp = (rand() % 30) * totalHealth;

	//if (ghostHp == 0) {
	//	ghostHP = = (rand() % 30) * totalHealth;
	//}

	ghostXp = ghostHp;

	if (ghostHp == 0)
		CreateGhost();
	if (ghostLevel == 0)
		CreateGhost();
}

