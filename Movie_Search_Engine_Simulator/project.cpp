#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Movie.h"
#include "User.h"

using namespace std;

//Declarations
Set<Movie*> *moviebank; //to store multiple movies
Set<User*> *userbank; //to store multiple users
Set<string> *keywordbank;

ifstream file; //to contain and load a file
ofstream fileo; //to read out to a file

stringstream ss; //to process data in a file
string line, input_one, input_two; //to help extract data from a file
string file_user, file_movie; //to help extract data from loading file
string user_id, user_name; //to help extract data from user file
string movie_title, movie_keyword, movie_compare; //to help extract data from movie file

Movie* movie; //to hold movie data
User* user; //to hold user data

int input_int; //int input
string input_string; //string input

int movie_count, keyword_match_count;
bool begin, user_check, movie_check, fileokay;
	
void File_Read_User()
{
	begin = false;
	while(getline(file,line))
	{
		ss << line;
		ss >> input_one;
		if(input_one=="BEGIN")
		{
			begin = true;
			ss >> user_id;
			//cout << user_id << endl;
		}
		ss.clear();
		if(begin)
		{
			while(getline(file,line))
			{
				ss << line;
				ss >> input_one;
				if(input_one=="END")
				{
					ss.clear();
					break;
				}
				getline(ss,user_name);
				user_name.erase(0,1);
				//cout << user_name << endl;
				ss.clear();					
			}
		}
		user = new User(user_id,user_name);
		userbank->add(user);
	}
}
void File_Read_Movie()
{
	begin = false;
	while(getline(file,line))
	{
		ss << line;
		ss >> input_one;
		if(input_one=="BEGIN")
		{
			begin = true;
			getline(ss,movie_title);
			movie_title.erase(0,1);
			//cout << movie_title << endl;
			movie_count++;
			movie = new Movie(movie_title);
		}
		ss.clear();
		if(begin)
		{
			while(getline(file,line))
			{
				ss << line;					
				ss >> input_one;
				if(input_one=="END")
				{
					ss.clear();
					break;
				}
				getline(ss,movie_keyword);
				movie_keyword.erase(0,1);
				movie->addKeyword(movie_keyword);
				//cout << movie_keyword << endl;
				ss.clear();
			}
		}
		moviebank->add(movie);
	}
}

void Search_Movie(bool search) //for the keyword search
{
	movie = moviebank->getCurrent();
	//Find associating keywords
	keywordbank = new Set<string>(movie->getAllKeywords());
	keywordbank->first();
	for(int j=0; j<keywordbank->size(); j++)
	{
		movie_compare = keywordbank->getCurrent();
		transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower);
		if(movie_compare==movie_keyword)
		{
			movie_check=true;
			break;
		}
		else
		{
			keywordbank->next();
		}
	}
	//Find associating keyword with movie title
	movie_compare = movie->getTitle();
	transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower);
	if(movie_compare==movie_keyword)
	{
		movie_check=true;
	}
	moviebank->next();
}

void Menu_Movie()
{
	while(true)
	{
		cout << "1. Search for a movie (by title)\n";
		cout << "2. Search for a movie (by keyword)\n";
		cout << "3. Logout\n";
		cout << ">> ";
		cin >> input_int;
		if(input_int==1)
		{
			cout << "Enter the movie's title: ";
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin,movie_title);
			transform(movie_title.begin(), movie_title.end(), movie_title.begin(), ::tolower);
			moviebank->first();
			movie_check=false;
			for(int i=0;i<moviebank->size();i++)
			{
				movie = moviebank->getCurrent();
				movie_compare = movie->getTitle();
				transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower);
				if(movie_compare==movie_title)
				{
					movie_check=true;
					break;
				}
				else
				{
					moviebank->next();
				}
			}						
			if(movie_check)
			{
				cout << endl << movie->getTitle() << endl;
				keywordbank = new Set<string>(movie->getAllKeywords());
				keywordbank->first();
				for(int j=0;j<keywordbank->size();j++)
				{
					cout << keywordbank->getCurrent() << endl;
					keywordbank->next();
				}
				cout << endl;
			}					
			else
			{
				cout << "No movie found...\n\n";
			}
		}
		else if(input_int==2)
		{
			cout << "Enter a keyword: ";
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin,movie_keyword);
			transform(movie_keyword.begin(), movie_keyword.end(), movie_keyword.begin(), ::tolower);
			moviebank->first();
			//Counting
			keyword_match_count=0;
			for(int i=0;i<moviebank->size();i++)
			{
				movie_check=false;
				Search_Movie(true);
				if(movie_check)
				{
					keyword_match_count++;
				}
			}			
			
			if(keyword_match_count==0)
			{
				cout << "No matches...\n\n";
			}
			else
			{
				cout << "There are " << keyword_match_count << " total matches!\n\n";
				moviebank->first();
				//Menu
				for(int i=0;i<moviebank->size();i++)
				{
					movie_check=false;
					Search_Movie(false);
					if(movie_check)
					{
						cout << movie->getTitle() << endl;
						keywordbank->first();
						for(int j=0;j<keywordbank->size();j++)
						{
							cout << keywordbank->getCurrent() << endl;
							keywordbank->next();
						}
						cout << endl;
						while(true)
						{
							//keyword search menu
							if(i<keyword_match_count-1) //checks to see if it is displaying the last result
							{
								cout << "1. Next movie\n";
							}
							cout << "2. Return to menu\n";
							cout << ">> ";
							cin >> input_int;
							if(input_int==1&&i<keyword_match_count-1)
							{
								cout << endl;
								break;
							}
							else if(input_int==2)
							{
								cout << endl;
								i=moviebank->size()+1;
								break;
							}
							else
							{
								cout << "Error input - try again!\n\n";
								cin.clear();
								cin.ignore(1000,'\n');
							}
						}
					}
				}
				cin.clear();
				cin.ignore(1000,'\n');
			}
		}
		else if(input_int==3)
		{
			cout << "Logging out...\n\n";
			break;
		}
		else
		{
			cout << "Error input - try again!\n\n";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
}

void Menu_User()
{
	while(fileokay)
	{
		cout << "Welcome to Notflix!\n";
		cout << "1. Log-in\n";
		cout << "2. Create new user\n";
		cout << "3. Quit\n";
		cout << ">> ";
		cin >> input_int;
		if(input_int==1)
		{
			cout << "Enter your user ID: ";
			cin >> input_string;
			userbank->first();
			user_check=false;
			for(int i=0;i<userbank->size();i++)
			{
				user = userbank->getCurrent();
				if(user->getID() == input_string)
				{
					user_check=true;
					break;
				}
				else
				{
					userbank->next();
				}
			}
			if(user_check)
			{
				cout << "\nSuccessful Log-in!\n";
				Menu_Movie();
			}
			else
			{
				cout << "Error - no associated user ID\n\n";
			}
			cin.clear();
			cin.ignore(1000,'\n');
		}
		else if(input_int==2)
		{
			while(true)
			{
				cout << "\nEnter a user ID: ";
				cin >> user_id;
				cin.clear();
				cin.ignore(1000,'\n');
				userbank->first();
				user_check=false;
				for(int i=0;i<userbank->size();i++)
				{
					user = userbank->getCurrent();
					if(user->getID() == user_id)
					{
						user_check=true;
						break;
					}
					else
					{
						userbank->next();
					}
				}
				if(user_check)
				{
					cout << "User ID already exists, try again\n";
				}
				else
				{
					cout << "Enter your name: ";
					getline(cin,user_name);
					user = new User(user_id,user_name);
					userbank->add(user);
					cout << user_name << " successfully added.\n\n";
					cin.clear();
					fileo.open(&file_user[0],std::ios::app);
					fileo << "BEGIN " << user_id << "\nNAME: " << user_name << "\nEND\n";
					fileo.close();
					break;
				}				
			}
		}
		else if(input_int==3)
		{
			cout << "Good-bye!\n";
			break;
		}
		else
		{
			cout << "Error input - try again!\n\n";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
}


int main(int argc, char *argv[])
{
//Initializations
	movie_count=0;
	fileokay=true;
	moviebank = new Set<Movie*>;
	userbank = new Set<User*>;
	keywordbank = new Set<string>;
	
	if(argc<2)
	{
		cout << "Program requires a command line input.\n";
		cout << "./<filename> <input text file>\n";
	}
	else
	{
//reading files
		file.open(argv[1]);
		if(file.fail())
		{
			cout << "Unable to open file.\n";
			fileokay=false;
		}
		else if(fileokay)
		{
			getline(file,line);
			ss << line;
			ss >> file_user; 
			ss.clear();
			getline(file,line);
			ss << line;
			ss >> file_movie;
			ss.clear();
			file.close();
		
			//User file input
			file.open(&file_user[0]);
			if(file.fail())
			{
				cout << "Unable to open user file.\n";
				fileokay=false;
			}
			else if(fileokay)
			{
				File_Read_User();
			}
			file.close();
			//Movie file input
			file.open(&file_movie[0]);
			if(file.fail())
			{					
				cout << "Unable to open movie file.\n";
				fileokay=false;
			}
			else if(fileokay)
			{
				File_Read_Movie();
			}
			file.close();
			
			//Go to the main menu
			Menu_User();
		}
	}
	delete moviebank;
	delete userbank;
	return 0;
}
