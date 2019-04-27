/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <fstream>
#include "Tree.h"
#include "catch.h"

using namespace std;

	///////////////////////////////////////
	// Hilfsmethoden fürs Menü hier:



	//
	///////////////////////////////////////
int main() {

	//int result = Catch::Session().run();

	///////////////////////////////////////
	// Ihr Code hier:

	std::cout << "==================================" << std::endl
		<< "Person Analyzer v19.84" << std::endl
		<< "1) Datensatz einfuegen, manuell" << std::endl
		<< "2) Datensatz einfuegen, CSV Datei" << std::endl
		<< "3) Datensatz loeschen" << std::endl
		<< "4) Suchen" << std::endl
		<< "5) Datenstruktur anzeigen" << std::endl;

	Tree tree;
	while (true)
	{
		int selection = 0;
		do
		{
			std::cout << "?> ";
			std::cin >> selection;
		} while (selection < 1 || selection > 5);

		switch (selection)
		{
			case 1:
			{
				std::string name;
				int alter = 0, plz = 0;
				double einkommen = .0;
				std::cout << "+ Bitte geben Sie die den Datensatz ein" << std::endl;
				std::cout << "Name ?> ";
				std::cin.ignore();
				std::getline(std::cin, name);
				std::cout << "Alter ?> ";
				std::cin >> alter;
				std::cout << "Einkommen ?> ";
				std::cin >> einkommen;
				std::cout << "PLZ ?> ";
				std::cin >> plz;				
				tree.addNode(name, alter, einkommen, plz);
				std::cout << "+ Ihr Datensatz wurde eingefuegt" << std::endl;
				break;
			}
			case 2:
			{
				char yesNo = 0;			
				do
				{
					std::cout << "+ Moechten Sie die Daten aus der Datei \"ExportZielanalyse.csv\" importieren (j/n) ?> ";
					std::cin >> yesNo;
				} while (yesNo != 'j' && yesNo != 'n');

				if (yesNo == 'j')
				{
					std::ifstream stream("ExportZielanalyse.csv");
					std::string line;
					while (std::getline(stream, line))
					{
						std::string record[4];
						int recordIndex = 0;
						for (unsigned int i = 0; i < line.size(); ++i)
						{
							if (line.at(i) == ';')							
								++recordIndex;							
							else							
								record[recordIndex] += line.at(i);													
						}
						tree.addNode(record[0], std::stoi(record[1]), std::stod(record[2]), std::stoi(record[3]));
					}					
					std::cout << "+ Daten wurden dem Baum hinzugefuegt." << std::endl;
				}
				break;
			}
			case 3:
			{
				int nodePosID = 0;
				std::cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << std::endl;
				std::cin >> nodePosID;
				tree.deleteNode(nodePosID);
				std::cout << "+ Datensatz wurde geloescht." << std::endl; // todo was wenn nicht gefunden?
				break;
			}
			case 4:
			{
				std::string name;
				std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, name);
				std::cout << "+ Fundstellen: " << std::endl;
				tree.searchNode(name);
				break;
			}
			case 5:
			{
				tree.printAll();
				break;
			}
		}
	}

	//
	///////////////////////////////////////
	system("PAUSE");

	return 0;
}
