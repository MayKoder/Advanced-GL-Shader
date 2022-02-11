#pragma once

#include "Module.h"
#include<map>

#include"MO_FileSystem.h"
#include"DEResource.h"

class M_ResourceManager : public Module
{

public:
	M_ResourceManager(Application* app, bool start_enabled = true);
	virtual ~M_ResourceManager();

	bool Init() override;

	bool CleanUp() override;

#ifndef STANDALONE
	void OnGUI() override;
#endif // !STANDALONE

	void UnloadResource(std::string& uid);
	Resource* RequestFromAssets(std::string& assets_path);

	Resource* RequestResource(const char* uid);
	Resource* CreateNewResource(std::string& assetsFile, Resource::Type type);
	Resource* LoadFromLibrary(std::string& libraryFile, Resource::Type type);
	Resource* GetResourceFromUID(std::string& uid);
	
	Resource::Type GetTypeFromAssetExtension(const char* assetFile) const;

private:
	void LoadResource(std::string& uid);
	void ReleaseResource(std::string& uid);

	bool IsResourceLoaded(std::string& uid);


private:
	std::map<std::string, Resource*> resources;
};