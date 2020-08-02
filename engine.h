#pragma once

#include "entitymanager.h"
#include "system_manager.h"
#include "inputlogger.h"
#include <time.h> 
#include <SDL.h>
#include "SDL.h"
#include "glew.h"
#include "SceneManager.h"
#include "scene.h"
#include <memory>
#include "MainGame.h"
#include "mainMenu.h"
#include "TextManager.h"

//base class for our engine setup

namespace ACC
{

	class engine
	{
	private:

		SDL_Renderer *renderer;
		SDL_Window *window;
		SDL_GLContext glcontext;
		unsigned int lastTime;
		unsigned int current;
		float deltaTs;
		std::shared_ptr<SceneManager> sceneMan;
		std::shared_ptr<entitymanager> myentman;

		int frametimelast;
		int framespersecond;

	public:

		bool OpenglSdlSetup(int width, int height);
		void init();
		void update();
		void cleanup();
		bool go;

	};

}