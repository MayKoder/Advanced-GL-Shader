#pragma once
#include"OpenGL.h"
#include"Camera.h"
#include"Shader.h"
#include"stb_image.h"
#include"Mesh.h"

class Dissolve : public Mesh
{
public:
	void init();
	void draw(Camera* camera);

private:
	Shader shader;

};

