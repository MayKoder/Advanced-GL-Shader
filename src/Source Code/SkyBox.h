#pragma once
#include <vector>
#include <iostream>
#include"OpenGL.h"
#include"Camera.h"
#include"Shader.h"
#include"stb_image.h"
#include"Mesh.h"

class Skybox : public Mesh
{

public:
	Skybox();
	~Skybox();

	void init(std::vector<std::string> faces);
	void draw(Camera* camera);

	unsigned int textureID;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

private:
	Shader shader;

};

