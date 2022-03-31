#pragma once
#include "SDL/include/SDL.h"
#include "Glew/include/glew.h"
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include"SkyBox.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	void linkReflection();

	void linkGeometryShader();

	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	//void playAudio(unsigned int Source, glm::vec3 pos);

	Display _gameDisplay;
	GameState _gameState;

	Texture* texture;

	Mesh geoMesh;
	Mesh reflectionMesh;

	Camera myCamera;

	Shader geoShader;
	Shader reflectionShader;

	Skybox skybox;

	float counter;
	//unsigned int whistle;
	//unsigned int backGroundMusic;
};

