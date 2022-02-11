#include "CO_MeshRenderer.h"

#include "Application.h"
#include "MO_Renderer3D.h"
#include"MO_ResourceManager.h"
#include"RE_Material.h"
#include"RE_Shader.h"
#include "IM_FileSystem.h"

#include "GameObject.h"
#include "CO_Material.h"
#include "CO_Transform.h"
#include"CO_Camera.h"

#include "ImGui/imgui.h"
#include"MO_Scene.h"

#include"DEJsonSupport.h"

#include"MathGeoLib/include/Geometry/Frustum.h"
#include"MathGeoLib/include/Geometry/Plane.h"

C_MeshRenderer::C_MeshRenderer(GameObject* _gm) : Component(_gm), _mesh(nullptr),
faceNormals(false), vertexNormals(false), showAABB(false), showOBB(false)
{
	name = "Mesh Renderer";
	alternColor = float3::one;
}

C_MeshRenderer::~C_MeshRenderer()
{
	indices.clear();
	vertices.clear();

	if (_mesh != nullptr) 
	{
		//EngineExternal->moduleResources->UnloadResource(_mesh->GetUID());
		delete _mesh;
		_mesh = nullptr;
	}
}

void C_MeshRenderer::Update()
{
	//if (_mesh == nullptr)
	//	return;

	EngineExternal->moduleRenderer3D->renderQueue.push_back(this);

#ifndef STANDALONE
	if (showAABB ==true) 
	{

		float3 points[8];
		globalAABB.GetCornerPoints(points);
		ModuleRenderer3D::DrawBox(points, float3(0.2f, 1.f, 0.101f));
	}

	if (showOBB == true) 
	{

		float3 points[8];
		globalOBB.GetCornerPoints(points);
		ModuleRenderer3D::DrawBox(points);
	}
#endif // !STANDALONE

}

void C_MeshRenderer::RenderMesh(bool rTex, ResourceShader* shader)
{

	shader->Bind();
	EngineExternal->moduleRenderer3D->activeRenderCamera->PushCameraShaderVars(shader->shaderProgramID);

	GLint modelLoc = glGetUniformLocation(shader->shaderProgramID, "position");
	glUniform3f(modelLoc, this->gameObject->transform->position.x, this->gameObject->transform->position.y, this->gameObject->transform->position.z);

	modelLoc = glGetUniformLocation(shader->shaderProgramID, "color");
	glUniform4f(modelLoc, 1, 1, 1, 1);

	modelLoc = glGetUniformLocation(shader->shaderProgramID, "normalMatrix");
	if (modelLoc != -1) {
		glUniformMatrix3fv(modelLoc, 1, GL_FALSE, this->gameObject->transform->NormalMatrixOpenGL().ptr());
	}

	this->OGL_GPU_Render();

	shader->Unbind();
	//if (_mesh == nullptr)
	//	return;


	//C_Transform* transform = gameObject->transform;

	////TODO IMPORTANT: Optimize this, save this pointer or something
	//C_Material* material = dynamic_cast<C_Material*>(gameObject->GetComponent(Component::Type::Material));
	//GLuint id = 0;

	//if (material != nullptr && material->IsActive())
	//	id = material->GetTextureID();

	//_mesh->RenderMesh(id, alternColor, rTex, (material && material->material != nullptr) ? material->material : EngineExternal->moduleScene->defaultMaterial, transform);

	//if (vertexNormals || faceNormals)
	//	_mesh->RenderMeshDebug(&vertexNormals, &faceNormals, transform->GetGlobalTransposed());

}

void C_MeshRenderer::OGL_GPU_Render()
{
	_mesh->RenderAsIndices(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT);
}

#ifndef STANDALONE
bool C_MeshRenderer::OnEditor()
{
	if (Component::OnEditor() == true)
	{
		ImGui::Separator();

		if (_mesh != nullptr) 
		{
			//ImGui::Image((ImTextureID)_mesh->textureID, ImVec2(128, 128));
			ImGui::Text("Vertices: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%i", this->vertices.size() / 3);
			ImGui::Text("Indices: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%i", this->indices.size());
		}

		ImGui::Checkbox("Vertex Normals", &vertexNormals);
		ImGui::SameLine();
		ImGui::Checkbox("Face Normals", &faceNormals);

		ImGui::Checkbox("Show AABB", &showAABB);
		ImGui::SameLine();
		ImGui::Checkbox("Show OBB", &showOBB);

		ImGui::ColorPicker3("No texture color: ", &alternColor.x);

		return true;
	}
	return false;
}
#endif // !STANDALONE
