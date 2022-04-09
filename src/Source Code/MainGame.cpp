#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>

MainGame::MainGame() : counter(0.0f), texture(nullptr)
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display

	//Audio* audioDevice();
}

MainGame::~MainGame()
{
	delete texture;
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	geoMesh.loadModel("assets/monkey3.obj");
	geoShader.init("assets/Shaders/geoShder.glsl");

	reflectionMesh.loadModel("assets/sphere.obj");
	reflectionShader.init("assets/Shaders/reflectionShader.glsl");

	dissolveMesh.loadModel("assets/sphere.obj");
	dissolveShader.init("assets/Shaders/dissolve.glsl");

	myCamera.initCamera(glm::vec3(0, 0, -5), 1.0471975512f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 0.0f;

	vector<std::string> faces
	{
		"assets/Skybox/right.jpg",
		"assets/Skybox/left.jpg",
		"assets/Skybox/top.jpg",
		"assets/Skybox/bottom.jpg",
		"assets/Skybox/front.jpg",
		"assets/Skybox/back.jpg"
	};

	skybox.init(faces);
	texture = new Texture("assets/bricks.jpg"); //load texture
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

//void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
//{
//	
//	ALint state; 
//	alGetSourcei(Source, AL_SOURCE_STATE, &state);
//	/*
//	Possible values of state
//	AL_INITIAL
//	AL_STOPPED
//	AL_PLAYING
//	AL_PAUSED
//	*/
//	if (AL_PLAYING != state)
//	{
//		audioDevice.playSound(Source, pos);
//	}
//}

void MainGame::linkGeometryShader()
{
	geoShader.setFloat("randColourX", ((float)rand()/(RAND_MAX)));
	geoShader.setFloat("randColourY", ((float)rand()/(RAND_MAX)));
	geoShader.setFloat("randColourZ", ((float)rand()/(RAND_MAX)));
	geoShader.setFloat("time", counter);
}

void MainGame::linkDissolveShader()
{
	dissolveShader.setMat4("model", dissolveMesh.transform.GetModel());
	dissolveShader.setMat4("view", myCamera.getView());
	dissolveShader.setMat4("projection", myCamera.getProjection());
	dissolveShader.setFloat("time", counter);
	dissolveShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, -0.5f));


	//dissolveShader.setVec3("inverseView", -myCamera.getForward());
	//dissolveShader.setVec3("cameraPos", myCamera.getPos());
	//dissolveShader.setVec2("u_resolution", glm::vec2(_gameDisplay.getWidth(), _gameDisplay.getHeight()));
}

void MainGame::linkReflection()
{
	reflectionShader.setMat4("model", reflectionMesh.transform.GetModel());
	reflectionShader.setMat4("view", myCamera.getView());
	reflectionShader.setMat4("projection", myCamera.getProjection());
	reflectionShader.setVec3("cameraPos", myCamera.getPos());
}

void MainGame::drawGame()
{
	//myCamera.RotateY(0.01f);
	_gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour
	

	geoShader.Bind();
	texture->Bind(0);
	geoMesh.transform.SetPos(glm::vec3(2.0, 0.0, 0.0));
	geoMesh.transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	geoMesh.transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	geoShader.Update(geoMesh.transform, myCamera);
	linkGeometryShader();
	geoMesh.draw();


	reflectionShader.Bind();
	reflectionMesh.transform.SetPos(glm::vec3(-2.0, 0.0, 0.0));
	reflectionMesh.transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	linkReflection();
	reflectionMesh.draw();

	skybox.draw(&myCamera);

	glDisable(GL_CULL_FACE);
	dissolveShader.Bind();
	texture->Bind(0);
	dissolveMesh.transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	//dissolveMesh.transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	dissolveMesh.transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	linkDissolveShader();
	dissolveMesh.draw();
	//glEnable(GL_CULL_FACE);

	counter += 0.008f;
				
	//glEnableClientState(GL_COLOR_ARRAY); 
	//glEnd();

	_gameDisplay.swapBuffer();
} 