#include "AcademicYear.h"
#include "..\Courses\Course.h"
#include "../GUI/GUI.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#include"StudyPlan.h"
using namespace std;

AcademicYear::AcademicYear()
{
	

	//TODO: make all necessary initializations
}




//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}


void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}

void AcademicYear::SAVE(ofstream& file)
{
	
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		
		file << sem << ",";

		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			Course* PCourse;
			PCourse = *course;
			PCourse->SaveMe(file);

		}
		cout << endl;
		
	}
	
	
}

Course* AcademicYear::Check_Course_coordinates(int X_coor, int Y_coor) 
{
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{


		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			Course* pCourse;
			pCourse = *course;
			if (pCourse->get_Specified_Course(X_coor, Y_coor) != nullptr)
				return pCourse;
			 

		}	

	}
	return nullptr;
}


vector<string> AcademicYear::check_Coreq() const
{
	list<string>coreq;
	int index = 0;
	string code="";
	vector<string>course_code;

	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			
			Course* pCOURSE;
			pCOURSE = *course;
			 coreq=pCOURSE->getCoReq();
			 
			 
			 for (auto cor = coreq.begin(); cor != coreq.end(); ++cor)
			 {
				 index = 0;

				 for (auto COREQ = YearCourses[sem].begin(); COREQ != YearCourses[sem].end(); ++COREQ)
				 {

					 if ((*COREQ)->getCode() == (*cor))
					 {
						 index = 1;

						 code = pCOURSE->getCode();
						 break;

					 }

				 }
				 if (index != 1)
				 {
					 course_code.push_back(code);

				 }
			 }
		}
	}
	return  course_code;
}

/*Course* pCOURSE;
			pCOURSE = *course;

			if(pCOURSE!=nullptr)
			return pCOURSE;*/


bool AcademicYear::Check_Course(string code)
{
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{

		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{

			if ((*course)->getCode() == (code))//situation = "course is found"
				return true;
			
		}
	}

	//situation = "course is not found!";
	return false;
			
}

	

			
AcademicYear::~AcademicYear()
{

}