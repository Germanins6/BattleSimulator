#ifndef _APPLICATION_
#define _APPLICATION_

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "Timer.h"
#include "PerfTimer.h"


#include <vector>

#include <iostream>
#include <fstream>
using namespace std;

#include "JSON/json.hpp"
using json = nlohmann::json;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleEditor* editor;
	ModuleRenderer3D* renderer3D;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

public:

	//Fps core
	float fps;
	float	dt;
	int cap;
	int	 capped_ms;
	PerfTimer				ptimer;
	Timer	ms_timer;
	Timer				frame_time;
	uint64				frame_count = 0;
	Timer				startup_time;
	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	//Engine configuration
	bool closeEngine;
	bool vsync;

	//JSON Stuff
	json config_file;
	string config_path;

private: 

	std::vector<Module*> list_modules;

};

extern Application* App;

#endif //_APPLICATION_