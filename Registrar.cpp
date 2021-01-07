#include "Registrar.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include<string.h>
#include<vector>
#include"Rules.h"
#include "Actions/ActionAddCourse.h"
#include"ActionSavePlan.h"


using namespace std;

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	LoadCatalog();
	
	
}


//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}
//string CourseTitle;
//string CourseType;
//string Coreqlist;
//string prerequisit;

//CourseInfo Registrar::getCourseInfo(Course* course)  const
//{
//	CourseInfo COURSE_INFO;
//	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) 
//	{
//		if (RegRules.CourseCatalog[i].Code == course->getCode())
//		{
//			 COURSE_INFO.Code=course->getCode();
//
//			COURSE_INFO.Title=course->getTitle();
//
//		    COURSE_INFO.Credits= course->getCredits();
//
//			for (int t = 0; t < COURSE_INFO.PreReqList.size(); t++)
//			COURSE_INFO.PreReqList[t] = course->getPreReq();
//
//			for (int r = 0; r < COURSE_INFO.CoReqList.size(); r++)
//		   COURSE_INFO.CoReqList[r]= course->getCoReq();
//			
//		}
//		
//	}
//	return COURSE_INFO;
//}


Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;

	case SAVE: //save current study plan
		RequiredAction = new ActionSavePlan(this);
	  break;

	

	//TODO: Add case for each action
	
	case EXIT:
		break;
		
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}
 

  void Registrar::SavePlan(ofstream& file)
{
	  pSPlan->SAVE(file);
	  
}
  

  Registrar* Registrar::getRegistrar()
  {
	 
	  pSPlan->Check_Elective_Univ_Studyplan(this);
	  pSPlan->Check_Elective_Univ_Studyplan(this);

	  pSPlan->Check_Elective_Univ_Studyplan(this);
	  pSPlan->Check_Elective_Univ_Studyplan(this);

	  pSPlan->Check_Elective_Univ_Studyplan(this);
	  pSPlan->Check_Elective_Univ_Studyplan(this);
	  return this;
  }

  
	  

  /*void Registrar::LoadCatalog()
  {

	  CourseInfo cinfo;

	  ifstream file;
	  file.open("D:\\CIE-year 2\\CIE 202 _C++\\ProjectFiles\\Catalog - 2020 12 19.txt");          ////change file
	  if (!file.is_open())
	  {
		  cout << "File open failure!";
	  }
	  string LineOfCode = "";
	  string restofline = "";
	  string prereq = "";
	  string CRDS = "";
	  int crds = 0;
	  list<string>PreReqList;
	  list<string>CoReqList;

	  while (getline(file, LineOfCode))
	  {
		  //cout << LineOfCode << endl;
		  stringstream cc(LineOfCode);
		  getline(cc, cinfo.Code, ',');
		  //cout << cinfo.Code << endl;
		  getline(cc, cinfo.Title, ',');
		  //cout << cinfo.Title << endl;
		  getline(cc, CRDS, ',');
		  stringstream string_to_int(CRDS);//we declared the line as a string so this function makes casting for the number of credits to be an integer.
		  string_to_int >> crds;
		  cinfo.Credits = crds;
		  //cout << cinfo.Credits;

		  getline(cc, restofline, ',');
		  if (restofline.empty())
			  continue;

		  cout << restofline << endl;
		  stringstream ss(restofline);
		  string temp;
		  string course, num;
		  string coursecode;
		  ss >> temp;
		  if (temp == "Coreq:") {
			  while (temp != "") {
				  ss >> course;
				  ss >> num;
				  coursecode = course + " " + num;
				  CoReqList.push_back(coursecode);
				  ss >> temp;

			  }
			  cout << coursecode << endl;

		  }
		  cout << temp << endl;
		  ss >> temp;
		  cout << temp << endl;
		  ss >> temp;
		  cout << temp << endl;

		  getline(cc, restofline, ',');
		  if (restofline.empty())
			  continue;

		  cout << restofline << endl;
		  stringstream rr(restofline);
		  string temporary;
		  string coursee, number;
		  string ccode;
		  rr >> temporary;
		  
			  while (temporary != "") {
				  rr >> coursee;
				  rr >> number;
				  ccode = coursee + " " + number;
				  PreReqList.push_back(ccode);
				  rr >> temporary;

			  }
			  cout << ccode << endl;

		  
		  cout << temporary << endl;
		  rr >> temporary;
		  cout << temporary << endl;
		  rr >> temporary;
		  cout << temporary << endl;
		 
		  RegRules.CourseCatalog.push_back(cinfo);
	  }

	  file.close();
  }*/
////##########################Load Catalog Mariam

void Registrar::LoadCatalog()
{

	CourseInfo cinfo;
	string LineOfCode = "";
	string restofline = "";
	string CRDS = "";
	int crds = 0;
	string Code;
	string Title;
	string temp;
	string  num;
	string coursecode;
	string newtemp;
	ifstream file;
	file.open("Catalog - 2020 12 19.txt");
	if (!file.is_open())
	{
		cout << "File open failure!";
	}
	while (getline(file, LineOfCode))
	{
		//###################################################
		  // this part for code and title and credits
		stringstream cc(LineOfCode);
		getline(cc, Code, ',');       // get the code of the course
		cinfo.Code = Code;
		getline(cc, Title, ',');      //get Course Title
		cinfo.Title = Title;
		getline(cc, CRDS, ',');
		stringstream Crd(CRDS);   //we declared the line as a string so this function makes casting for the number of credits to be an integer.
		Crd >> crds;
		cinfo.Credits = crds;
		//###################################################

		getline(cc, restofline, ',');
		///  Case of there is no prerequisite or corequisite for this course
		if (restofline.empty()) {
			RegRules.CourseCatalog.push_back(cinfo);
			continue;
		}


		// case of there is a corequisite put the list of corequisite in restofline
		stringstream ss(restofline);
		ss >> temp;
		if (temp == "Coreq:") {
			ss >> Code;
			ss >> num;
			coursecode = Code + " " + num;
			cinfo.CoReqList.push_back(coursecode);
		}

		restofline = "";
		getline(cc, restofline, ',');


		//######################################################
		// in case of there is no prereq  only coreq for the course

		if (restofline.empty()) {
			RegRules.CourseCatalog.push_back(cinfo);
			continue;
		}
		/// #####################################################
		//Case of there is a prerequisite
		stringstream preline(restofline);        // Put prerequisite list in preline 
		preline >> newtemp;
		if (newtemp == "Prereq:") {
			preline >> Code;
			preline >> num;
			coursecode = Code + " " + num;
			cinfo.PreReqList.push_back(coursecode);       // first prerequisite course

			newtemp = "";
			preline >> newtemp;
			if (newtemp.empty()) {             // only one prerequisite
				RegRules.CourseCatalog.push_back(cinfo);
				continue;
			}

			while (newtemp == "And") {                // multiiple prerequisite
				preline >> Code;
				preline >> num;
				coursecode = Code + " " + num;
				cinfo.PreReqList.push_back(coursecode);
				newtemp = "";
				preline >> newtemp;
			}

		}
		RegRules.CourseCatalog.push_back(cinfo);

	}


	file.close();
}

  vector<Course_Code> Registrar::getCatalogPrereq(string coursecode)
  {

	  for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	  {
		  if (RegRules.CourseCatalog[i].Code == coursecode && !RegRules.CourseCatalog[i].PreReqList.empty())
		  {
			  return RegRules.CourseCatalog[i].PreReqList;
		  }
	  }
  }

vector <Course_Code> Registrar::getCatalog_Coreq(string coursecode)
  {

	  for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	  {
		  if (RegRules.CourseCatalog[i].Code == coursecode && !RegRules.CourseCatalog[i].CoReqList.empty())
		  {
			  return RegRules.CourseCatalog[i].CoReqList;
		  }
	  }
  }

	
  //################################### Mariam##################################
  MyYearAndSemester& Registrar::GetYearAndSem(int y) {

	  if (y < 540 && y >= 450) {
		  if (y <= 540 && y >= 514) {

			  YandS.Year = 1;
			  YandS.sem = FALL;

			  return YandS;
		  }
		  if (y < 514 && y >= 488) {

			  YandS.Year = 1;
			  YandS.sem = SPRING;

			  return YandS;
		  }

		  if (y < 488 && y >= 450) {

			  YandS.Year = 1;
			  YandS.sem = SUMMER;

			  return YandS;
		  }

	  }
	  else if (y < 450 && y >= 370)
	  {
		  if (y <= 460 && y >= 434) {

			  YandS.Year = 2;
			  YandS.sem = FALL;

			  return YandS;
		  }

		  if (y < 434 && y >= 408) {

			  YandS.Year = 2;
			  YandS.sem = SPRING;

			  return YandS;
		  }

		  if (y < 408 && y >= 370) {

			  YandS.Year = 1;
			  YandS.sem = SUMMER;

			  return YandS;
		  }

	  }
	  else if (y < 370 && y >= 290) {
		  if (y < 380 && y >= 354) {

			  YandS.Year = 3;
			  YandS.sem = FALL;

			  return YandS;
		  }

		  if (y < 354 && y >= 328) {

			  YandS.Year = 3;
			  YandS.sem = SPRING;

			  return YandS;
		  }

		  if (y < 328 && y >= 290) {

			  YandS.Year = 3;
			  YandS.sem = SUMMER;

			  return YandS;
		  }

	  }
	  else if (y < 290 && y >= 210) {
		  if (y <= 290 && y >= 274) {

			  YandS.Year = 4;
			  YandS.sem = FALL;

			  return YandS;
		  }

		  if (y < 274 && y >= 248) {

			  YandS.Year = 4;
			  YandS.sem = SPRING;

			  return YandS;
		  }
		  if (y < 248 && y >= 210) {

			  YandS.Year = 4;
			  YandS.sem = SUMMER;

			  return YandS;
		  }

	  }
	  else if (y < 210 && y >= 100) {
		  if (y < 210 && y >= 194)
		  {

			  YandS.Year = 5;
			  YandS.sem = FALL;

			  return YandS;
		  }
		  if (y < 194 && y >= 168)
		  {

			  YandS.Year = 5;
			  YandS.sem = SPRING;

			  return YandS;
		  }
		  if (y < 168 && y >= 100)
		  {
			  YandS.Year = 5;
			  YandS.sem = SUMMER;

			  return YandS;
		  }

	  }
	  else {
		  YandS.Year = 1;
		  YandS.sem = FALL;
		  return YandS;
	  }

  }

  CourseInfo Registrar::getCourseInfo(string code) {

	  vector<CourseInfo> Catalog = getCourseCatalog();

	  for (int i = 0; i < Catalog.size(); i++) {
		  if (code == Catalog[i].Code)
			  return Catalog[i];
	  }
  }

  Rules& Registrar::getRegRules() 
  {
	  return RegRules;

  }




  vector<CourseInfo> Registrar::getCourseCatalog() {
	  return RegRules.CourseCatalog;
  }



   void Registrar::Check_Credits() const
  {
	  string result_Univ_Crds;
	  string result_Track_Crds;
	  string result_Major_Crds;
	  string Total_Crds;
	 

	  int totalUnivcrds = pSPlan->getTotalUnivCredits();
	  int TrackCrds = pSPlan->getTotalTrackCredits();
	  int MajorCrds = pSPlan->getTotalMajorCredits();

	  if ((RegRules.ReqUniv_CompCredits + RegRules.ReqUniv_electiveCredits) != totalUnivcrds) //Checking the total university credits (compulsory & elective)
	  {
		  result_Univ_Crds = "University credits are incomplete!";
		  pSPlan->getcredits().push_back(result_Univ_Crds);
	  }
	  else
	  {
		  result_Univ_Crds = " ReqUniv_CompCredits are complete";
	  }

	  if (RegRules.ReqTrackCredits != TrackCrds)  //Checking the total Track credits
	  {
		  result_Track_Crds = "Track credits are  incomplete!";
		  pSPlan->getcredits().push_back(result_Track_Crds);
	  }
	  else
	  {
		  result_Track_Crds = " Track credits are complete";
	  }

	  if ((RegRules.ReqMajor_CompCredits + RegRules.ReqMajor_electiveCredits) != MajorCrds)  //Checking the total Major credits
	  {
		  result_Major_Crds = "Major credits are  incomplete!";
		  pSPlan->getcredits().push_back(result_Major_Crds);
	  }
	  else
	  {
		  result_Major_Crds = " Major credits are complete";
	  }

	  if (RegRules.total_Credits != (totalUnivcrds + MajorCrds + TrackCrds)) //Checking the total credits (all types together)
	  {
		  Total_Crds = "Total credits are  incomplete!";
		  pSPlan->getcredits().push_back(Total_Crds);
	  }
	  else
	  {
		  Total_Crds = "Total  credits are complete";
	  }


  }

	  

	
	  Registrar::~Registrar()
	  {
		  delete pSPlan;
		  delete pGUI;

	  }
	




	
	
		
	



	





