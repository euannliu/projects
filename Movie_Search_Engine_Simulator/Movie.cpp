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
	Set<string> temporary;
	temporary = other.getAllKeywords();
	temporary.first();
	for(int i=0; i<temporary.size(); i++)
	{
		addKeyword(temporary.getCurrent());
		temporary.next();
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
