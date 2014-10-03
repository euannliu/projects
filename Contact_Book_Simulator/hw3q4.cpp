#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Map.h"

using namespace std;

int main()
{
	bool success;
	Map<string,string> *map, *loadmap;
	ifstream file;
	string input, name, mail, line;
	stringstream ss;
	cout << "Welcome to e-Contact Book!\n";
	cout << "Type in an appropriate command (typos will not be tolerated).\n";
	cout << "QUIT - quits the program\n";
	cout << "ADD - add a name and an associated e-mail\n";
	cout << "REMOVE - remove a name from the your book\n";
	cout << "QUERY - search up an e-mail with a given name\n";
	cout << "LOAD - merge your book with another book!\n";

	map = new Map<string,string>;

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
			cout << map->size() << endl << endl;
		}
		else if(input == "add")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			cout << "Enter an e-mail with square brackets [] around the e-mail\n>> ";
			getline(cin,mail);
			cout << endl;
			map->add(name,mail);
			cout << name << " has been added with e-mail: " << mail << endl << endl;
		}
		else if(input == "remove")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			map->remove(name);
			cout << name << " has been removed\n\n";
		}
		else if(input == "query")
		{
			cin.ignore(10000,'\n');
			cout << "Enter a name with square brackets [] around the name\n>> ";
			getline(cin,name);
			cout << endl;
			mail = map->get(name,success);
			if(success)
			{
				cout << name << "'s e-mail address is: " << mail << endl << endl;
			}
			else
			{
				cout << name << " is not found\n\n";
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
				loadmap = new Map<string,string>;
				while(getline(file,line)) //create a list with from the imported text file
				{
					ss << line;
					getline(ss,name,']');
					name = name + "]";
					getline(ss,mail,']');
					mail = mail + "]";
					loadmap->add(name,mail);
					ss.ignore();
					ss.clear();
				}
				map->merge(*loadmap);
				delete loadmap;
			}
			file.close();
		}
	}
	delete map;
	return 0;
}