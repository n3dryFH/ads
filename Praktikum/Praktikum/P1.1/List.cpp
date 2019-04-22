#include "List.h"

List::List()
{
	// Konstruktor für eine leere Liste
	head_tail = new Node;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

List::List(const List & _List)
{
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

List::List(const List * _List)
{
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

List::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
/*
	hier alle Knoten löschen, die im Objekt List allokiert wurden
*/
	
	Node* node = head_tail->next;
	while (node != head_tail)
	{
		Node* tmpPtr = node->next;
		delete node;
		node = tmpPtr;
	}	

	delete head_tail;
	head_tail = nullptr;	
}

void List::insertFront(int key)
{
	// Einfügen eines neuen Knotens am Anfang der Liste
/*
	Einen neuen Knoten mit dem Schlüsselwert key am Anfang der Liste einfügen
*/
	Node* node = new Node(key, head_tail->next, head_tail); // add new node before current head
	head_tail->next->prev = node; // set prev of current head to new node
	head_tail->next = node; // set current head to new node
	++list_size; // increase list size by 1
}

void List::insertFront(List & _List)
{
	// Einfügen einer vorhandenen Liste am Anfang
	/*	
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
*/
	if (_List.head_tail->next != _List.head_tail->prev) // check for empty list
	{
		head_tail->next->prev = _List.head_tail->prev; // set prev of current head to last node of the added list
		_List.head_tail->prev->next = head_tail->next; // from the added list, set the next from tail to the current head
		head_tail->next = _List.head_tail->next; // set current head to the head of the added list
		head_tail->next->prev = head_tail; // set prev of current head to head_tail
		list_size += _List.list_size; // incrase current list size by the size of the added list
		_List.head_tail->next = _List.head_tail->prev = _List.head_tail; // clear/reset head_tail from added list
		_List.list_size = 0; 
	}
}

void List::insertFront(List * _List)
{
	// Einfügen einer vorhandenen Liste am Anfang
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 	
	*/
/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
*/
	if (_List->head_tail->next != _List->head_tail->prev) // check for empty list
	{
		head_tail->next->prev = _List->head_tail->prev; // set prev of current head to last node of new list
		_List->head_tail->prev->next = head_tail->next; // from the new list, set the next from tail to the current head
		head_tail->next = _List->head_tail->next; // set current head to the head of the added list
		head_tail->next->prev = head_tail; // set prev of current head to head_tail
		list_size += _List->list_size; // incrase current list size by the size of the new list
		_List->head_tail->next = _List->head_tail->prev = _List->head_tail; // clear/reset head_tail from _List
		_List->list_size = 0;
	}
}

void List::insertBack(int key)
{
	// Einfügen eines neuen Knotens am Ende der Liste
/*
	Einen neuen Knoten mit dem Schlüsselwert key am Ende der Liste einfügen
*/
	Node* node = new Node(key, head_tail, head_tail->prev); // add new node after current tail
	head_tail->prev->next = node; // set next of current tail to the new node
	head_tail->prev = node; // set current head to new node
	++list_size; // increase list size by 1
}

void List::insertBack(List & _List)
{
	// Einfügen einer vorhandenen Liste am Ende
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/
	if (_List.head_tail->next != _List.head_tail->prev) // check for empty list
	{
		head_tail->prev->next = _List.head_tail->next; // set next of the current tail to the head of the new list
		_List.head_tail->next->prev= head_tail->prev; // from the new list, set the next from tail to the current head
		head_tail->prev = _List.head_tail->prev; // set current tail to the tail of the added list
		head_tail->prev->next = head_tail; // set next of current tail to head_tail
		list_size += _List.list_size; // incrase current list size by the size of the new list
		_List.head_tail->next = _List.head_tail->prev = _List.head_tail; // clear/reset head_tail from the added list
		_List.list_size = 0;
	}
}

void List::insertBack(List * _List)
{
	// Einfügen einer vorhandenen Liste am Ende
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/
	if (_List->head_tail->next != _List->head_tail->prev) // check for empty list
	{
		head_tail->prev->next = _List->head_tail->next; // set next of the current tail to the head of the new list
		_List->head_tail->next->prev = head_tail->prev; // from the new list, set the next from tail to the current head
		head_tail->prev = _List->head_tail->prev; // set current tail to the tail of the added list
		head_tail->prev->next = head_tail; // set next of current tail to head_tail
		list_size += _List->list_size; // incrase current list size by the size of the new list
		_List->head_tail->next = _List->head_tail->prev = _List->head_tail; // clear/reset head_tail from the added list
		_List->list_size = 0;
	}
}

bool List::getFront(int & key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen
/*
	Der Wert des vorderen Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(key) darf nicht zum löschen benutzt werden.
*/
	if (head_tail->prev == head_tail->next) // check for empty list
		return false;
	
	const Node* currentHead = head_tail->next;
	key = currentHead->key;
	head_tail->next = currentHead->next;
	head_tail->next->prev = head_tail;
	delete currentHead;
	currentHead = nullptr;
	--list_size;
	return true;
}

bool List::getBack(int & key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen
/*
	Der Wert des letzten Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
	Die Methode del(key) darf nicht zum löschen benutzt werden.
*/
	if (head_tail->prev == head_tail->next) // check for empty list
		return false;

	const Node* currentTail = head_tail->prev;
	key = currentTail->key;
	head_tail->prev = currentTail->prev;
	head_tail->prev->next = head_tail;
	delete currentTail;
	currentTail = nullptr;
	--list_size;
	return true;	
}

bool List::del(int key)
{
	// Löschen eines gegebenen Knotens
/*
	Löschen des Knotens mit dem Schlüssel key
*/
	if (head_tail->prev == head_tail->next) // check for empty list
		return false;

	for (Node* ptr = head_tail->next; ptr != head_tail; ptr = ptr->next)
	{
		if (ptr->key == key)
		{
			if (head_tail->next == ptr) // delete head
			{
				head_tail->next = head_tail->next->next;
				head_tail->next->prev = head_tail;				
			}
			else if (head_tail->prev == ptr) // delete tail
			{
				head_tail->prev = head_tail->prev->prev;
				head_tail->prev->next = head_tail;				
			}
			else
			{				
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
			}
			delete ptr;
			ptr = nullptr;
			--list_size;
			return true;
		}
	}

	return false;
}

bool List::search(int key)
{
	// suchen eines Knotens
/*
	suchen ob ein Knoten mit dem Schlüssel key existiert.
*/
	for (Node* ptr = head_tail->next; ptr != head_tail; ptr = ptr->next)
		if (ptr->key == key)
			return true;
	return false;
}

bool List::swap(int key1, int key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn verändert.
/*
	Vertauschen von zwei Knoten mit dem key1 und dem key2
	Es dürfen nicht nur einfach die Schlüssel in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuhängen.
*/

	if (key1 == key2 || list_size < 2)
		return false;	

	Node* leftNodePtr = nullptr, *rightNodePtr = nullptr;
	for (Node* ptr = head_tail->next; ptr != head_tail; ptr = ptr->next)
	{
		if (ptr->key == key1 || ptr->key == key2)
		{
			if (leftNodePtr)
			{
				rightNodePtr = ptr;
				break;
			}
			else
				leftNodePtr = ptr;			
		}			

	}	

	if (!leftNodePtr || !rightNodePtr)
		return false;

	Node* rightNext = rightNodePtr->next;
	Node* rightPrev = rightNodePtr->prev;
	bool bAreNeighbours = leftNodePtr->next == rightNodePtr;

	/********************* swap right to left node **********************/
	if (bAreNeighbours)	
		rightNodePtr->next = leftNodePtr;	
	else
	{
		rightNodePtr->next = leftNodePtr->next;	 	
		rightNodePtr->next->prev = rightNodePtr; 
	}

	if (leftNodePtr == head_tail->next) // check for head		
	{
		rightNodePtr->prev = head_tail;
		head_tail->next = rightNodePtr;
	}
	else
	{
		rightNodePtr->prev = leftNodePtr->prev;
		leftNodePtr->prev->next = rightNodePtr;
	}

	/********************* swap left to right node **********************/
	if (bAreNeighbours)	
		leftNodePtr->prev = rightNodePtr;	
	else
	{
		leftNodePtr->prev = rightPrev;
		leftNodePtr->prev->next = leftNodePtr;
	}
	
	if (rightNodePtr == head_tail->prev) // check for tail
	{
		leftNodePtr->next = head_tail;
		head_tail->prev = leftNodePtr;
	}
	else
	{
		leftNodePtr->next = rightNext;
		rightNext->prev = leftNodePtr;
	}	
	   	 
	return true;
}

int List::size(void)
{
	// Rückgabe der Knoten in der Liste mit O(1)
/*
	Anzahl der Knoten in der Liste zurückgeben.
*/
	return list_size;
}

bool List::test(void)
{
	// Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und zurück
	// Es werden dabei die Anzahl der Knoten gezählt.
	// Stimmt die Anzahl der Knoten überein liefert die Methode true
	Node * tmp = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size) return false;
		i_next++;
	}
	if (i_next != list_size) return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size) return false;
		i_prev++;
	}
	return i_prev == i_next;
}

List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail)
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;			// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;			// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator + (const List & List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {	
		tmp = new List(this);						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append.list_size) {					// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht						
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List(this);						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append->list_size) {					// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht					
	return *tmp;
}

void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen des Formates für die Ausgabesteuerung der Liste bei cout
	// das Format wird für den überladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node * tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node * tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}
