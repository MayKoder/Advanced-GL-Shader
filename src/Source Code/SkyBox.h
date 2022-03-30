#pragma once
#include <vector>
#include <iostream>
#include"OpenGL.h"
#include"Camera.h"
#include"Shader.h"
#include"stb_image.h"

class Skybox
{
public:
	void init(std::vector<std::string> faces);
	void draw(Camera* camera);

	unsigned int textureID;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

private:
	Shader shader;

};

