/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.hpp"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:

	/*Ring* nRing = new Ring();
	nRing->addNode("test1", "test1");
	nRing->addNode("test2", "test2");
	nRing->addNode("test3", "test3");
	nRing->addNode("test4", "test4");
	nRing->addNode("test5", "test5");
	nRing->addNode("test6", "test6");
	delete nRing;*/

	Ring ring;	
	std::cout << "OneRingToRuleThemAll v0.1" << std::endl
		<< "==================================" << std::endl
		<< "1) Backup einfuegen" << std::endl
		<< "2) Backup suchen" << std::endl
		<< "3) Alle Backups ausgeben" << std::endl;

	while (true)
	{
		int selection = 0;
		do
		{
			std::cout << "?> ";
			std::cin >> selection;
		} while (selection < 1 || selection > 3);

		switch (selection)
		{
			case 1:
			{
				std::string description, data;
				std::cout << "+Neuen Datensatz einfuegen" << std::endl;			
				std::cout << "Beschreibung ?> ";
				std::cin.ignore();
				std::getline(std::cin, description);
				std::cout << "Daten ?>";
				std::getline(std::cin, data);				
				ring.addNode(description, data);
				std::cout << "+Ihr Datensatz wurde hinzugefuegt." << std::endl;
				break;
			}
			case 2:
			{
				std::string data;
				std::cout << "+Nach welchen Daten soll gesucht werden?" << std::endl
					<< "?> ";
				std::cin.ignore();
				std::getline(std::cin, data);				
				ring.search(data);					
				break;
			}			
			case 3:
			{
				ring.print();
				break;
			}				
		}
	}

	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
