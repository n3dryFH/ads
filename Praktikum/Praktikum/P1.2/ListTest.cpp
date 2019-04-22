/*************************************************
* ADS Praktikum 1.1
* Unit-Testdatei
* Änderungen fürs Praktikum untersagt!
*************************************************/
#include "catch.hpp"
#include "List.h"
#include "Node.h"
#include <string>

using namespace std;

// Friend-Methode fuer Testroutine
Node<int>* get_anker(List<int>& l) {
	return l.head_tail;
}

int get_AnzahlNodes(List<int>& l) {
	return l.list_size;
}

TEST_CASE("List Testing", "[List]") {

	List<int> test_list;
	List<int> second;

	SECTION("Hinzufuegen und Suche von Nodes - simple") {
		test_list.insertFront(5);
		test_list.insertFront(7);

		test_list.insertBack(9);
		test_list.insertBack(4);

		REQUIRE(test_list.size() == 4);

		REQUIRE(test_list.search(7) == true);
		REQUIRE(test_list.search(8) == false);
		REQUIRE(test_list.search(3) == false);
		REQUIRE(test_list.search(9) == true);

		int key;
		test_list.getBack(key);
		REQUIRE(key == 4);
		test_list.getFront(key);
		REQUIRE(key == 7);
	}

	SECTION("Hinzufuegen von Nodes aus zweiter Liste am Ende") {
		test_list.insertFront(5);
		test_list.insertFront(7);

		test_list.insertBack(9);
		test_list.insertBack(4);

		second.insertFront(5);
		second.insertFront(5);

		second.insertBack(5);
		second.insertBack(5);

		test_list.insertBack(second);

		REQUIRE(test_list.size() == 8);		
		
		Node<int>* tmp = get_anker(test_list);
		tmp = tmp->next;
		int key = tmp->key;
		REQUIRE(key == 7);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 9);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 4);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);
		
		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		for (int i = 0; i < 8; i++)
			tmp = tmp->prev;

		//head_tail wieder erreicht
		key = tmp->key;
		REQUIRE(key == 0);
	}

	SECTION("Hinzufuegen von Nodes aus zweiter Liste am Anfang") {
		test_list.insertFront(5);
		test_list.insertFront(7);
		test_list.insertBack(9);

		second.insertFront(5);
		second.insertFront(5);
		second.insertBack(5);

		test_list.insertFront(second);

		REQUIRE(test_list.size() == 6);

		Node<int>* tmp = get_anker(test_list);
		tmp = tmp->next;
		int key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 7);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 5);

		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 9);

		for (int i = 0; i < 6; i++)
			tmp = tmp->prev;

		//head_tail wieder erreicht
		key = tmp->key;
		REQUIRE(key == 0);
	}

	SECTION("Hinzufuegen und Loeschen von Nodes - simpel") {
		test_list.insertFront(5);
		test_list.insertFront(7);
		test_list.insertFront(9);
		test_list.insertFront(4);

		test_list.insertBack(3);
		test_list.insertBack(2);
		test_list.insertBack(4);
		test_list.insertBack(1);

		REQUIRE(test_list.size() == 8);

		REQUIRE(test_list.del(8) == false);
		REQUIRE(test_list.del(4) == true);
		REQUIRE(test_list.del(1) == true);
		REQUIRE(test_list.del(5) == true);

		REQUIRE(test_list.size() == 5);

		int key;
		test_list.getBack(key);
		REQUIRE(key == 4);
		test_list.getFront(key);
		REQUIRE(key == 9);
	}

	SECTION("Vertauschen von zwei Elementen und testen der Zeiger") {
		test_list.insertFront(5);
		test_list.insertFront(7);
		test_list.insertFront(9);
		test_list.insertFront(4);

		test_list.insertBack(3);
		test_list.insertBack(2);
		test_list.insertBack(4);
		test_list.insertBack(1);

		REQUIRE(test_list.size() == 8);
		//////////////////////////////////////////////////////////////
		//Fall 1: Zwei Knoten aus der Mitte, nicht nebeneinander	//
		//////////////////////////////////////////////////////////////
		REQUIRE(test_list.swap(7, 2) == true);
		Node<int>* tmp = get_anker(test_list);
		//prüfe ob 2 an neuem Platz
		for (int i = 0; i < 3; i++)
			tmp = tmp->next;
		int key = tmp->key;
		REQUIRE(key == 2);
		//Prüfe ob 7 an neuem Platz
		for (int i = 0; i < 3; i++)
			tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 7);
		tmp = tmp->next;
		//Prüfe ob Anker wieder erreichbar
		for (int i = 0; i < 7; i++)
			tmp = tmp->prev;
		key = tmp->key;
		REQUIRE(key == 0);

		//////////////////////////////////////////////////////////////////////////
		//Fall 2: Erster Knoten mit einem aus der Mitte, nicht nebeneinander	//
		//////////////////////////////////////////////////////////////////////////
		REQUIRE(test_list.swap(4, 5) == true);
		tmp = tmp->next;
		//Prüfe ob neuer erster richtig
		key = tmp->key;
		REQUIRE(key == 5);
		//Prüfe ob 4 an neuem Platz
		for (int i = 0; i < 3; i++)
			tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 4);
		tmp = tmp->next;
		//Prüfe ob Anker wieder erreichbar
		for (int i = 0; i < 5; i++)
			tmp = tmp->prev;
		key = tmp->key;
		REQUIRE(key == 0);

		//////////////////////////////////////////////////////////////////////////
		//Fall 3: Letzter Knoten mit einem aus der Mitte, nicht nebeneinander	//
		//////////////////////////////////////////////////////////////////////////
		REQUIRE(test_list.swap(1, 3) == true);
		for(int i = 0; i < 5; i++)
			tmp = tmp->next;
		//Prüfe ob 1 an neuem Platz
		key = tmp->key;
		REQUIRE(key == 1);
		//Prüfe ob neuer letzter richtig
		for (int i = 0; i < 3; i++)
			tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 3);
		tmp = tmp->next;
		//Prüfe ob Anker wieder erreichbar
		for (int i = 0; i < 9; i++)
			tmp = tmp->prev;
		key = tmp->key;
		REQUIRE(key == 0);

		//////////////////////////////////////////////////////
		//Fall 4: Zwei Knoten aus der Mitte, nebeneinander	//
		//////////////////////////////////////////////////////
		REQUIRE(test_list.swap(2, 4) == true);
		for (int i = 0; i < 3; i++)
			tmp = tmp->next;
		//Prüfe ob 4 an neuem Platz
		key = tmp->key;
		REQUIRE(key == 4);
		//Prüfe ob 1 an neuem Platz
		tmp = tmp->next;
		key = tmp->key;
		REQUIRE(key == 2);
		tmp = tmp->next;
		//Prüfe ob Anker wieder erreichbar
		for (int i = 0; i < 5; i++)
			tmp = tmp->prev;
		key = tmp->key;
		REQUIRE(key == 0);		
	}
}

TEST_CASE("Custom List Testing", "[List]") {
	List<int> test_list;
	SECTION("Vertauschen Head Knoten mit Tail Knoten") {
		test_list.insertFront(5);
		test_list.insertFront(7);
		test_list.insertFront(9);
		test_list.insertFront(4);

		REQUIRE(test_list.size() == 4);
		Node<int>* anker = get_anker(test_list);
		Node<int>* headNext = anker->next->next;
		Node<int>* tailPrev = anker->prev->prev;
		REQUIRE(test_list.swap(4, 5) == true);
		REQUIRE(get_anker(test_list)->next->key == 5);
		REQUIRE(get_anker(test_list)->prev->key == 4);
		REQUIRE(get_anker(test_list)->prev->prev == tailPrev);
		REQUIRE(get_anker(test_list)->next->next == headNext);
	}
	SECTION("Swap mit einem Element") {
		test_list.insertFront(5);
		REQUIRE(test_list.size() == 1);
		Node<int>* anker = get_anker(test_list);
		REQUIRE(test_list.swap(5, 5) == false);
		REQUIRE(anker->next == anker->prev);
	}
	SECTION("getFront und getBack") {
		test_list.insertFront(5);
		test_list.insertBack(4);
		REQUIRE(test_list.size() == 2);
		int key;
		REQUIRE(test_list.getBack(key) == true);
		REQUIRE(test_list.size() == 1);
		REQUIRE(key == 4);
		REQUIRE(test_list.getBack(key) == true);
		REQUIRE(test_list.size() == 0);
		REQUIRE(key == 5);
	}
	SECTION("nullptr und selbes objekt sicher") {
		test_list.insertFront(5);
		test_list.insertFront(test_list);
		test_list.insertFront(&test_list);
		test_list.insertFront(nullptr);
		test_list.insertBack(nullptr);
		test_list.insertBack(test_list);
		test_list.insertBack(&test_list);
		REQUIRE(test_list.size() == 1);
	}
	SECTION("leere liste element löschen") {
		REQUIRE(test_list.size() == 0);
		REQUIRE(test_list.del(4) == false);
	}
}