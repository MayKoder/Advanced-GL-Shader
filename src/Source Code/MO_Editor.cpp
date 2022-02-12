#ifndef STANDALONE

#include "Application.h"

#include "MMGui.h"
#include "parson/parson.h"

#include"DETime.h"

#include "MO_Window.h"
#include "MO_Renderer3D.h"
#include "MO_Editor.h"
#include "MO_Scene.h"
#include "MO_ResourceManager.h"

#include"GameObject.h"
#include"IM_TextureImporter.h"
#include"MO_Camera3D.h"

#include"ImGui/imgui.h"
#include"ImGui/backends/imgui_impl_opengl3.h"
#include"ImGui/backends/imgui_impl_sdl.h"

//TODO: Do i really need all those includes?
M_Editor::M_Editor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

M_Editor::~M_Editor()
{
}

bool M_Editor::Init()
{

	LOG(  "Init: ImGui");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	//io.ConfigViewportsNoDecoration = true;                    
	//io.ConfigViewportsNoAutoMerge = true;

	//ImGuiStyle* style = &ImGui::GetStyle();
	//style->WindowMenuButtonPosition = ImGuiDir_None;
	//style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.219f, 0.219f, 0.219f, 1.f);
	//style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.f, 1.f, 1.f, 1.f);

	//style->Colors[ImGuiCol_TitleBg] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);
	//style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);

	//style->Colors[ImGuiCol_Separator] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);
	//style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);

	//style->Colors[ImGuiCol_WindowBg] = ImVec4(0.211, 0.211, 0.211, 1.f);
	////style->WindowBorderSize = 0.0f;

	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	style->WindowRounding = 0.0f;
	//	style->Colors[ImGuiCol_WindowBg].w = 1.0f;
	//}


	ImGui::StyleColorsDark();

	bool test2 = ImGui_ImplSDL2_InitForOpenGL(App->moduleWindow->window, App->moduleRenderer3D->context);
	bool test = ImGui_ImplOpenGL3_Init();

	io.MouseDrawCursor = false;
	io.IniFilename = "Settings/imgui.ini";
	io.IniFilename = NULL;

	return true;
}

bool M_Editor::Start()
{


	return true;
}

void M_Editor::Draw()
{
	//glClearColor(0.08f, 0.08f, 0.08f, 1.f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->moduleWindow->window);
	ImGui::NewFrame();

	//DrawMenuBar();

	//ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowBorderSize, 0);
	//DrawTopBar();
	//ImGui::PopStyleVar();

	//CreateDockSpace();

	settingsWindow.Draw();

	//Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
	//	SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
	//	ImGui::UpdatePlatformWindows();
	//	ImGui::RenderPlatformWindowsDefault();
	//	SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	//}

}


bool M_Editor::CleanUp()
{
	LOG(  "Editor CleanUp");


	LOG(  "ImGui Shutdown");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

#endif