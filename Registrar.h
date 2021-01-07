#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
#pragma once
struct MyYearAndSemester {
	int Year;
	SEMESTER sem;
};
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	MyYearAndSemester YandS;      // Mariam
	void LoadCatalog(); //by me
	
	

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	Registrar* getRegistrar();
	Rules& getRegRules();
	//CourseInfo getCourseInfo(Course*) const; //by me
	
	vector<Course_Code> getCatalogPrereq(string coursecode);

	vector<Course_Code> getCatalog_Coreq(string coursecode);

	void SavePlan(ofstream& filename);
	
	/// ////////////

	CourseInfo getCourseInfo(string code);
	MyYearAndSemester& GetYearAndSem(int y);
	vector<CourseInfo> getCourseCatalog();
	void Run();
	void Check_Credits()  const;
	
	

	~Registrar();
};

