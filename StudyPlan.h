#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"

class Registrar; //forward class declaration

//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	struct Warnings {
		vector<string> moderate;
		vector<string> credits;
		vector<string> uniCOMIssues;
		vector<string> TrackCOMIssues;
		vector<string> TrackElectiveIssues;
		vector<string> uniElectiveIssues;
		vector<string> MajorCOMIssues;
		vector<string> MajorElectiveIssues;
		vector<string> Prereqwarning;
		vector<string>Coreqwarning;	
	};
	

	vector<AcademicYear*> plan;	//plan is a list of academic years
	string PlanNotes;
	Warnings  planWarning;

protected:
	AcademicYear* AcadYear;
	

	
	
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	void virtual DrawMe(GUI*) const;
	void SAVE(ofstream& filename);
	Course* Check_Course_coordinates_SP(int X_coor, int Y_coor);
	virtual ~StudyPlan();
	int getTotalUnivCredits() const;
	int getTotalMajorCredits() const;
	int getTotalTrackCredits()  const;
	int getTotalConcentrationCredits() const;
	int getTotalMinorCredits()  const;
	void Check_Coreq_studyplan();

	//Warnings getWarnings() const;
	vector<string> getPrereqwarning() const;
	vector<string> getCoreqwarning() const;
	vector<string> getuniCOMIssues() const;
	vector<string> getTrackCOMIssues() const;
	vector<string> getTrackElectiveIssues() const;
	vector<string> getuniElectiveIssues() const;
	vector<string> getMajorCOMIssues() const;
	vector<string> getMajorElectiveIssues() const;
	vector<AcademicYear*> getplan() const;

	vector<string>getcredits() const;
	
	Course* Check_Validity();
	

	void Check_Comp_Univ_Studyplan(Registrar* preg) ;
	void Check_Elective_Univ_Studyplan(Registrar* preg);

	void Check_Comp_Track_Studyplan(Registrar* preg) ;
	void Check_Elective_Track_Studyplan(Registrar* preg);

	void Check_Comp_Major_Studyplan(Registrar* preg);
	void Check_Elective_Major_Studyplan(Registrar* preg);
	
};

