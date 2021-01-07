#include "ActionDisplayCourseInfo.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include<iostream>
using namespace std;


ActionDisplayCourseInfo::ActionDisplayCourseInfo(Registrar* p) :Action(p)
{

}

bool ActionDisplayCourseInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	
	
	ActionData actData = pGUI->GetUserAction();
	
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		string courseC;
		StudyPlan* pS = pReg->getStudyPlay();
		Course* Pcourse=pS->Check_Course_coordinates_SP(x, y);
		pGUI->Open_Window(Pcourse);
	}


	return true;
}










ActionDisplayCourseInfo::~ActionDisplayCourseInfo()
{
	
}


