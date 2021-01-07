#pragma once
#include <list>
#include<vector>
#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"
using namespace std;

//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	int year;
	
public:
	AcademicYear();
	virtual ~AcademicYear();

	void SAVE(ofstream& file);

	bool AddCourse(Course*, SEMESTER );
	Course* Check_Course_coordinates(int X_coor,int Y_coor);
	void virtual DrawMe(GUI*) const;
	vector<string> check_Coreq() const;
	bool Check_Course(string code);
	
};


