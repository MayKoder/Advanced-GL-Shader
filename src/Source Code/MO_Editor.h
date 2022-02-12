#ifndef STANDALONE
#pragma once

#include "Module.h"
#include "Globals.h"
#include "Window.h"

#define STYLES_PATH "Settings/styles.json"
#define MAX_STY_INPUT 15

typedef unsigned int ImGuiID;
enum class LogType;
class GameObject;
class ResourceTexture;
struct AssetDir;

class M_Editor : public Module
{

public:
	M_Editor(Application* app, bool start_enabled = true);
	virtual ~M_Editor();

	bool Init() override;
	bool Start() override;

	void Draw();

	bool CleanUp() override;

	Window settingsWindow;

};

#endif