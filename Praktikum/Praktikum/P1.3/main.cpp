#include <iostream>
#include "List.h"
#include "tweet.h"
using namespace std;

int main()
{
	List<tweet> Tweets;
	string Text;
	
	Tweets.format("Tweet\n--->\n", "\n", "\n--->\n");
	while (true)
	{
		cout << "\nNachricht: ";
		getline(cin, Text);
		if (Text == "quit") break;
		Tweets.insertFront(tweet(Text));

		cout << Tweets;
	}

	return 0;
}