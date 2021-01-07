#include "StudyPlan.h"
#include "AcademicYear.h"
#include"../Rules.h"
#include"../Registrar.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;



StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years+

	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
}




//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}
void StudyPlan::SAVE(ofstream& file)
{
	
	for (int r = 0; r < plan.size(); r++)
	{
		AcademicYear* pAcademicYear;
		file << "year" << r + 1;
		 pAcademicYear= plan[r];
		pAcademicYear->SAVE(file);
		cout << endl;	
	}
	
}

Course* StudyPlan::Check_Course_coordinates_SP(int X_coor, int Y_coor) 
{
	AcademicYear* pYear;
	for (auto year = 0; year < plan.size(); year++)
	{
		pYear = plan[year];
		Course* pCourse = pYear->Check_Course_coordinates(X_coor, Y_coor);
		if (pCourse != nullptr)
			return pCourse;
	}
	return nullptr;
}



//Course* StudyPlan::Check_Validity() //compare the Prerequisites of a certain course in the study plan of the student with that is found in the course catalog
//{
//	AcademicYear* pAcademicYear;
//	
//	for (auto year = 0; year < plan.size(); year++)
//	{
//		pAcademicYear = plan[year];
//		Course* pCOURSE = pAcademicYear->Return_Course_Pointer(); //returns pointer on every course in the study plan.
//		if (pCOURSE != nullptr)
//			return pCOURSE;
//	}
//	return nullptr;
//	
//}
vector<string> StudyPlan::getcredits() const
{
	return  planWarning.credits;
}

int StudyPlan::getTotalMajorCredits() const
{
	return TotalMajorCredits;
}
int StudyPlan::getTotalTrackCredits()  const
{
	return TotalTrackCredits;
}
int StudyPlan::getTotalConcentrationCredits()  const
{
	return TotalConcentrationCredits;
}
int StudyPlan::getTotalMinorCredits()  const
{
	return TotalMinorCredits;
}
int StudyPlan::getTotalUnivCredits() const
{
	return TotalUnivCredits;
}


vector<string> StudyPlan::getPrereqwarning() const
{
	return planWarning.Prereqwarning;
}
vector<string> StudyPlan::getCoreqwarning() const
{
	return planWarning.Coreqwarning;
}

vector<string> StudyPlan::getuniCOMIssues() const
{
	return planWarning.uniCOMIssues;
}
vector<string> StudyPlan::getuniElectiveIssues() const
{
	return planWarning.uniElectiveIssues;
}
vector<string> StudyPlan::getTrackCOMIssues() const
{
	return planWarning.TrackCOMIssues;
}
vector<string> StudyPlan::getTrackElectiveIssues() const
{
	return planWarning.TrackElectiveIssues;
}

vector<string> StudyPlan::getMajorCOMIssues() const
{
	return planWarning.MajorCOMIssues;
}
vector<string> StudyPlan::getMajorElectiveIssues() const
{
	return  planWarning.MajorElectiveIssues;
}
vector<AcademicYear*> StudyPlan::getplan() const
{
	return plan;
}

void StudyPlan::Check_Coreq_studyplan() 
{
	
	for (auto year = 0; year < plan.size(); year++)
	{
		AcadYear = plan[year];
		vector <string> course_codes= AcadYear->check_Coreq();

		for (int r = 0; r < course_codes.size(); r++)
		{
			planWarning.Coreqwarning.push_back(course_codes[r]);
		}

	}
	
}

void StudyPlan::Check_Comp_Univ_Studyplan(Registrar* preg)
{
	
	string coursecode_UC;
	
	for (int i=0;i<preg->getRegRules().UnivCompulsory.size();i++)
	{
		coursecode_UC = preg->getRegRules().UnivCompulsory[i];

		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result = AcadYear->Check_Course(coursecode_UC); //function in the academic year that check if all the UnivCompulsory courses of the vector are in the study plan of the student.
			
			if (result == false)
			{
				planWarning.uniCOMIssues.push_back(coursecode_UC);
			}
		}
		
	}
	
}
void StudyPlan::Check_Elective_Univ_Studyplan(Registrar* preg) 
{
	string coursecode_UE;
	
	for (int i=0;i< preg->getRegRules().UnivElective.size();i++)
	{
		coursecode_UE = preg->getRegRules().UnivElective[i];

		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result = AcadYear->Check_Course(coursecode_UE); //function in the academic year that check if all the UnivElective courses of the vector are in the study plan of the student
			if (result == false)
			{
				planWarning.uniElectiveIssues.push_back(coursecode_UE);
			}
		}
		
	}

}
void StudyPlan::Check_Comp_Track_Studyplan(Registrar* preg) 
{
	string coursecode_CT;

	for (int i = 0; i < preg->getRegRules().TrackCompulsory.size(); i++)
	{
		coursecode_CT = preg->getRegRules().TrackCompulsory[i];
		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result = AcadYear->Check_Course(coursecode_CT); //function in the academic year that check if all the Track compulsory courses of the vector are in the study plan of the student
			if (result == false)
			{
				planWarning.TrackCOMIssues.push_back(coursecode_CT);
			}
		}

	}
}

void StudyPlan::Check_Elective_Track_Studyplan(Registrar* preg) 
{
	string coursecode_ET;
	
	for (int i = 0; i < preg->getRegRules().TrackElective.size(); i++)
	{
		coursecode_ET = preg->getRegRules().TrackElective[i];
		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result = AcadYear->Check_Course(coursecode_ET); //function in the academic year that check if all the Track compulsory courses of the vector are in the study plan of the student
			if (result == false)
			{
				planWarning.TrackElectiveIssues.push_back(coursecode_ET);
			}
		}

	}

}



void StudyPlan::Check_Comp_Major_Studyplan(Registrar* preg) 
{
	string coursecode_CM;

	
	for (int i = 0; i < preg->getRegRules().MajorCompulsory.size(); i++)
	{
		coursecode_CM = preg->getRegRules().MajorCompulsory[i];

		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result = AcadYear->Check_Course(coursecode_CM); //function in the academic year that check if all the mAJOR compulsory courses of the vector are in the study plan of the student
			if (result == false)
			{
				planWarning.MajorCOMIssues.push_back(coursecode_CM);
			}
		}

	}

}
void StudyPlan::Check_Elective_Major_Studyplan(Registrar* preg) 
{
	string coursecode_EM;

	for (int i = 0; i < preg->getRegRules().MajorElective.size(); i++)
	{
		coursecode_EM = preg->getRegRules().MajorElective[i];
		for (auto year = 0; year < plan.size(); year++)
		{
			AcadYear = plan[year];
			bool result= AcadYear->Check_Course(coursecode_EM); //function in the academic year that check if all the mAJOR compulsory courses of the vector are in the study plan of the student
			if (result == false)
			{
				planWarning.MajorElectiveIssues.push_back(coursecode_EM);
			}
		}

	}


}


StudyPlan::~StudyPlan()
{
	
	
}
