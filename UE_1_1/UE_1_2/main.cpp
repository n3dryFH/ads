int main()
{
	MyList l;
	string line;
	while (getline(cin, line))
	{
		istringstream iss(line);
		string word;
		unsigned i = 0;
		while (iss >> word)
		{
			if (word.compare("-") != 0)
				l.push(word);
			else if (!l.isEmpty())
				cout << l.pop() << " ";
			++i;
		}
		if (i == 0) break;
	}
	cout << endl;
	cout << "Fertig!" << endl;
	return 0;
}