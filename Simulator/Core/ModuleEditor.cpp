//Modules
#include "Application.h"
#include "ModuleEditor.h"
#include "Character.h"

//Tools
#include "Globals.h"
#include <string>
#include "ImGui/imgui_internal.h"
#include <gl/GL.h>
#include <time.h>
#include <math.h>

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    show_console_window = true;
    show_characters_window = true;
    show_stats_window = true;
    show_battle_window = true;
    show_graph_window = true;

    simulations = 10;

    character_selected = nullptr;
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init() {
    bool ret = true;
  
    CreateCharacter("Sura", 600, 10, 5, 10, 3, 2, 6);
    CreateCharacter("Kiran", 800, 20, 10, 3, 3, 4, 10);
    CreateCharacter("Nathan", 400, 10, 2, 13, 1, 5, 3);
    CreateCharacter("Iqniq", 1500, 25, 17, 5, 7, 6, 14);

    srand(time(NULL));

    return ret;
}

// Called before render is available
bool ModuleEditor::Start()
{
	bool ret = true;
	
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup ImGui style by default
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
	ImGui_ImplOpenGL3_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);


    return ret;
}

update_status ModuleEditor::PreUpdate(float dt) {

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    return UPDATE_CONTINUE;

}

// PreUpdate: clear buffer
update_status ModuleEditor::Update(float dt)
{
   //Creating MenuBar item as a root for docking windows
   if (DockingRootItem("Viewport", ImGuiWindowFlags_MenuBar)) {
       MenuBar();
       ImGui::End();
   }

   //Update status of each window and shows ImGui elements
   UpdateWindowStatus();
        
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float dt) {

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Rendering
    ImGui::Render();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    ImGui::EndFrame();

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    for (size_t i = 0; i < characters.size(); i++)
        RELEASE(characters[i]);

	return true;
}


void ModuleEditor::UpdateText(const char* consoleText) {
    console_text.appendf(consoleText);
}

bool ModuleEditor::DockingRootItem(char* id, ImGuiWindowFlags winFlags)
{
    //Setting windows as viewport size
    ImGuiViewport* viewport = ImGui::GetWindowViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    
    //Setting window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, .0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, .0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, .0f);

    //Viewport window flags just to have a non interactable white space where we can dock the rest of windows
    winFlags |= ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar;
    winFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;

    bool temp = true;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    temp = ImGui::Begin(id, &temp, winFlags);
    ImGui::PopStyleVar(3);

    BeginDock(id, ImGuiDockNodeFlags_PassthruCentralNode);

    return temp;
}

void ModuleEditor::BeginDock(char* dockSpaceId, ImGuiDockNodeFlags dockFlags, ImVec2 size)
{
    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dock = ImGui::GetID(dockSpaceId);
        ImGui::DockSpace(dock, size, dockFlags);
    }
}

void ModuleEditor::MenuBar() {

    /* ---- MAIN MENU BAR DOCKED ----*/
    if (ImGui::BeginMainMenuBar()) {

        /* ---- WINDOW ----*/
        if (ImGui::BeginMenu("Window")) {

            if (ImGui::BeginMenu("Workspace Style")) {
                if (ImGui::MenuItem("Dark")) ImGui::StyleColorsDark();
                if (ImGui::MenuItem("Classic")) ImGui::StyleColorsClassic();
                if (ImGui::MenuItem("Light")) ImGui::StyleColorsLight();
                if (ImGui::MenuItem("Custom")) ImGui::StyleColorsCustom();
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Console")) show_console_window = !show_console_window;
            ImGui::EndMenu();
        }

        /* ---- HELP ---- */
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Download Latest")) ShellExecute(NULL, "open", "https://github.com/Germanins6/BattleSimulator/releases", NULL, NULL, SW_SHOWNORMAL);
            if (ImGui::MenuItem("Report Issue")) ShellExecute(NULL, "open", "https://github.com/Germanins6/BattleSimulator/issues", NULL, NULL, SW_SHOWNORMAL);
            ImGui::EndMenu();
        }
    }

    ImGui::EndMainMenuBar();
}

void ModuleEditor::UpdateWindowStatus() {

    //Console
    if (show_console_window) {

        ImGui::Begin("Battle Log");
        ImGui::TextUnformatted(console_text.begin(), console_text.end());
        ImGui::End();
    }

    if (show_characters_window) {
        ImGui::Begin("Characters");

        for (size_t i = 0; i < characters.size(); i++)
            ShowCharacters(characters[i]);

        ImGui::TextUnformatted("Select Character By Index");
        int index = 0;
        if(ImGui::SliderInt("##Selection", &index, 1, 4))
            character_selected = characters[index - 1];


        ImGui::End();
    }

    if (show_stats_window) {
        ImGui::Begin("Character Stats");

        if (character_selected != nullptr) {

            //Level
            if(character_selected->level < 15)
                ImGui::Text("Level %i", character_selected->level);
            else
                ImGui::Text("Max Level Reached(15)");

            //Exp
            ImGui::Text("Experience %i", character_selected->experience);

            //Base stats
            ImGui::Text("Vitality");
            ImGui::DragInt("##Vitality", &character_selected->vitality);
            ImGui::SameLine();
            ImGui::InputFloat("Vitality", &character_selected->mod_vitality, 0.01, 1.0f, "%.2f");

            ImGui::Text("Wisdom");
            ImGui::DragInt("##Wisdom", &character_selected->wisdom);
            ImGui::SameLine();
            ImGui::InputFloat("Wisdom", &character_selected->mod_wisdom, 0.01, 1.0f, "%.2f");

            ImGui::Text("Strength");
            ImGui::DragInt("##Strength", &character_selected->strength);
            ImGui::SameLine();
            ImGui::InputFloat("Strength", &character_selected->mod_strength, 0.01, 1.0f , "%.2f");

            ImGui::Text("Agility");
            ImGui::DragInt("##Agility", &character_selected->agility);
            ImGui::SameLine();
            ImGui::InputFloat("Agility", &character_selected->mod_agility, 0.01, 1.0f, "%.2f");

            ImGui::Text("Defense");
            ImGui::DragInt("##Defense", &character_selected->defense);
            ImGui::SameLine();
            ImGui::InputFloat("Defense", &character_selected->mod_defense, 0.01, 1.0f, "%.3f");

            ImGui::Text("Arcane Defense");
            ImGui::DragInt("##Arcane Defense", &character_selected->arcane_defense);
            ImGui::SameLine();
            ImGui::InputFloat("ArcaneDefense", &character_selected->mod_arcane_defense, 0.01, 1.0f, "%.2f");

            ImGui::Text("Control");
            ImGui::DragInt("##Control", &character_selected->control);
            ImGui::SameLine();
            ImGui::InputFloat("Control", &character_selected->mod_control, 0.01, 1.0f, "%.2f");

            //Upgrade level
            if (ImGui::Button("Upgrade Level"))
                if(character_selected->level < 15)
                    character_selected->UpgradeLevel();
        }

        ImGui::End();
    }

    if (show_battle_window) {
        ImGui::Begin("Round Simulator");


        ImGui::TextUnformatted("Simulate");
        ImGui::InputInt("##Rounds to Simulate", &simulations);        
        if (ImGui::Button("Start Simulations per Level")) {

            int levels = 1;
            while (levels <= 15) {
                LOG(" ///// Level %i /////", levels);
                for (size_t i = 0; i < simulations; i++)
                {
                    LOG("---- Simulation Round %i ----", i);

                    //Each round make action with characters
                    for (size_t i = 0; i < characters.size(); i++)
                    {
                        LOG("%s life: %i", characters[i]->char_name.c_str(), characters[i]->vitality);

                        //Do random action and calculate value
                        Actions action = (Actions)(rand() % 4);
                        float value = characters[i]->DoAction(action);

                        //Interactions depending character
                        if (characters[i]->char_name != "Iqniq") {

                            //Apply damage if attack, add vitality as shield and damage mitigated into vitality
                            if (action == Actions::PhysAttack || action == Actions::MagicAttack)
                                characters[3]->vitality -= value;
                            else
                                characters[i]->vitality += value;
                        }
                        else {

                            //Pick random between Sura, Kiran and Nathan
                            int randomCharacter = rand() % 3;

                            if (action == Actions::PhysAttack || action == Actions::MagicAttack)
                                characters[randomCharacter]->vitality -= value;
                            else
                                characters[i]->vitality += value;
                        }
                    }

                    //LOG("%i %i %i %i", characters[0]->vitality, characters[1]->vitality, characters[2]->vitality, characters[3]->vitality);
                }
                levels++;
            }
        }
       
        if (ImGui::Button("Reset Characters"))
            ResetCharacters();

        ImGui::SameLine();

        if (ImGui::Button("Save Current Values"))
            StoreData();

        ImGui::End();
    }

    if (show_graph_window) {
        ImGui::Begin("Graphs", &show_graph_window, ImGuiWindowFlags_NoScrollbar);
        static float values[90] = {};
        float average = 0.0f;
        for (int n = 0; n < IM_ARRAYSIZE(values); n++)
            average += values[n];
        average /= (float)IM_ARRAYSIZE(values);
        char overlay[32];
        sprintf(overlay, "avg %f", average);
        ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), 0, overlay, -1.0f, 1.0f, ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y));
        ImGui::End();
    }
}

void ModuleEditor::CreateCharacter(std::string name, int vit, int wis, int str, int agi, int def, int arc_def, int ctrl) {


    Character* newCharacter = new Character(name, vit, wis, str, agi, def, arc_def, ctrl);
    characters.push_back(newCharacter);
}

void ModuleEditor::ShowCharacters(Character* character) {

    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_Leaf;

    if (character == character_selected)
        flag |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(character->char_name.c_str(), flag)) {
   

        ImGui::TreePop();
    }
}

void ModuleEditor::StoreData() {

    data.AddUnsignedInt("Characters", characters.size());


    for (size_t i = 0; i < characters.size(); i++)
    {
        data.Object[to_string(i)];

        data.AddStringObj("Name", characters[i]->char_name, to_string(i));
        data.AddUnsignedIntObj("Vitality", characters[i]->vitality, to_string(i));
        data.AddUnsignedIntObj("Wisdom", characters[i]->wisdom, to_string(i));
        data.AddUnsignedIntObj("Strength", characters[i]->strength, to_string(i));
        data.AddUnsignedIntObj("Agility", characters[i]->agility, to_string(i));
        data.AddUnsignedIntObj("Defense", characters[i]->defense, to_string(i));
        data.AddUnsignedIntObj("ArcaneDef", characters[i]->arcane_defense, to_string(i));
        data.AddUnsignedIntObj("Control", characters[i]->control, to_string(i));
       
    }

    data.Save("storedValues.json");
}

//Takes json file from root and set characters in default values
void ModuleEditor::ResetCharacters() {

    data.Load("defaultValues.json");

    //Clean vector to add again later characters
    character_selected = nullptr;
    for (size_t i = 0; i < characters.size(); i++)
        RELEASE(characters[i]);

    characters.clear();
    
    
    int nCharacters = data.GetInt("Characters");
    
    for (size_t i = 0; i < nCharacters; i++)
    {
        string charname = data.GetStringObj("Name", to_string(i));
        uint Vitality = data.GetUnsignedIntObj("Vitality", to_string(i));
        uint Wisdom = data.GetUnsignedIntObj("Wisdom", to_string(i));
        uint Strength = data.GetUnsignedIntObj("Strength", to_string(i));
        uint Agility = data.GetUnsignedIntObj("Agility", to_string(i));
        uint Defense = data.GetUnsignedIntObj("Defense", to_string(i));
        uint ArcaneDef = data.GetUnsignedIntObj("ArcaneDef", to_string(i));
        uint Control = data.GetUnsignedIntObj("Control", to_string(i));
        
        Character* newChar = new Character(charname, Vitality, Wisdom, Strength, Agility, Defense, ArcaneDef, Control);
        characters.push_back(newChar);
    }
    
}