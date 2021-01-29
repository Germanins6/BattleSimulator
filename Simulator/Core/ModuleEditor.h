#pragma once
#include "Module.h"
#include "Globals.h"

#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Serialization.h"

#include <string>
#include <vector>

//Forward declaration
class Character;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	//Docking Helper functions
	bool DockingRootItem(char* id, ImGuiWindowFlags winFlags);
	void BeginDock(char* dockSpaceId, ImGuiDockNodeFlags dockFlags, ImVec2 size = { .0f, .0f });

	//Core Update functions to show and manage windows
	void MenuBar();
	void UpdateWindowStatus();

	//Console Text Pushback
	void UpdateText(const char* consoleText);

	void CreateCharacter(std::string name, int vit, int wis, int str, int agi, int def, int arc_def, int ctrl);
	void ShowCharacters(Character* character);
	void StoreData();
	void ResetCharacters();

public:

	float window_width, window_height;

	//Window status control
	bool show_console_window;
	bool show_characters_window;
	bool show_stats_window;
	bool show_battle_window;
	bool show_graph_window;

	int simulations;

	ImGuiTextBuffer console_text;
	ImGuiTreeNodeFlags tmp_flags;

	std::vector<Character*> characters;
	Character* character_selected;

	Serializer data;

};