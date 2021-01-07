#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include"../Registrar.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include<string>


GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
	
}

void GUI::Open_Window(Course* P_course)
{
	int msg_x = 15;
	int msg_y = StatusBarHeight + 50;
	p_Infowind = new window(W, L, Start, End);
	p_Infowind->ChangeTitle(InfowindTitle);
	p_Infowind->SetFont(20, BOLD, BY_NAME, "Arial");
	p_Infowind->SetPen(MsgColor);
	p_Infowind->DrawString(msg_x, L - msg_y, P_course->getCode());
	p_Infowind->DrawString(msg_x, L - msg_y, P_course->getTitle());
	stringstream int_to_string;  //here,I am changing the credits from int to be string.
	int_to_string << P_course->getCredits();
	string str = int_to_string.str();
	p_Infowind->DrawString(msg_x, L - msg_y, str);
	for (auto prereq = P_course->getPreReq().begin(); prereq != P_course->getPreReq().end(); ++prereq)
	{
		p_Infowind->DrawString(msg_x, L - msg_y, *prereq);
	}
	for (auto coreq = P_course->getCoReq().begin(); coreq != P_course->getCoReq().end(); ++coreq)
	{
		p_Infowind->DrawString(msg_x, L - msg_y, *coreq);

	}
}
	


	

//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\Menu_SAVE.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD , BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd<< "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();

	///TODO: compelete this function to:
	// 1- Draw a rectangle for the academic year
	pWind->SetBrush(BACKGROUND_RED);
	pWind->SetPen(BLACK, 2);
	ifstream infile;
	int i = 0;
	int j = 0;
	string line = "";
	string year = "";
	string semester = "";
	infile.open("CIE-StudyPlan.txt");
	if (!infile.is_open()) {
		cout << "FIle failed\n";
	}
	else {
		while (getline(infile, line))
		{
			pWind->SetPen(BLACK);
			while (line[j] != ',') {
				year = year + line[j];
				++j;
			}
			if (i % 3 == 0) {
				pWind->SetFont(16, 2, ROMAN);
				pWind->DrawString(4, WindHeight - StatusBarHeight - 6 - YearHeight * i - 50, year);
				pWind->DrawRectangle(0, WindHeight - StatusBarHeight - 6 - YearHeight * i - 6, 60, ((WindHeight - StatusBarHeight - YearHeight - YearHeight * (i + 2)) - 2) + 2, FRAME, 7, 7);
			}
			year = "";
			++j;
			while (line[j] != ',') {
				semester = semester + line[j];
				++j;
			}
			pWind->DrawRectangle(62, WindHeight - StatusBarHeight - 6 - YearHeight * i, 120, (WindHeight - StatusBarHeight - YearHeight - YearHeight * i) - 2, FRAME, 7, 7);
			pWind->SetFont(15, 1, ROMAN);
			pWind->DrawString(65, WindHeight - StatusBarHeight - 27 - YearHeight * i, semester);
			pWind->SetPen(SKYBLUE);
			pWind->DrawLine(60, WindHeight - StatusBarHeight - 6 - YearHeight * i - 0.5, WindWidth, WindHeight - StatusBarHeight - 6 - YearHeight * i - 0.5);
			pWind->SetPen(SKYBLUE, 2);
			if (i % 3 == 0) {
				pWind->DrawLine(0, WindHeight - StatusBarHeight - 8 - YearHeight * i, WindWidth, WindHeight - StatusBarHeight - 8 - YearHeight * i);
			}
			++i;
			j = 0;
			semester = "";
		}
	}
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_EXIT: return ActionData{ EXIT };		//Exit
			    case ITM_SAVE: return ActionData{ SAVE };   //save current plan

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	

	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








GUI::~GUI()
{
	delete pWind;
	delete p_Infowind;
}
