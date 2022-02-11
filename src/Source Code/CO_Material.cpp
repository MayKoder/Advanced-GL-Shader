#include "CO_Material.h"
#include "ImGui/imgui.h"
#include "Application.h"
#include"MO_Renderer3D.h"
#include"MO_Scene.h"

#include"RE_Texture.h"
#include"RE_Shader.h"
#include"MO_ResourceManager.h"

#include"DEJsonSupport.h"
#include"IM_TextureImporter.h"
#include"RE_Material.h"

#include "IM_FileSystem.h"
#include "IM_MaterialImporter.h"

C_Material::C_Material(GameObject* _gm) : Component(_gm), viewWithCheckers(false), matTexture(nullptr),
material(nullptr)
{
	name = "Material";
	material = (EngineExternal->moduleScene->defaultMaterial != nullptr) ? dynamic_cast<ResourceMaterial*>(EngineExternal->moduleResources->RequestResource(EngineExternal->moduleScene->defaultMaterial->GetUID().c_str())) : NULL;
}

C_Material::~C_Material()
{
	if(matTexture != nullptr)
		EngineExternal->moduleResources->UnloadResource(matTexture->GetUID());

	if (material != nullptr)
		EngineExternal->moduleResources->UnloadResource(material->GetUID());
}

#ifndef STANDALONE
bool C_Material::OnEditor()
{
	if (Component::OnEditor() == true)
	{
		ImGui::Separator();

		ImGui::Text("Drop here to change material");
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_MATERIAL"))
			{
				std::string* assetsPath = (std::string*)payload->Data;

				if(material != nullptr)
					EngineExternal->moduleResources->UnloadResource(material->GetUID());

				material = dynamic_cast<ResourceMaterial*>(EngineExternal->moduleResources->RequestFromAssets(*assetsPath));
			}
			ImGui::EndDragDropTarget();
		}

		if (material) 
		{
			ImGui::Dummy(ImVec2(0, 15));
			ImGui::Text("Using shader: %s", material->shader->GetAssetPath());
		}

		return true;
	}
	return false;
}
#endif // !STANDALONE

int C_Material::GetTextureID()
{
	return (viewWithCheckers == false && (matTexture && matTexture->textureID != 0)) ? matTexture->textureID : EngineExternal->moduleRenderer3D->checkersTexture;
	//return matTexture->textureID;
}

void C_Material::SaveData(JSON_Object* nObj)
{
	Component::SaveData(nObj);

	DEJson::WriteBool(nObj, "IsEmpty", (matTexture == nullptr) ? true : false);
	if (matTexture != nullptr) 
	{
		DEJson::WriteString(nObj, "AssetPath", matTexture->GetAssetPath());
		DEJson::WriteString(nObj, "UID", matTexture->GetUID().c_str());
	}
	if (material != nullptr) 
	{
		DEJson::WriteString(nObj, "MaterialAssetPath", material->GetAssetPath());
		DEJson::WriteString(nObj, "MaterialUID", material->GetUID().c_str());
	}
	//TODO: Call texture importer and load data
}

void C_Material::LoadData(DEConfig& nObj)
{
	Component::LoadData(nObj);

	//if (nObj.ReadBool("IsEmpty") == true)
	//	return;


	int w, h;
	w = h = 0;
	std::string texPath = nObj.ReadString("AssetPath");
	std::string texName = nObj.ReadString("LibraryPath");

	if (texName != "") 
		matTexture = dynamic_cast<ResourceTexture*>(EngineExternal->moduleResources->RequestResource(nObj.ReadString("UID")));


	if (material != nullptr) 
	{
		EngineExternal->moduleResources->UnloadResource(material->GetUID());
		material = nullptr;
	}

	if(nObj.ReadInt("MaterialUID") != 0)
		material = dynamic_cast<ResourceMaterial*>(EngineExternal->moduleResources->RequestResource(nObj.ReadString("MaterialUID")));
}