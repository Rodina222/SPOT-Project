#pragma once
#include"Actions/Action.h"
#include"StudyPlan/StudyPlan.h"
//Class responsible for displaying course information  action
class ActionDisplayCourseInfo : public Action
{
public:
	ActionDisplayCourseInfo(Registrar*);
	bool virtual Execute();
	virtual ~ActionDisplayCourseInfo();
	
};




