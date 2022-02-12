#pragma once
#include "Component.h"

#include"MathGeoLib/include/Geometry/AABB.h"
#include"MathGeoLib/include/Geometry/OBB.h"

#include"GL_Object.h"

class C_MeshRenderer : public Component
{
public:
	C_MeshRenderer(GameObject* _gm);
	virtual ~C_MeshRenderer();

	void Update() override;

	void RenderMesh(bool rTex = false, ResourceShader* shader = nullptr);

	void OGL_GPU_Render();

#ifndef STANDALONE
	bool OnEditor() override;
#endif // !STANDALONE

	static inline Type GetType() { return Type::MeshRenderer; }; //This will allow us to get the type from a template

	OBB globalOBB;
	AABB globalAABB;
	bool faceNormals, vertexNormals, showAABB, showOBB;

	std::vector<float> vertices;
	std::vector<int> indices;

	GL_Object _mesh = GL_Object(GL_Object::RENDER_TYPE::RE_INDICES);
private:
	float3 alternColor;
};