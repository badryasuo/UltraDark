#ifndef _DARK_DISPLAY_H
#define _DARK_DISPLAY_H
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
namespace Display
{
	int IsClosed = 0;
	float SCR_WIDTH;
	float SCR_HEIGHT;
	float SCR_AspectRatio;
	// Declare static variables
	SDL_Window * Window;
	SDL_GLContext GLContext;
	// Functions
	void Init(int width, int height, const char* title)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (Window == NULL)
			std::cerr << "Failed to create OpenGL window\n" << SDL_GetError() << "\n";
		else
		{
			SCR_WIDTH = (float)width;
			SCR_HEIGHT = (float)height;
			SCR_AspectRatio = SCR_WIDTH / SCR_HEIGHT;
		}
		GLContext = SDL_GL_CreateContext(Window);
		SDL_GL_MakeCurrent(Window, GLContext);

		if (!gladLoadGL())
			std::cerr << "Failed to load OpenGL\n" << SDL_GetError() << "\n";
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}
	void Update()
	{
		int w, h;
		SDL_GetWindowSize(Window, &w, &h);
		glViewport(0, 0, w, h);
		SDL_GL_SwapWindow(Window);
		SDL_Event e;
		// returns 1 if there's a binding event
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: 			IsClosed = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:	IsClosed = true;
					break;
				case SDLK_q:		std::cout << "Q\n";
					break;
				}
				break;
			}
		}
	}
	void Bye()
	{
		SDL_GL_DeleteContext(GLContext);
		SDL_DestroyWindow(Window);
		SDL_Quit();
	}

};
// Define static varaibles

#endif