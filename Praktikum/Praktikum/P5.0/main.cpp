#include <iostream>
#include <string>
#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "graph.h"

int main()
{
	Catch::Session().run();

	Graph grap;	
	int input = 0;
	do 
	{
		std::cout << "###################################" << std::endl
			<< "Working on Grphs. Please choose:" << std::endl
			<< "1) Graph einlesen" << std::endl
			<< "2) Tiefensuche" << std::endl
			<< "3) Breitensuche" << std::endl
			<< "4) Prim" << std::endl
			<< "5) Kruskal" << std::endl
			<< "6) Print Graph" << std::endl
			<< "0 zum beenden" << std::endl
			<< "?> ";

		std::cin >> input;
		switch (input)
		{	
			case 1:
			{
				std::string filename;
				std::cout << "Dateinamen eingeben: ";
				std::cin >> filename;
				grap.init(filename);
				break;
			}
			case 2:
			{
				int startKey;
				std::cout << "Start Key: ";
				std::cin >> startKey;				
				if (grap.depthSearchRek(startKey))
					std::cout << "Tiefensuche erfolgreich!" << std::endl;
				else
					std::cout << "Tiefensuche nicht erfolgreich!" << std::endl;
				break;
			}
			case 3:
			{
				int startKey;
				std::cout << "Start Key: ";
				std::cin >> startKey;
				if (grap.breadthSearchIter(startKey))
					std::cout << "Breitensuche erfolgreich!" << std::endl;
				else
					std::cout << "Breitensuche nicht erfolgreich!" << std::endl;
				break;
			}
			case 4:
			{
				int startKey;
				std::cout << "Start Key: ";
				std::cin >> startKey;
				double value = grap.prim(startKey);	
				std::cout << "Prim kosten minimaler Spannbaum: " << value << std::endl;
				break;
			}
			case 5:
			{
				double value = grap.kruskal();
				std::cout << "Kruskal kosten minimaler Spannbaum: " << value << std::endl;
				break;
			}
			case 6:	
			{
				grap.printAll();
				break;
			}
		}
	} while (input != 0);	
}