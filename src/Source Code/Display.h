#pragma once

#include"OpenGL.h"


#include <iostream>
#include <string>
using namespace std;

#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )


class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float screenWidth;
	float screenHeight;
};

