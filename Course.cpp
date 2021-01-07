#include "Course.h"
#include"../StudyPlan/AcademicYear.h"
#include "../GUI/GUI.h"
#include<iostream>
using namespace std;


Course::Course(Course_Code r_code, string r_title, int crd): code(r_code),Title(r_title)
{
	credits = crd;
}


 
Course* Course::get_Specified_Course(int X_coor,int Y_coor) 
{
	
	if(((X_coor > x_Coordinate) && (X_coor < (x_Coordinate + CRS_WIDTH))) && ((Y_coor > y_Coordinate) && (Y_coor < (y_Coordinate + CRS_HEIGHT))))
	{
		return this;
	}
	else
		return nullptr;
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}

string Course::getType() const
{
	return type;
}

list<Course_Code> Course::getPreReq() const
{

	return PreReq;
		
}

list<Course_Code> Course::getCoReq()  const
{
	
	return CoReq;
		
}


void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

int Course::getx_Coordinate() const
{
	return x_Coordinate;
}
int Course::gety_Coordinate() const
{
	return y_Coordinate;
}



void Course::SaveMe(ofstream& file)
{
	
	file << code << ",";
	file.close();
}

void Course::setX(int x)
{
	x_Coordinate=x;

}

void Course::setY(int y)
{
	y_Coordinate-=y;
}

Course::~Course()
{

	
}

