#include "Movie.h"
using namespace std;

Movie::Movie()
{
	c_title = "";
	bank = new Set<string>;
}

Movie::Movie(string title)
{
	c_title=title;
	bank = new Set<string>;
}

Movie::Movie(const Movie & other)
{
	c_title = other.getTitle();
	Set<string>::Iterator temp_it;
	temp_it = other.getAllKeywords().begin();
	//Set<string> temporary;
	//temporary = other.getAllKeywords();
	//temporary.first();
	//for(int i=0; i<temporary.size(); i++)
	while(true)
	{
		addKeyword(*temp_it);
		try
		{
			++temp_it;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
		//addKeyword(temporary.getCurrent());
		//temporary.next();
	}
}

Movie::~Movie ()
{
	delete bank;
}

string Movie::getTitle () const
{
	return c_title;
}

void Movie::addKeyword (string keyword)
{
	string temp = keyword;
	transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	if(!bank->contains(temp))
	{
		bank->add(keyword);
	}
}

Set<string> & Movie::getAllKeywords () const
{
	return *bank;
}
