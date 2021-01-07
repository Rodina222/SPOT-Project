#pragma once
#include <string.h>
#include<iostream>
#include"../Rules.h"
#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"

using namespace std;

class Course;
class AcademicYear;
class Registrar;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course

		ITM_SAVE,  //save current study plan

						//TODO: Add more items names here


		ITM_EXIT,		//Exit item

		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};

	//Some constants for GUI
	static const int	WindWidth = 1000, WindHeight = 600,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 80,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 70,	//Width of each item in the menu
	    YearHeight = 30;

	static const int W = 500, L = 200, Start = 100, End = 200; //Info_window data


	color DrawColor = BLACK;		//Drawing color
	color FillColor = YELLOW;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLUE;			//Messages color
	color BkGrndColor = LIGHTGRAY;	//Background color
	color StatusBarColor = DARKGRAY;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";
	string InfowindTitle = "Course Information";

	window* pWind;
	window* p_Infowind;
	Registrar* P_reg;

public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar
	void Open_Window(Course*); //Create window for displaying course information 
	
	

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course* );
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;


	
	

	~GUI();
};

