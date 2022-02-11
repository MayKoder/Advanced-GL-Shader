#pragma once

#include "Module.h"
#include<vector>
#include<string>
#include"Globals.h"

class M_FileSystem : public Module
{

public:
	M_FileSystem(Application* app, bool start_enabled = true);
	virtual ~M_FileSystem();

	bool Init() override;
	bool Start() override;

	bool CleanUp() override;

public:
	uint64 GetLastModTime(const char* filename);

	static std::string OpenSaveAsDialog();
	static std::string OpenFileSelectDialog();
	static void ToLocalAssetsPath(std::string& inp);

	//Permanent delete, use with caution
	int DeleteAssetFile(const char* fileDir);
};