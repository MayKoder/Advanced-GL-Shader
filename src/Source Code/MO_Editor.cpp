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

//TODO: Do i really need all those includes?
M_Editor::M_Editor(Application* app, bool start_enabled) : Module(app, start_enabled), displayWindow(false),
viewportCorSize(0.f)
{
	//Sould load the last used style on start?
	UpdateLoadedStylesVector(&styles);
}

M_Editor::~M_Editor()
{
}

bool M_Editor::Init()
{

	LOG(  "Init: ImGui");

	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	////io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	////io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	////io.ConfigViewportsNoDecoration = true;                    
	////io.ConfigViewportsNoAutoMerge = true;

	////ImGuiStyle* style = &ImGui::GetStyle();
	////style->WindowMenuButtonPosition = ImGuiDir_None;
	////style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.219f, 0.219f, 0.219f, 1.f);
	////style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.f, 1.f, 1.f, 1.f);

	////style->Colors[ImGuiCol_TitleBg] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);
	////style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);

	////style->Colors[ImGuiCol_Separator] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);
	////style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.152f, 0.152f, 0.152f, 1.f);

	////style->Colors[ImGuiCol_WindowBg] = ImVec4(0.211, 0.211, 0.211, 1.f);
	//////style->WindowBorderSize = 0.0f;

	////if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	////{
	////	style->WindowRounding = 0.0f;
	////	style->Colors[ImGuiCol_WindowBg].w = 1.0f;
	////}


	//ImGui::StyleColorsDark();
	////ImGui::StyleColorsClassic();

	//// Setup Platform/Renderer backends
	//bool test2 = ImGui_ImplSDL2_InitForOpenGL(App->moduleWindow->window, App->moduleRenderer3D->context);
	//bool test = ImGui_ImplOpenGL3_Init();

	//io.MouseDrawCursor = false;
	//io.IniFilename = "Settings/imgui.ini";
	//playingTint = ImVec4(1, 1, 1, 1);
	//io.IniFilename = NULL;

	return true;
}

bool M_Editor::Start()
{
	//W_TextEditor* txtEditor = dynamic_cast<W_TextEditor*>(GetEditorWindow(EditorWindow::TEXTEDITOR));
	//if(txtEditor != nullptr)
	//	txtEditor->SetTextFromFile("Library/Shaders/28971592.shdr");

	return true;
}

void M_Editor::Draw()
{
	////glClearColor(0.08f, 0.08f, 0.08f, 1.f);
	////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Start the Dear ImGui frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplSDL2_NewFrame(App->moduleWindow->window);
	//ImGui::NewFrame();

	//ImGuizmo::BeginFrame();

	////DrawMenuBar();

	////ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowBorderSize, 0);
	////DrawTopBar();
	////ImGui::PopStyleVar();

	////CreateDockSpace();


	//for (unsigned int i = 0; i < windows.size(); i++)
	//{
	//	if (windows[i]->active)
	//	{
	//		windows[i]->Draw();
	//	}
	//}

	//if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left)) 
	//{
	//	W_Hierarchy* hier = dynamic_cast<W_Hierarchy*>(GetEditorWindow(EditorWindow::HIERARCHY));
	//	hier->dropTarget = nullptr;
	//}

	//if (displayWindow)
	//{
	//	ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 1.f));
	//	ImGui::ShowDemoWindow();
	//	ImGui::PopStyleColor();
	//}

	////Rendering
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	return true;
}

//Draw menu bar
void M_Editor::DrawMenuBar()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
			if (ImGui::MenuItem("New"))
			{
				//Do something
				App->moduleScene->CleanScene();
			}
			if (ImGui::MenuItem("Save scene", "CTRL+S"))
			{
				std::string sceneDir = M_FileSystem::OpenSaveAsDialog();
				App->moduleFileSystem->ToLocalAssetsPath(sceneDir);
				if (!sceneDir.empty())
				{
					App->moduleScene->SaveScene(sceneDir.c_str());
				}

			}
			if (ImGui::MenuItem("Quit", "Esc"))
			{
				App->ExitApplication();
			}
			ImGui::PopStyleColor(1);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject"))
		{
			DrawCreateMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
			
			if (ImGui::MenuItem("ImGui Demo", nullptr, displayWindow))
			{
				displayWindow = !displayWindow;
			}
			if (ImGui::MenuItem("Documentation"))
			{
				ShellExecute(0, 0, "https://github.com/MayKoder/Diamond-Engine", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("Download latest"))
			{
				ShellExecute(0, 0, "https://github.com/MayKoder/Diamond-Engine/releases", 0, 0, SW_SHOW);
			}		
			if (ImGui::MenuItem("Report a bug"))
			{
				ShellExecute(0, 0, "https://github.com/MayKoder/Diamond-Engine/issues", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("MayKoder Github"))
			{
				ShellExecute(0, 0, "https://github.com/MayKoder", 0, 0, SW_SHOW);
			}

			ImGui::PopStyleColor(1);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	ImGui::PopStyleColor(1);
}

//void M_Editor::DrawTopBar()
//{
//	//Main menu bar 2
//	ImGuiViewport* viewport = ImGui::GetMainViewport();
//
//	ImGui::SetNextWindowPos(viewport->GetWorkPos());
//	ImGui::SetNextWindowViewport(viewport->ID);
//	ImGuiContext& g = *GImGui;
//
//	g.NextWindowData.MenuBarOffsetMinVal = ImVec2(g.Style.DisplaySafeAreaPadding.x, ImMax(g.Style.DisplaySafeAreaPadding.y - g.Style.FramePadding.y, 0.0f));
//
//	ImGui::SetNextWindowSize(ImVec2(g.IO.DisplaySize.x, (g.NextWindowData.MenuBarOffsetMinVal.y + g.FontBaseSize + g.Style.FramePadding.y) * 2.5f));
//
//	g.NextWindowData.MenuBarOffsetMinVal = ImVec2(0.f, 0.f);
//
//
//	if (ImGui::Begin("ButtonsNavBar", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDocking))
//	{
//
//		viewportCorSize = ImGui::GetWindowSize().y;
//
//		ImGuiStyle& style = ImGui::GetStyle();
//		float w = ImGui::CalcItemWidth();
//		float spacing = style.ItemInnerSpacing.x;
//		float button_sz = ImGui::GetFrameHeight();
//		ImGui::PushItemWidth((w - spacing * 2.0f - button_sz * 2.0f) * 0.13f);
//		if (ImGui::BeginCombo("##styleDropdown", "Style"))
//		{
//			//It's never a good idea to change a vector content
//			//while iterating over it
//			bool fileChanged = false;
//			for (int n = 0; n < styles.size(); n++)
//			{
//				if (ImGui::Button(styles[n].c_str()))
//					ChangeStyleTo(styles[n].c_str());
//
//				ImGui::SameLine();
//				std::string label("X" + std::to_string(n));
//				if (ImGui::Button(label.c_str()))
//				{
//					//Delete style
//					DeleteStyle(styles[n].c_str());
//					fileChanged = true;
//				}
//			}
//
//			ImGui::Separator();
//
//			//WARNING, TODO: Temporal fix, this is bad, fix it
//			ImGui::PushItemWidth(10 * MAX_STY_INPUT);
//			ImGui::InputText("##sName: ", styleInput, MAX_STY_INPUT);
//			ImGui::PopItemWidth();
//
//			if (ImGui::Button("Save current style") && styleInput[0] != '\0')
//			{
//				SaveStyle(styleInput);
//				styleInput[0] = '\0';
//				fileChanged = true;
//			}
//
//			if (fileChanged)
//				UpdateLoadedStylesVector(&styles);
//
//			ImGui::EndCombo();
//		}
//		ImGui::PopItemWidth();
//
//		ImGui::SameLine((ImGui::GetContentRegionMax().x / 2.f) - 100);
//
//
//		ImGui::SameLine(ImGui::GetContentRegionMax().x - (ImGui::GetButtonSize("Take Screenshoot").x + style.FramePadding.x));
//		if (ImGui::Button("Take Screenshoot")) 
//		{
//			TextureImporter::TakeScreenshot(App->moduleCamera->editorCamera.resolvedFBO.GetFrameBuffer());
//		}
//	}
//	ImGui::End();
//
//	//ImGui::PopStyleColor();
//}
//
//void M_Editor::CreateDockSpace()
//{
//	ImGuiViewport* viewport = ImGui::GetMainViewport();
//
//	ImVec2 dockPos(viewport->GetWorkPos());
//	dockPos.y += viewportCorSize;
//	ImGui::SetNextWindowPos(dockPos);
//
//	ImVec2 dockSize(viewport->GetWorkSize());
//	dockSize.y -= viewportCorSize;
//	ImGui::SetNextWindowSize(dockSize);
//
//	dockspace_id = ImGui::DockSpaceOverViewportCustom(viewport, ImGuiDockNodeFlags_PassthruCentralNode, dockPos, dockSize, nullptr);
//}


void M_Editor::DrawCreateMenu()
{
	
}

//Save a style to JSON
void M_Editor::SaveStyle(const char* styleName)
{
	//Maybe learning json alone wasn't a good idea
	LOG(  "Saving %s", styleName);

	JSON_Value* file = json_parse_file(STYLES_PATH);
	JSON_Object* root_object = json_value_get_object(file);

	//Init settings array
	JSON_Value* settingsArray = json_value_init_array();
	json_object_set_value(root_object, styleName, settingsArray);

	//Populate settings array
	JSON_Array* settings = json_value_get_array(settingsArray);
	ImGuiStyle& style = ImGui::GetStyle();

	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		JSON_Value *leaf_value = json_value_init_object();
		JSON_Object *leaf_object = json_value_get_object(leaf_value);

		json_object_set_number(leaf_object,"ID", i);
		json_object_set_number(leaf_object,"R", style.Colors[i].x);
		json_object_set_number(leaf_object,"G", style.Colors[i].y);
		json_object_set_number(leaf_object,"B", style.Colors[i].z);
		json_object_set_number(leaf_object,"A", style.Colors[i].w);

		json_array_append_value(settings, leaf_value);
	}

	//Save file 
	json_serialize_to_file_pretty(file, STYLES_PATH);

	//Free memory
	json_value_free(file);
}

//Change current style
void M_Editor::ChangeStyleTo(const char* styleName)
{
	JSON_Value* file = json_parse_file(STYLES_PATH);
	JSON_Object* root_object = json_value_get_object(file);

	JSON_Value* stArray = json_object_get_value(root_object, styleName);
	JSON_Array* settings = json_value_get_array(stArray);

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* mod = nullptr;
	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		JSON_Object* a = json_array_get_object(settings, i);
		mod = &style.Colors[i];

		mod->x = json_object_get_number(a, "R");
		mod->y = json_object_get_number(a, "G");
		mod->z = json_object_get_number(a, "B");
		mod->w = json_object_get_number(a, "A");

	}

	json_value_free(file);
	//json_value_free(stArray);

	LOG(  "Style %s loaded", styleName);
}

/*Delete a style*/
void M_Editor::DeleteStyle(const char* styleName)
{
	//Maybe learning json alone wasn't a good idea
	LOG(  "Deleting style %s", styleName);

	//Init node
	JSON_Value* file = json_parse_file(STYLES_PATH);
	JSON_Object* root_object = json_value_get_object(file);

	json_object_remove(root_object, styleName);

	//json_object_set_value(root_object, styleName, NULL);

	//Save file 
	json_serialize_to_file_pretty(file, STYLES_PATH);

	//Free memory
	json_value_free(file);
}

/*Update saved styles*/
void M_Editor::UpdateLoadedStylesVector(std::vector<std::string>* _styles)
{
	LOG(  "Loading saved styles at default file");

	styles.clear();
	JSON_Value* file = json_parse_file(STYLES_PATH);

	if (file != NULL)
	{
		JSON_Object* root_object = json_value_get_object(file);
		size_t size = json_object_get_count(root_object);

		for (size_t i = 0; i < size; ++i)
		{
			_styles->push_back(json_object_get_name(root_object, i));
		}
	}
	else
	{
		LOG( "Styles file could not be loaded, loading default style");
	}
	json_value_free(file);
}
#endif