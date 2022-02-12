#pragma once
#include "Application.h"
#include "Module.h"

#include <queue>

#include"MathGeoLib/include/Math/float3.h"
#include"MathGeoLib/include/Geometry/LineSegment.h"

#include"DE_Cubemap.h"

#include<map>

class C_MeshRenderer;
class ResourceTexture;
class C_Camera;
class C_DirectionalLight;

typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */

#define MAX_LIGHTS 1

#define SQUARE_TEXTURE_W 256
#define SQUARE_TEXTURE_H 256

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	virtual ~ModuleRenderer3D();

	bool Init() override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	void OnResize(int width, int height) override;

#ifndef STANDALONE
	void OnGUI() override;

	void DrawDebugLines();
	void AddDebugLines(float3& a, float3& b, float3& color);
#endif // !STANDALONE


	static void DrawBox(float3* points, float3 color = float3::one);

	C_Camera* GetGameRenderTarget()const;
	void SetGameRenderTarget(C_Camera* cam);

	void ClearAllRenderData();
private:

	void DirectionalShadowPass();

	void RenderWithOrdering(bool rTex = false);
	void DebugLine(LineSegment& line);
	void GetCAPS(std::string& caps);
	std::string str_CAPS;

public:
	bool vsync, wireframe, cull, lightng, color_material, texture_2d;

	GLuint checkersTexture;
	GLubyte checkerImage[SQUARE_TEXTURE_W][SQUARE_TEXTURE_H][4];

	std::vector<C_MeshRenderer*> renderQueue;
	std::multimap<float, C_MeshRenderer*> renderQueueMap;

	SDL_GLContext context;

	C_Camera* activeRenderCamera = nullptr; //TODO: This is temporal
	DE_Cubemap skybox;
	C_DirectionalLight* directLight;

	ResourceShader* defaultShader;

private:
	//std::vector<LineRender> lines;
	LineSegment pickingDebug;


	//MMP_Plane plane;
};