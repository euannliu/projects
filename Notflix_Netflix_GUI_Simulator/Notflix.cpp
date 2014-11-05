#include "Notflix.h"

using namespace std;

Notflix::Notflix()
{
	resize(480,320);
	setFixedSize(size());
	
	in_menu = false;
	
	//TITLE PAGE
	pixmapLogo = new QPixmap("img/NotflixLogo.png");
	pixmapLogo -> scaled(480,320);
	
	labelPicture = new QLabel(this);
	labelPicture -> setPixmap(*pixmapLogo);
	labelPicture -> setFixedSize(pixmapLogo->size());
	
	errorEmptyFields = new QErrorMessage();
	errorEmptyFields -> showMessage("Error 011 - Error - no arguments in command line");
}
Notflix::Notflix(int argc, char* argv[])
{
	resize(480,320);
	setFixedSize(size());
	
	in_menu = false;
	
	//TITLE PAGE
	pixmapLogo = new QPixmap("img/NotflixLogo.png");
	pixmapLogo -> scaled(480,320);
	
	labelPicture = new QLabel(this);
	labelPicture -> setPixmap(*pixmapLogo);
	labelPicture -> setFixedSize(pixmapLogo->size());
	
	errorEmptyFields = new QErrorMessage();
	Read_Data(argc, argv);
}

Notflix::~Notflix()
{
	delete moviebank;
	delete userbank;
}

void Notflix::Read_Data(int argc, char* argv[])
{
//Initializations
	movie_count=0;
	fileokay=true;
	moviebank = new Set<Movie*>;
	userbank = new Set<User*>;
	keywordbank = new Set<string>;
	crash = false;
	
	if(argc<2)
	{
		errorEmptyFields -> showMessage("Error 012 - Error - no arguments in command line");
	}
	else
	{
//reading files
		file.open(argv[1]);
		if(file.fail())
		{		
			errorEmptyFields -> showMessage("Error 010 - Unable to open file");
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
		
			//Movie file input
			file.open(&file_movie[0]);
			if(file.fail())
			{					
				errorEmptyFields -> showMessage("Error 013 - Unable to open movie file");
				fileokay=false;
			}
			else if(fileokay)
			{
				Read_Movie_Data();
			}
			file.close();
			
			//User file input
			file.open(&file_user[0]);
			if(file.fail())
			{
				errorEmptyFields -> showMessage("Error 013 - Unable to open user file");
				fileokay=false;
			}
			else if(fileokay)
			{
				Read_User_Data();
			}
			file.close();
			
			//Go to the main menu
			if(!crash)
				Initialize();
		}
	}
}


void Notflix::Read_Movie_Data()
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
				if(input_one=="KEYWORD:")
				{
					getline(ss,movie_keyword);
					movie_keyword.erase(0,1);
					movie->addKeyword(movie_keyword);
					ss.clear();
				}
				else if(input_one=="END")
				{
					ss.clear();
					break;
				}
				else
				{
					errorEmptyFields -> showMessage("Error 014 - Invalid file formatting");
					ss.clear();
					crash = true;
					fileokay=false;
					break;
				}
			}
			if(crash)
				break;
		}
		moviebank->add(movie);
	}
}

void Notflix::Read_User_Data()
{
	begin = false;
	read_movie = NULL;
	while(getline(file,line))
	{
		ss << line;
		ss >> input_one;
		if(input_one=="BEGIN")
		{
			begin = true;
			ss >> user_id;
		}
		ss.clear();
		if(begin)
		{
			while(getline(file,line))
			{
				ss << line;
				ss >> input_one;
				if(input_one=="BEGIN")
				{
					ss >> input_one;
					if(input_one=="QUEUE") //extracting user queue
					{
						ss.clear();
						while(getline(file,line))
						{
							if(line=="END QUEUE")
							{
								break;
							}
							//Checking through all the movies to see if user has the right movies in Queue
							mb_iterator = moviebank->begin();
							while(true)
							{
								Movie* temp_movie;
								temp_movie = *mb_iterator;
								if(line==temp_movie->getTitle())
								{
									q_movies.enqueue(*mb_iterator);
									break;
								}
								else
								{
									try
									{
										++mb_iterator;
									}
									catch(NoSuchElementException &e)
									{
										break;
									}
								}
							}
						}
					}	
				}
				else if(input_one=="END")
				{
					ss.clear();
					break;
				}
				else if(input_one=="NAME:")
				{
					getline(ss,user_name);
					user_name.erase(0,1);
				}
				else if(input_one=="MOVIE:")
				{
					Movie *temp_movie;
					getline(ss,user_movie);
					user_movie.erase(0,1);
					mb_iterator = moviebank->begin();
					while(true)
					{
						temp_movie = *mb_iterator;
						if(user_movie==temp_movie->getTitle())
						{
							read_movie = temp_movie;
							break;
						}
						else
						{
							try
							{
								++mb_iterator;
							}
							catch(NoSuchElementException &e)
							{
								break;
							}
						}
					}
				}
				ss.clear();					
			}
		}
		user = new User(user_id,user_name);
		user->rentMovie(read_movie);
		read_movie = NULL;
		while(!q_movies.isEmpty())
		{
			user->usermoviebank.enqueue(q_movies.peekFront());
			q_movies.dequeue();
		}
		userbank->add(user);
	}
}

void Notflix::Initialize()
{
	pixmapSide = new QPixmap("img/NotflixSideLogo.png");
	pixmapSide -> scaled(480,320);
	
	labelSide = new QLabel(this);
	labelSide -> setPixmap(*pixmapSide);
	labelSide -> setFixedSize(pixmapSide->size());
	labelSide -> hide();
	
	widgetTitlebar = new QWidget(this);
	widgetTitlebar->resize(480,192);
	widgetTitlebar->move(0,208);
	
	labelText1 = new QLabel(widgetTitlebar);
	labelText1 -> setText("<font color='white'>Enter your username:</font>");
	labelText1 -> setGeometry(56,16,240,24);
	labelText1 -> show();
	
	inputLogin = new QLineEdit(widgetTitlebar);
	inputLogin -> setGeometry(28,42,192,24);
	inputLogin -> setMaxLength(16);
	inputLogin -> show();
	inputLogin -> setFocus();
	connect(inputLogin, SIGNAL(returnPressed()), this, SLOT(Main_Menu()));
	
	buttonLogin = new QPushButton("Log-in",widgetTitlebar);
	buttonLogin -> setGeometry(88,74,72,24);
	connect(buttonLogin, SIGNAL(clicked()), this, SLOT(Main_Menu()));

	buttonNewUser = new QPushButton("Register",widgetTitlebar);
	buttonNewUser -> setGeometry(272,48,72,28);	
	connect(buttonNewUser, SIGNAL(clicked()), this, SLOT(Register()));
	
	buttonQuit = new QPushButton("Quit",widgetTitlebar);
	buttonQuit -> setGeometry(376,48,72,28);	
	connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
	//
	
	//REGISTER PAGE
	inputNewID = new QLineEdit(widgetTitlebar);
	inputNewID -> setGeometry(28,34,192,24);
	inputNewID -> setMaxLength(16);
	inputNewID -> hide();

	inputNewName = new QLineEdit(widgetTitlebar);
	inputNewName -> setGeometry(28,78,192,24);
	inputNewName -> setMaxLength(32);
	inputNewName -> hide();
	
	connect(inputNewID, SIGNAL(returnPressed()), inputNewName, SLOT(setFocus()));
	connect(inputNewName, SIGNAL(returnPressed()), this, SLOT(Reg_Complete()));
	
	labelText2 = new QLabel(widgetTitlebar);
	labelText2 -> setGeometry(90,58,240,24);
	labelText2 -> setText("<font color='white'>Full Name:</font>"); 
	labelText2 -> hide();
	
	messageNotice = new QMessageBox();
	//
	
	//MAIN MENU
	widgetMainMenu = new QWidget(this);
	widgetMainMenu -> resize(320,320);
	widgetMainMenu -> move(160,0);
	widgetMainMenu -> hide();
	/*
	frameQueue = new QFrame(widgetMainMenu);
	frameQueue -> setGeometry(24,88,268,86);
	frameQueue -> setFrameStyle(QFrame::Panel | QFrame::Raised);
	frameQueue -> setLineWidth(1);
	frameQueue -> show();
	
	frameSearch = new QFrame(widgetMainMenu);
	frameSearch -> setGeometry(24,176,268,86);
	frameSearch -> setFrameStyle(QFrame::Panel | QFrame::Raised);
	frameSearch -> setLineWidth(1);
	frameSearch -> show();
	*/
	labelMainText1 = new QLabel(widgetMainMenu);
	labelMainText1 -> setGeometry(0,8,320,24);
	labelMainText1 -> setAlignment(Qt::AlignCenter);
	labelMainText1 -> hide();
	
	labelMainText2 = new QLabel(widgetMainMenu);
	labelMainText2 -> setGeometry(0,34,320,24);
	labelMainText2 -> setAlignment(Qt::AlignCenter);
	labelMainText2 -> hide();
	
	labelMainText3 = new QLabel(widgetMainMenu);
	labelMainText3 -> setGeometry(40,94,240,24);
	labelMainText3 -> setText("<font color='white'>Queue</font>");
	labelMainText3 -> setAlignment(Qt::AlignCenter);
	labelMainText3 -> hide();
	
	labelMainText4 = new QLabel(widgetMainMenu);
	labelMainText4 -> setGeometry(0,118,320,24);
	labelMainText4 -> setAlignment(Qt::AlignCenter);
	labelMainText4 -> hide();
	
	labelMainText5 = new QLabel(widgetMainMenu);
	labelMainText5 -> setGeometry(40,176,240,24);
	labelMainText5 -> setAlignment(Qt::AlignCenter);
	labelMainText5 -> setText("<font color='white'>Search</font>");
	labelMainText5 -> hide();
	
	buttonReturn = new QPushButton("Return Movie",widgetMainMenu);
	buttonReturn -> setGeometry(88,60,144,24);
	buttonReturn -> hide();
	connect(buttonReturn, SIGNAL(clicked()), this, SLOT(Return_Movie()));
	
	buttonRent = new QPushButton("Rent",widgetMainMenu);
	buttonRent -> setGeometry(44,142,72,24);
	buttonRent -> hide();
	connect(buttonRent, SIGNAL(clicked()), this, SLOT(Queue_Rent()));
	
	buttonNext = new QPushButton("Next",widgetMainMenu);
	buttonNext -> setGeometry(124,142,72,24);
	buttonNext -> hide();
	connect(buttonNext, SIGNAL(clicked()), this, SLOT(Queue_Next()));
	
	buttonRemove = new QPushButton("Remove",widgetMainMenu);
	buttonRemove-> setGeometry(204,142,72,24);
	buttonRemove -> hide();
	connect(buttonRemove, SIGNAL(clicked()), this, SLOT(Queue_Remove()));
	
	buttonMovie = new QPushButton("by Title",widgetMainMenu);
	buttonMovie-> setGeometry(58,236,96,24);
	buttonMovie -> hide();
	connect(buttonMovie, SIGNAL(clicked()), this, SLOT(Search_Title()));
	
	buttonKeyword = new QPushButton("by Keyword",widgetMainMenu);
	buttonKeyword -> setGeometry(166,236,96,24);
	buttonKeyword -> hide();
	connect(buttonKeyword, SIGNAL(clicked()), this, SLOT(Search_Keyword()));
	
	buttonLogout = new QPushButton("Log-out",widgetMainMenu);
	buttonLogout -> setGeometry(67,278,186,24);
	buttonLogout -> hide();
	connect(buttonLogout, SIGNAL(clicked()), this, SLOT(Logout()));
	
	inputSearch = new QLineEdit(widgetMainMenu);
	inputSearch -> setGeometry(62,206,192,24);
	inputSearch -> setMaxLength(32);
	inputSearch -> hide();
	connect(inputSearch, SIGNAL(returnPressed()), this, SLOT(Search_Title()));
	
	pixmapBack = new QPixmap("img/Background.png");
	pixmapBack -> scaled(320,320);
	
	windowMovie = new QWidget(this);
	windowMovie -> setGeometry(112,32,256,256);
	windowMovie -> hide();
	
	labelBack = new QLabel(windowMovie);
	labelBack -> setPixmap(*pixmapBack);
	labelBack -> setFixedSize(pixmapBack->size());
	labelBack -> hide();
	
	buttonMQueue = new QPushButton("Queue",windowMovie);
	buttonMQueue -> setGeometry(96,220,64,24);
	buttonMQueue -> hide();
	connect(buttonMQueue, SIGNAL(clicked()), this, SLOT(M_Queue()));
	
	buttonMExit = new QPushButton("Back",windowMovie);
	buttonMExit -> setGeometry(172,220,64,24);
	buttonMExit -> hide();
	connect(buttonMExit, SIGNAL(clicked()), this, SLOT(M_Exit()));
	
	buttonKNext = new QPushButton("Next",windowMovie);
	buttonKNext -> setGeometry(20,220,64,24);
	buttonKNext -> hide();
	connect(buttonKNext, SIGNAL(clicked()), this, SLOT(K_Next()));
	
	buttonKQueue = new QPushButton("Queue",windowMovie);
	buttonKQueue -> setGeometry(96,220,64,24);
	buttonKQueue -> hide();
	connect(buttonKQueue, SIGNAL(clicked()), this, SLOT(K_Queue()));
	
	buttonKExit = new QPushButton("Back",windowMovie);
	buttonKExit -> setGeometry(172,220,64,24);
	buttonKExit -> hide();
	connect(buttonKExit, SIGNAL(clicked()), this, SLOT(K_Destructor()));
	
	scrollArea = new QScrollArea(windowMovie);
	scrollArea -> setGeometry(8,120,240,80);
	scrollArea -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea -> setWidgetResizable(1);
	scrollArea -> hide();
	
	widgetArea = new QWidget(scrollArea);
	widgetArea -> hide();
	
	windowKeyword = NULL;
}

void Notflix::Register()
{
	inputNewID -> show();
	inputNewName -> show();
	inputLogin -> hide();
	labelText1 -> setGeometry(89,12,240,24);
	labelText1 -> setText("<font color='white'>Username:</font>"); 
	labelText2 -> show();
	buttonLogin -> hide();
	disconnect(buttonNewUser,0,0,0);
	connect(buttonNewUser, SIGNAL(clicked()), this, SLOT(Reg_Complete()));
	
	delete buttonQuit;
	buttonQuit = new QPushButton("Back",widgetTitlebar);
	buttonQuit -> setGeometry(376,48,72,28);	
	buttonQuit -> show();
	connect(buttonQuit, SIGNAL(clicked()), this, SLOT(Reg_Back()));
}

void Notflix::Reg_Complete()
{			
	string temp_string1, temp_string2;
	temp_string1 = inputNewID->text().toLocal8Bit().constData();
	temp_string2 = inputNewName->text().toLocal8Bit().constData();
	if(temp_string1.find_first_not_of("\t\n ") || temp_string2.find_first_not_of("\t\n "))
	{
		errorEmptyFields -> showMessage("Error 003 - Empty Fields");
	}
	else
	{	
		user_id = temp_string1;
		user_name = temp_string2;
		ub_iterator = userbank->begin();
		user_check=false;
		for(int i=0;i<userbank->size();i++)
		{
			user = *ub_iterator;
			if(user->getID() == user_id)
			{
				user_check=true;
				break;
			}
			else
			{
				try
				{
					++ub_iterator;
				}
				catch(NoSuchElementException &e)
				{
					break;
				}
			}
		}
		if(user_check)
		{
			errorEmptyFields -> showMessage("Error 004 - Username already taken");
		}
		else
		{
			string combine;
			combine = user_name + " has been added to the database!";
			messageNotice -> setText(QString(combine.c_str()));
			messageNotice -> exec();
			user = new User(user_id,user_name);
			userbank->add(user);
			cin.clear();
			fileo.open(&file_user[0],std::ios::app);
			fileo << "BEGIN " << user_id << "\nNAME: " << user_name << "\nMOVIE: " << "\nEND\n";
			fileo.close();
			Read_User_Data();
			Reg_Back();
		}	
	}
}

void Notflix::Reg_Back()
{
	inputNewID -> setText("");
	inputNewName -> setText("");
	inputNewID -> hide();
	inputNewName -> hide();
	inputLogin -> show();
	labelText1 -> setText("<font color='white'>Enter your username:</font>");
	labelText1 -> setGeometry(57,16,240,24);
	labelText2 -> hide();
	buttonLogin -> show();
	disconnect(buttonNewUser,0,0,0);
	connect(buttonNewUser, SIGNAL(clicked()), this, SLOT(Register()));
	
	delete buttonQuit;
	buttonQuit = new QPushButton("Quit",widgetTitlebar);
	buttonQuit -> setGeometry(376,48,72,28);	
	buttonQuit -> show();
	connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Notflix::Search_Title()
{
	movie_title = inputSearch->text().toLocal8Bit().constData();
	inputSearch -> clear();
	transform(movie_title.begin(), movie_title.end(), movie_title.begin(), ::tolower);
	mb_iterator = moviebank->begin();
	movie_check=false;
	for(int i=0;i<moviebank->size();i++)
	{
		movie = *mb_iterator;
		movie_compare = movie->getTitle();
		transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower);
		if(movie_compare==movie_title)
		{
			movie_check=true;
			break;
		}
		else
		{
			try
			{
				++mb_iterator;
			}
			catch(NoSuchElementException &e)
			{
				break;
			}
		}
	}						
	if(movie_check)
	{
		windowMovie -> show();
		labelBack -> show();
		widgetArea -> show();
	
		ifstream test_pic_file;
		string combine;
		
		disconnect(buttonReturn,0,0,0);
		disconnect(buttonLogout,0,0,0);
		disconnect(buttonRemove,0,0,0);
		disconnect(buttonKeyword,0,0,0);
		
		buttonMQueue -> show();
		buttonMExit -> show();
		combine = "<font color='white'>" + movie->getTitle() + "</font>";
		labelMovieTitle = new QLabel(windowMovie);
		labelMovieTitle -> setAlignment(Qt::AlignCenter);
		labelMovieTitle -> setGeometry(0,8,258,24);
		labelMovieTitle -> setText(QString(combine.c_str()));
		labelMovieTitle -> show();
		
		combine = "img/Logo/" + movie->getTitle() + " Logo.png";
		test_pic_file.open(&combine[0]);
		if(test_pic_file.fail())
		{
			pixmapMovie = new QPixmap("img/Logo/DefaultLogo.png");
			pixmapMovie -> scaled(208,72);
			
			labelMovie = new QLabel(windowMovie);
			labelMovie -> setPixmap(*pixmapMovie);
			labelMovie -> setFixedSize(pixmapMovie -> size());
			labelMovie -> setGeometry(24,35,208,72);
			labelMovie -> show();
		}		
		else
		{
			pixmapMovie = new QPixmap(QString(combine.c_str()));
			pixmapMovie -> scaled(208,72);
			
			labelMovie = new QLabel(windowMovie);
			labelMovie -> setPixmap(*pixmapMovie);
			labelMovie -> setFixedSize(pixmapMovie -> size());
			labelMovie -> setGeometry(24,35,208,72);
			labelMovie -> show();
		}
		test_pic_file.close();
		kb_iterator = movie->getAllKeywords().begin();
		combine = "";
		int window_size = 0;
		for(int j=0;j<movie->getAllKeywords().size();j++)
		{
			window_size += 24;
			combine = combine + *kb_iterator + "\n";
			try
			{
				++kb_iterator;
			}
			catch(NoSuchElementException &e)
			{
				break;
			}
		}
		
		labelKeywords = new QLabel(widgetArea);
		labelKeywords -> setGeometry(0,0,240,window_size);
		labelKeywords -> setText(QString(combine.c_str()));
		labelKeywords -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
		labelKeywords -> show();
		widgetArea -> setMinimumSize(240,window_size);
		scrollArea -> setWidget(widgetArea);
		scrollArea -> show();
		
		labelKeywords -> show();
	}					
	else		
		errorEmptyFields -> showMessage("Error 008 - No movie in database");
}

void Notflix::M_Queue()
{
	string combine;
	combine = movie->getTitle() + " has been added to your Queue";
	messageNotice -> setText(QString(combine.c_str()));
	messageNotice -> exec();
	user->usermoviebank.enqueue(movie);
	combine = "<font color='white'>Top: " + movie->getTitle() + "</font>";
	labelMainText4 -> setText(QString(combine.c_str()));
	M_Exit();
}

void Notflix::M_Exit()
{
	windowMovie -> hide();
	labelBack -> hide();
	scrollArea -> hide();
	widgetArea -> hide();
	buttonMQueue -> hide();
	buttonMExit -> hide();
	delete labelMovieTitle;
	delete labelKeywords;
	delete pixmapMovie;
	delete labelMovie;
	
	connect(buttonReturn, SIGNAL(clicked()), this, SLOT(Return_Movie()));
	connect(buttonLogout, SIGNAL(clicked()), this, SLOT(Logout()));
	connect(buttonRemove, SIGNAL(clicked()), this, SLOT(Queue_Remove()));
	connect(buttonKeyword, SIGNAL(clicked()), this, SLOT(Search_Keyword()));
}

void Notflix::Search_Keyword()
{		
	string combine;
	movie_keyword = inputSearch->text().toLocal8Bit().constData();
	inputSearch -> clear();
	transform(movie_title.begin(), movie_title.end(), movie_title.begin(), ::tolower);

	mb_iterator = moviebank->begin();
	//Counting
	keyword_match_count=0;	
	hold_movie = new Movie* [moviebank->size()];
			
	for(int i=0;i<moviebank->size();i++)
	{
		hold_movie[i] = *mb_iterator;
		try
		{
			++mb_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	hold_count=0;
	for(int i=0;i<moviebank->size();i++)
	{
		movie_check=false;
		Search_Movie();
		if(movie_check)
		{
			keyword_match_count++;
		}
	}
	if(keyword_match_count==0)
	{
		errorEmptyFields -> showMessage("Error 009 - No movies with matching keyword");
	}
	else
	{
		ifstream test_pic_file;
		string combine;
		stringstream temp_ss;
		string temp_stringthing;
		
		temp_ss << keyword_match_count;
		temp_ss >> temp_stringthing;
		combine = "There are a total of " + temp_stringthing + " matches!";
		messageNotice -> setText(QString(combine.c_str()));
		messageNotice -> exec();
		
		windowMovie -> show();
		labelBack -> show();
		widgetArea -> show();
	
		disconnect(buttonReturn,0,0,0);
		disconnect(buttonLogout,0,0,0);
		disconnect(buttonRemove,0,0,0);
		disconnect(buttonKeyword,0,0,0);
		
		buttonKQueue -> show();
		buttonKExit -> show();

		mb_iterator = moviebank->begin();
		hold_count=0;
		
		counter_check = true;
		counter_one = 0;
		counter_two = 0;
		K_Menu();

	}
}

void Notflix::K_Menu()
{	
	string combine;
	ifstream test_pic_file;
	if(counter_two == moviebank->size())
	{
		K_Exit();
	}
	movie_check=false;
	Search_Movie();
	if(movie_check)
	{
		combine = "<font color='white'>" + movie->getTitle() + "</font>";
		labelMovieTitle = new QLabel(windowMovie);
		labelMovieTitle -> setAlignment(Qt::AlignCenter);
		labelMovieTitle -> setGeometry(0,8,258,24);
		labelMovieTitle -> setText(QString(combine.c_str()));
		labelMovieTitle -> show();
		
		combine = "img/Logo/" + movie->getTitle() + " Logo.png";
		test_pic_file.open(&combine[0]);
		if(test_pic_file.fail())
		{
			pixmapMovie = new QPixmap("img/Logo/DefaultLogo.png");
			pixmapMovie -> scaled(208,72);
			
			labelMovie = new QLabel(windowMovie);
			labelMovie -> setPixmap(*pixmapMovie);
			labelMovie -> setFixedSize(pixmapMovie -> size());
			labelMovie -> setGeometry(24,35,208,72);
			labelMovie -> show();
		}		
		else
		{
			pixmapMovie = new QPixmap(QString(combine.c_str()));
			pixmapMovie -> scaled(208,72);
			
			labelMovie = new QLabel(windowMovie);
			labelMovie -> setPixmap(*pixmapMovie);
			labelMovie -> setFixedSize(pixmapMovie -> size());
			labelMovie -> setGeometry(24,35,208,72);
			labelMovie -> show();
		}
		test_pic_file.close();
		
		kb_iterator = movie->getAllKeywords().begin();
		combine = "";
		int window_size = 0;
		for(int j=0;j<movie->getAllKeywords().size();j++)
		{
			window_size += 24;
			combine = combine + *kb_iterator + "\n";
			try
			{
				++kb_iterator;
			}
			catch(NoSuchElementException &e)
			{
				break;
			}
		}
		labelKeywords = new QLabel(widgetArea);
		labelKeywords -> setGeometry(0,0,240,window_size);
		labelKeywords -> setText(QString(combine.c_str()));
		labelKeywords -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
		labelKeywords -> show();
		cout << window_size << endl;
		widgetArea -> setMinimumSize(240,window_size);
		scrollArea -> setWidget(widgetArea);
		scrollArea -> show();
		
		if(counter_check)
		{
			counter_check = false;
			counter_one=0;
		}
		if((counter_one<keyword_match_count-1)) //checks to see if it is displaying the last result
			buttonKNext -> show();
		else
			buttonKNext -> hide();
	}
	else
	{
		counter_one++;
		counter_two++;
		K_Menu();
	}
}

void Notflix::K_Next()
{
	delete labelMovieTitle;
	delete labelKeywords;
	delete pixmapMovie;
	delete labelMovie;
	counter_one++;
	counter_two++;
	K_Menu();
}

void Notflix::K_Queue()
{
	string combine;
	combine = movie->getTitle() + " has been added to your Queue";
	messageNotice -> setText(QString(combine.c_str()));
	messageNotice -> exec();
	user->usermoviebank.enqueue(movie);
	combine = "<font color='white'>Top: " + movie->getTitle() + "</font>";
	labelMainText4 -> setText(QString(combine.c_str()));
	K_Menu();
}

void Notflix::K_Destructor()
{
	delete labelMovieTitle;
	delete labelKeywords;
	delete pixmapMovie;
	delete labelMovie;
	K_Exit();
}

void Notflix::K_Exit()
{
	windowMovie -> hide();
	labelBack -> hide();
	scrollArea -> hide();
	widgetArea -> hide();
	buttonKQueue -> hide();
	buttonKExit -> hide();
	
	connect(buttonReturn, SIGNAL(clicked()), this, SLOT(Return_Movie()));
	connect(buttonLogout, SIGNAL(clicked()), this, SLOT(Logout()));
	connect(buttonRemove, SIGNAL(clicked()), this, SLOT(Queue_Remove()));
	connect(buttonKeyword, SIGNAL(clicked()), this, SLOT(Search_Keyword()));
	delete [] hold_movie;
}

void Notflix::Search_Movie()
{	
	movie = hold_movie[hold_count];
	//Find associating keywords
	hold_keyword = new string [movie->getAllKeywords().size()];
	
	kb_iterator = movie->getAllKeywords().begin();

	for(int k=0;k<movie->getAllKeywords().size();k++)
	{
		hold_keyword[k] = *kb_iterator;
		try
		{
			++kb_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}	
	hold_kcount=0;
	for(int j=0; j<movie->getAllKeywords().size(); j++)
	{
		movie_compare = hold_keyword[hold_kcount];
		hold_kcount++;
		transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower); //this is messing up my pointers for some reason
		if(movie_compare==movie_keyword)
		{
			movie_check=true;
			break;
		}
	}
	//Find associating keyword with movie title
	movie_compare = movie->getTitle();
	transform(movie_compare.begin(), movie_compare.end(), movie_compare.begin(), ::tolower);
	if(movie_compare==movie_keyword)
	{
		movie_check=true;
	}
	hold_count++;
	delete [] hold_keyword;
}

void Notflix::Main_Menu()
{	
	in_menu = true;
	input_string = inputLogin -> text().toLocal8Bit().constData();
	ub_iterator = userbank->begin();
	user_check=false;
	for(int i=0;i<userbank->size();i++)
	{
		user = *ub_iterator;
		if(user->getID() == input_string)
		{
			user_check=true;
			break;
		}
		else
		{
			try
			{
				++ub_iterator;
			}
			catch(NoSuchElementException &e)
			{
				break;
			}
		}
	}
	if(user_check) //SUCCESSFUL LOGIN
	{
		//Set-Up
	
		//widgetMainMenu -> setStyle(QStyle(platinum));
		widgetMainMenu -> show();
		labelSide -> show();
	
		inputLogin -> hide();
		labelText1 -> hide();
		buttonLogin -> hide();
		buttonQuit -> hide();
		buttonNewUser -> hide();
	
		buttonReturn -> show();
		buttonRent -> show();
		buttonNext -> show();
		buttonRemove -> show();
		buttonMovie -> show();
		buttonKeyword -> show();
		buttonLogout -> show();	
		string temp = user->getName();
		string combine;
		combine = "<font color='white'>Welcome to Notflix " + temp + "!</font>";
		labelMainText1 -> setText(QString(combine.c_str()));
		//Checked out movie
		if(user->currentMovie() != NULL)
		{
			temp = user->currentMovie()->getTitle();
			combine = "<font color='white'>You have checked out: " + temp + "</font>";
			labelMainText2 -> setText(QString(combine.c_str()));
		}
		else
		{
			combine = "<font color='white'>You have no movies checked out...</font>";
			labelMainText2 -> setText(QString(combine.c_str()));			
		}
		//Queue
		if(!user->usermoviebank.isEmpty())
		{
			temp = user->usermoviebank.peekFront()->getTitle();
			combine = "<font color='white'>Top: " + temp + "</font>";
			labelMainText4 -> setText(QString(combine.c_str()));
		}
		else
		{
			combine = "<font color='white'>Top: No movie in Queue...</font>";
			labelMainText4 -> setText(QString(combine.c_str()));
		}
		
		labelMainText1 -> show();
		labelMainText2 -> show();
		labelMainText3 -> show();
		labelMainText4 -> show();
		labelMainText5 -> show();
	
		inputSearch -> show();
	}
	else
	{
		errorEmptyFields -> showMessage("Error 002 - Invalid Log-in");
		inputLogin -> clear();
	}
}

void Notflix::Return_Movie()
{
	if(user->currentMovie()!=NULL)
	{
		string combine;
		combine = user->currentMovie()->getTitle() + " has been returned!";
		messageNotice -> setText(QString(combine.c_str()));
		messageNotice -> exec();
		user->returnMovie();
		
		//Update current movie
		combine = "<font color='white'>You have no movies checked out...</font>";
		labelMainText2 -> setText(QString(combine.c_str()));
	}
	else
		errorEmptyFields -> showMessage("Error 005 - No movie to return");
}

void Notflix::Queue_Rent()
{
	if(user->currentMovie()==NULL)
	{
		if(!user->usermoviebank.isEmpty())
		{
			string combine, temp;
			combine = user->usermoviebank.peekFront()->getTitle() + " has been checked out!";
			messageNotice -> setText(QString(combine.c_str()));
			messageNotice -> exec();
			user->rentMovie(user->usermoviebank.peekFront());
			user->usermoviebank.dequeue();
			
			//Update current movie
			temp = user->currentMovie()->getTitle();
			combine = "<font color='white'>You have checked out: " + temp + "</font>";
			labelMainText2 -> setText(QString(combine.c_str()));
			
			//Update Queue output
			if(!user->usermoviebank.isEmpty())
			{
				temp = user->usermoviebank.peekFront()->getTitle();
				combine = "<font color='white'>Top: " + temp + "</font>";
				labelMainText4 -> setText(QString(combine.c_str()));
			}
			else
			{
				combine = "<font color='white'>Top: No movie in Queue...</font>";
				labelMainText4 -> setText(QString(combine.c_str()));
			}
		}
		else
			errorEmptyFields -> showMessage("Error 007 - No movie in Queue");
	}
	else		
		errorEmptyFields -> showMessage("Error 006 - A movie has already been checked out");
}

void Notflix::Queue_Next()
{
	if(!user->usermoviebank.isEmpty())
	{
		string combine, temp;
		Movie* temp_movie;
		temp_movie = user->usermoviebank.peekFront();
		user->usermoviebank.dequeue();
		user->usermoviebank.enqueue(temp_movie);
		
		//Update Queue output
		temp = user->usermoviebank.peekFront()->getTitle();
		combine = "<font color='white'>Top: " + temp + "</font>";
		labelMainText4 -> setText(QString(combine.c_str()));
	}
	else
		errorEmptyFields -> showMessage("Error 007 - No movie in Queue");
}

void Notflix::Queue_Remove()
{
	if(!user->usermoviebank.isEmpty())
	{
		string combine, temp;
		combine = user->usermoviebank.peekFront()->getTitle() + " has been removed...";
		messageNotice -> setText(QString(combine.c_str()));
		messageNotice -> exec();
		user->usermoviebank.dequeue();
		
		//Update Queue output
		if(!user->usermoviebank.isEmpty())
		{
			temp = user->usermoviebank.peekFront()->getTitle();
			combine = "<font color='white'>Top: " + temp + "</font>";
			labelMainText4 -> setText(QString(combine.c_str()));
		}
		else
		{
			combine = "<font color='white'>Top: No movie in Queue...</font>";
			labelMainText4 -> setText(QString(combine.c_str()));
		}
	}
	else
		errorEmptyFields -> showMessage("Error 007 - No movie in Queue");
}

void Notflix::Logout()
{
	messageNotice -> setText("Changes have been saved.");
	messageNotice -> exec();
	in_menu = false;
	string name_of_user = user->getID();
	ifstream current_file;
	current_file.open(&file_user[0]);
	ofstream current_file_o, temp_file_o;
	temp_file_o.open("temp.txt",std::ios::app);
	stringstream sstoken;
	string token;
	Queue<Movie*> temp_Q;
	
	//Reads in text file to store into another temporary text file; omits lines about the current user
	while(getline(current_file,line))
	{
		sstoken.str("");
		sstoken.clear();
		sstoken << line;
		sstoken >> token;
		if(token=="BEGIN")
		{
			sstoken >> token;
			if(token==name_of_user)
			{
				while(getline(current_file,line))
				{
					sstoken.str("");
					sstoken.clear();
					sstoken << line;
					sstoken >> token;
					if(token=="END")
					{
						sstoken >> token;
						if(token!="QUEUE")
						{
							break;
						}
					}
				}
			}
			else
			{
				temp_file_o << line << endl;
			}
		}
		else
		{
			temp_file_o << line << endl;
		}
	}
	
	//writing to the temp file at the end for the updated current user info
	temp_file_o << "BEGIN " << name_of_user << endl;
	temp_file_o << "NAME: " << user->getName() << endl;
	if(user->currentMovie()==NULL)
		temp_file_o << "MOVIE: " << endl;
	else
		temp_file_o << "MOVIE: " << user->currentMovie()->getTitle() << endl;
	temp_file_o << "BEGIN QUEUE" << endl;
	while(!user->usermoviebank.isEmpty())
	{
		temp_file_o << user->usermoviebank.peekFront()->getTitle() << endl;
		temp_Q.enqueue(user->usermoviebank.peekFront());
		user->usermoviebank.dequeue();
	}
	temp_file_o << "END QUEUE" << endl;
	temp_file_o << "END" << endl;
	while(!temp_Q.isEmpty())
	{
		user->usermoviebank.enqueue(temp_Q.peekFront());
		temp_Q.dequeue();
	}
	
	current_file.close();
	temp_file_o.close();
	remove(&file_user[0]);
	rename("temp.txt",&file_user[0]);

	//New UI
	widgetMainMenu -> hide();
	labelSide -> hide();
	
	inputLogin -> show();
	inputLogin -> clear();
	labelText1 -> show();
	buttonLogin -> show();
	buttonQuit -> show();
	buttonNewUser -> show();
	
	buttonReturn -> hide();
	buttonRent -> hide();
	buttonNext -> hide();
	buttonRemove -> hide();
	buttonMovie -> hide();
	buttonKeyword -> hide();
	buttonLogout -> hide();
	
	labelMainText1 -> hide();
	labelMainText2 -> hide();
	labelMainText3 -> hide();
	labelMainText4 -> hide();
	labelMainText5 -> hide();
	
	inputSearch -> hide();	

}

void Notflix::closeEvent(QCloseEvent *event)
{
	if(in_menu)
	{
		messageNotice -> setText("Changes will not be saved.");
		messageNotice -> exec();
	}
	
}
