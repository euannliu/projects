#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Set.h"
using namespace std;

int main()
{
	Set<string> *set, *loadset;
	ifstream file;
	string input, name, mail, line;
	stringstream ss;
	cout << "Welcome to e-Contact Book BETA!\n";
	cout << "Type in an appropriate command (typos will not be tolerated).\n";
	cout << "QUIT - quits the program\n";
	cout << "ADD - add a name and an associated e-mail\n";
	cout << "REMOVE - remove a name from the your book\n";
	cout << "CONTAINS - search up an e-mail with a given name\n";
	cout << "LOAD - merge your book with another book!\n";
	set = new Set<string>;
	while(true)
	{
		cout << ">> ";
		cin >> input;
		cout << endl;
		transform(input.begin(), input.end(), input.begin(), ::tolower); //makes string input become all lowercase
		if(input == "quit")
		{
			cout << "Bye bye!\n";
			break;
		}
		else if(input == "size")
		{
			cout << set->size() << endl << endl;
		}
		else if(input == "add")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			cout << "Enter an e-mail with square brackets [] around the e-mail\n>> ";
			cin >> mail;
			cout << endl;
			set->add(name);
		}
		else if(input == "remove")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			set->remove(name);
		}
		else if(input == "contains")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			if(set->contains(name))
			{
				cout << "That name is in your book!\n\n";
			}
			else
			{
				cout << "That name is not in your book!\n\n";
			}
		}
		else if(input == "load")
		{
			cin.ignore(10000,'\n');
			cout << "Enter the name of the text file you wish to import\n>> ";
			cin >> input;
			cout << endl;
			file.open(&input[0]);
			cin.ignore();
			if(file.fail())
			{
				cout << "ERROR - cannot open text file\n";
			}
			else
			{
				loadset = new Set<string>;
				while(getline(file,line)) //create a list with from the imported text file
				{
					ss << line;
					getline(ss,name,']');
					name = name + "]";
					getline(ss,mail,']');
					loadset->add(name);
					ss.ignore();
					ss.clear();
				}
				set->merge(*loadset);
				delete loadset;
			}
			file.close();
		}
	}
	delete set;
	return 0;
}