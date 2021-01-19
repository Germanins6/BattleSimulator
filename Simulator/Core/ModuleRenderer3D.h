#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/glew.h"

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

public:
	SDL_GLContext context;

	bool depth_test;
	bool cull_face;
	bool lighting;
	bool mat_color;
	bool texture;
	bool wireframe_mode;
	bool vsync_active;
};