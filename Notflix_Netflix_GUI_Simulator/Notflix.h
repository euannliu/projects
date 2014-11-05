#ifndef NOTFLIX_H
#define NOTFLIX_H

#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cctype>

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QMainWindow>
#include <QFont>
#include <QtGui>
#include <QObject>
#include <QErrorMessage>
#include <QStyle>
#include <QMessageBox>
#include <QFrame>
#include <QScrollArea>
#include <QCloseEvent>

#include "Movie.h"
#include "User.h"

using namespace std;

class Notflix : public QMainWindow
{
	Q_OBJECT
	public:
		Notflix();
		Notflix(int argv, char* argc[]);
		~Notflix();
		
		QWidget *windowMovie;
		QWidget *windowKeyword;
		
		QPixmap *pixmapLogo;
		QPixmap *pixmapSide;
		QPixmap *pixmapBack;
		QPixmap *pixmapMovie;
		
		QLabel *labelPicture;
		QLabel *labelSide;
		QLabel *labelHeader;
		QLabel *labelBack;
		QLabel *labelMovie;
		QLabel *labelMovieTitle;
		QLabel *labelKeywords;
		
		QPushButton *buttonLogin;
		QPushButton *buttonNewUser;
		QPushButton *buttonQuit;
		QPushButton *buttonReturn;
		QPushButton *buttonRent;
		QPushButton *buttonNext;
		QPushButton *buttonRemove;
		QPushButton *buttonMovie;
		QPushButton *buttonKeyword;
		QPushButton *buttonLogout;
		
		QPushButton *buttonMQueue;
		QPushButton *buttonMExit;
		
		QPushButton *buttonKNext;
		QPushButton *buttonKQueue;
		QPushButton *buttonKExit;
		
		QLineEdit *inputLogin;
		QLineEdit *inputNewID;
		QLineEdit *inputNewName;
		QLineEdit *inputSearch;
		
		QLabel *labelText1;
		QLabel *labelText2;
		QLabel *labelMainText1;
		QLabel *labelMainText2;
		QLabel *labelMainText3;
		QLabel *labelMainText4;
		QLabel *labelMainText5;
		
		QFrame *frameQueue;
		QFrame *frameSearch;
		
		QWidget *widgetTitlebar;
		QWidget *widgetMainMenu;
		
		QErrorMessage *errorEmptyFields;
		QMessageBox *messageNotice;
		
		QWidget *widgetArea;
		QScrollArea *scrollArea;
		
	private slots:
		void Register();
		void Reg_Back();
		void Reg_Complete();
		void Main_Menu();
		void Search_Title();
		void Search_Keyword();
		
		void Return_Movie();
		void Queue_Rent();
		void Queue_Next();
		void Queue_Remove();
		void Logout();
		
		void M_Queue();
		void M_Exit();
		
		void K_Next();
		void K_Queue();
		void K_Exit();
		void K_Destructor();
	
	private:
		void K_Menu();
		void Read_Movie_Data();
		void Read_User_Data();
		void Read_Data(int argv, char* argc[]);
		void Initialize();
		void Search_Movie();
		
		void closeEvent(QCloseEvent *event);
		
		//Declarations
		Set<Movie*> *moviebank; //to store multiple movies
		Set<Movie*>::Iterator mb_iterator; 
		Set<User*> *userbank; //to store multiple users
		Set<User*>::Iterator ub_iterator;
		Set<string> *keywordbank;
		Set<string>::Iterator kb_iterator;
		Queue<Movie*> q_movies;

		ifstream file; //to contain and load a file
		ofstream fileo; //to read out to a file

		stringstream ss; //to process data in a file
		string line, input_one, input_two; //to help extract data from a file
		string file_user, file_movie; //to help extract data from loading file
		string user_id, user_name, user_movie; //to help extract data from user file
		string movie_title, movie_keyword, movie_compare; //to help extract data from movie file

		Movie* movie; //to hold movie data
		User* user; //to hold user data

		Movie* read_movie;

		Movie ** hold_movie;
		string * hold_keyword;

		int input_int; //int input
		string input_string; //string input

		int movie_count, keyword_match_count, hold_count, hold_kcount;
		bool begin, user_check, movie_check, fileokay;	

		bool crash;
		bool in_menu;
		
		int counter_one;
		int counter_two;
		bool counter_check;
};

#endif
