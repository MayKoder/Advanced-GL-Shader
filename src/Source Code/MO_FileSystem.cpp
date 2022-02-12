#include "MO_FileSystem.h"
#include "Globals.h"

#include "IM_FileSystem.h"

#include "Application.h"

#include "MO_Editor.h"
#include "MO_ResourceManager.h"
#include"MO_Scene.h"

#include "PhysFS/include/physfs.h"
#include"DEJsonSupport.h"

#include "DevIL\include\ilu.h"
#include "DevIL\include\ilut.h"
#include"RE_Shader.h"
#include"RE_Material.h"


M_FileSystem::M_FileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

M_FileSystem::~M_FileSystem()
{
}

bool M_FileSystem::Init()
{
	//Devil init
	LOG(  "DevIL Init");
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	FileSystem::FSInit();

	return true;
}

bool M_FileSystem::Start()
{

	//TODO: Move to resource manager
	App->moduleScene->defaultMaterial = (ResourceMaterial*)App->moduleResources->RequestFromAssets(std::string("assets/Materials/default.mat"));
	App->moduleRenderer3D->skybox.shaderRes = dynamic_cast<ResourceShader*>(App->moduleResources->RequestResource("assets/Shaders/cubeMap.glsl"));
	App->moduleRenderer3D->defaultShader = dynamic_cast<ResourceShader*>(App->moduleResources->RequestResource("assets/Shaders/default.glsl"));

	return true;
}

bool M_FileSystem::CleanUp()
{

	FileSystem::FSDeInit();

	return true;
}

uint64 M_FileSystem::GetLastModTime(const char* filename)
{
	PHYSFS_Stat stat;
	PHYSFS_stat(filename, &stat);
	return stat.modtime;
}

std::string M_FileSystem::OpenFileSelectDialog()
{
	char filename[MAX_PATH];
	filename[0] = '\0';

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = ".des\0*.des*\0"; //Text Files\0*.txt\0 //I DONT KNOW HOW TO FILTER .META FILES AAAAAAAH
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	
	if (GetOpenFileNameA(&ofn))
		return std::string(filename);

	return std::string("\0");
}

std::string M_FileSystem::OpenSaveAsDialog()
{
	char filename[MAX_PATH];
	filename[0] = '\0';

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Diamond Engine Scene (.des)\0"; //Text Files\0*.txt\0
	ofn.lpstrDefExt = "des";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Save file as";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_NOCHANGEDIR;

	if (GetSaveFileNameA(&ofn))
		return std::string(filename);

	return std::string("\0");
}

void M_FileSystem::ToLocalAssetsPath(std::string& inp)
{
	std::string localPath = FileSystem::NormalizePath(inp.c_str());
	inp.clear();

	size_t pos = 0;
	pos = localPath.find(ASSETS_PATH);
	if (pos != std::string::npos)
	{
		localPath = localPath.substr(pos);
		if (localPath.c_str() != "") {
			inp = localPath;
			return;
		}
	}

	inp = localPath;
	localPath.clear();
	return;
}

int M_FileSystem::DeleteAssetFile(const char* fileDir)
{
	if (fileDir == nullptr)
		return 0;

	return PHYSFS_delete(fileDir);
}