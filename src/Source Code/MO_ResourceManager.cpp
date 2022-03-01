#include "MO_ResourceManager.h"
#include"Application.h"
#include"ImGui/imgui.h"

//Importers
#include"IM_FileSystem.h"
#include"IM_TextureImporter.h"
#include"IM_ShaderImporter.h"

#include"MO_Scene.h"
#include"Globals.h"

#include"RE_Texture.h"
#include"RE_Shader.h"

#include"DEJsonSupport.h"
#include"MO_Window.h"

M_ResourceManager::M_ResourceManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

M_ResourceManager::~M_ResourceManager()
{
}

bool M_ResourceManager::Init()
{
	return true;
}

bool M_ResourceManager::CleanUp()
{
	return true;
}

#ifndef STANDALONE
void M_ResourceManager::OnGUI()
{
	//TODO: Move this to a new editor window
	if (ImGui::CollapsingHeader("Resource Display", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%i resources loaded", resources.size());
		for (auto it = resources.begin(); it != resources.end(); ++it)
		{
			ImGui::Text("%i: %s", (*it).second->GetReferenceCount(), (*it).second->GetUID().c_str());
		}
	}
}
#endif // !STANDALONE

//Returns a resource* if the resource is loaded or creates a new resource from the library file
Resource* M_ResourceManager::RequestResource(const char* uid)
{
	//Find if the resource is already loaded
	if (uid == nullptr)
		return nullptr;

	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it != resources.end())
	{
		it->second->IncreaseReferenceCount();
		return it->second;
	}

	//Find the library file (if exists) and load the custom file format
	if (uid != nullptr) 
	{
		Resource* ret = nullptr;

		static_assert(static_cast<int>(Resource::Type::UNKNOWN) == 2, "Update all switches with new type");

		//Save check
		if (FileSystem::Exists(uid))
		{
			//uid = 0; //This should be the uid from library
			switch (GetTypeFromAssetExtension(uid))
			{
				case Resource::Type::TEXTURE: ret = (Resource*) new ResourceTexture(std::string(uid)); break;
				case Resource::Type::SHADER: ret = dynamic_cast<Resource*>(new ResourceShader(std::string(uid))); break;
			}

			if (ret != nullptr)
			{
				resources[uid] = ret;
				ret->SetAssetsPath(uid);
				ret->IncreaseReferenceCount();

				ret->LoadToMemory();
			}
			LOG(  "Requested resource loaded as new"); //UNCOMMENT
		}
		else
			LOG( "Requested resource does not exist");

		return ret;
	}

	return nullptr;
	//return TryToLoadResource();
}

void M_ResourceManager::ReleaseResource(std::string& uid)
{
	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it == resources.end())
		return;
	
	Resource* res = (*it).second;
	(*it).second->UnloadFromMemory();
	resources.erase((*it).second->GetUID());
	delete res;
}

Resource* M_ResourceManager::RequestFromAssets(std::string& assets_path)
{
	Resource* ret = nullptr;
	if (FileSystem::Exists(assets_path.c_str()) == true)
	{
		ret = RequestResource(assets_path.c_str()); 
		if(ret != nullptr)
			ret->SetAssetsPath(assets_path.c_str());
	}
	else
		LOG( "ASSET NOT IN FOLDER");

	return ret;
}

Resource* M_ResourceManager::CreateNewResource(std::string& assetsFile, Resource::Type type)
{
	Resource* ret = nullptr;

	static_assert(static_cast<int>(Resource::Type::UNKNOWN) == 2, "Update all switches with new type");
	switch (type) 
	{
		case Resource::Type::TEXTURE: ret = (Resource*) new ResourceTexture(assetsFile); break;
		case Resource::Type::SHADER: ret = (Resource*) new ResourceShader(assetsFile); break;
	}

	if (ret != nullptr)
	{
		resources[assetsFile] = ret;
		ret->SetAssetsPath(assetsFile.c_str());
		ret->IncreaseReferenceCount();
	}

	return ret;
}

Resource* M_ResourceManager::LoadFromLibrary(std::string& libraryFile, Resource::Type type)
{
	Resource* ret = nullptr;

	static_assert(static_cast<int>(Resource::Type::UNKNOWN) == 2, "Update all switches with new type");

	switch (type)
	{
		case Resource::Type::TEXTURE: ret = (Resource*) new ResourceTexture(libraryFile); break;
		case Resource::Type::SHADER: ret = (Resource*) new ResourceShader(libraryFile); break;
		//case Resource::Type::SCENE : ret = (Resource*) new ResourceScene(uid); break;
	}

	if (ret != nullptr)
	{
		resources[libraryFile] = ret;
		ret->SetAssetsPath("");
		ret->IncreaseReferenceCount();
	}

	return ret;
}

Resource* M_ResourceManager::GetResourceFromUID(std::string& uid)
{
	//Find if the resource is already loaded
	if (uid.empty())
		return nullptr;

	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it != resources.end())
	{
		return it->second;
	}

	return nullptr;
}

void M_ResourceManager::LoadResource(std::string& uid)
{
	Resource* res = nullptr;

	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it == resources.end())
		return;

	res = it->second;
	res->IncreaseReferenceCount();

	//Load to memory [Buffers etcetc]
	res->LoadToMemory();

}

void M_ResourceManager::UnloadResource(std::string& uid)
{
	Resource* res = nullptr;
	
	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it == resources.end())
		return;
	
	res = it->second;
	res->DecreaseReferenceCount();

	if (res->GetReferenceCount() <= 0) 
		ReleaseResource(res->GetUID());

}

bool M_ResourceManager::IsResourceLoaded(std::string& uid)
{
	std::map<std::string, Resource*>::iterator it = resources.find(uid);
	if (it != resources.end())
		return true;

	return false;
}

Resource::Type M_ResourceManager::GetTypeFromAssetExtension(const char* assetFile) const
{
	std::string ext(assetFile);
	ext = ext.substr(ext.find_last_of('.') + 1);

	for (size_t i = 0; i < ext.length(); i++)
	{
		ext[i] = std::tolower(ext[i]);
	}

	if (ext == "dds")
		return Resource::Type::TEXTURE;
	if (ext == "glsl")
		return Resource::Type::SHADER;


	return Resource::Type::UNKNOWN;
}
