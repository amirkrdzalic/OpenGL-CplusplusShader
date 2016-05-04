#include <iostream>
#include "GL/glew.h"
#include <GL/gl.h>
#include "SDL.h"
#include <cassert>
#include "Debug.h"
#include "Window.h"

using namespace GAME;

Window::Window():windowPtr(nullptr),winRect(),glContext(nullptr), isInitialized(false), isFullScreen(false) {
/// Nothing much to do here. Init the variables, that's it 			
}

Window::~Window() {
	OnDestroy();
}

bool Window::OnCreate() {
	isInitialized = false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Debug::Log(EMessageType::FATAL_ERROR,  std::string(SDL_GetError()), __FILE__, __LINE__);
		return isInitialized;
	}

	/// These attributes must be set before the SDL window is created 

	/// You may need to change this to 16 or 32 depending on your graphics card
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);/// Enable Depth Cueing (the Z-buffer) 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);/// Turn on double buffering with a 24bit Z buffer. 

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	

	/// Create the SDL window
	windowPtr = SDL_CreateWindow("Component Framework Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
							winRect.w, winRect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (windowPtr == nullptr) {
		Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}
	
	/// Attach OpenGl to the new Window
	glContext = SDL_GL_CreateContext(windowPtr);
	if (glContext == nullptr) {
		Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	/// Fire up the GL Extension Wrangler
	glewExperimental = GL_TRUE; 
	GLenum glewError =  glewInit();
	if( glewError != GLEW_OK ){
		Debug::Log(EMessageType::FATAL_ERROR, (char*)glewGetErrorString( glewError ), __FILE__, __LINE__);
		assert(0);
	}

	/// This makes the buffer swap syncronize with the monitor's vertical refresh 
	if( SDL_GL_SetSwapInterval( 1 ) < 0 ){
		Debug::Log(EMessageType::WARNING, SDL_GetError(), __FILE__, __LINE__);
	}

	Debug::Log(EMessageType::INFO, (char*)glewGetString(GLEW_VERSION), __FILE__, __LINE__);
	GetInstalledOpenGLInfo();


	isInitialized = true;
	return true;
}


void Window::GetInstalledOpenGLInfo(){
	/// You can (and probably need) to get some info regarding versions and manufacturer
	const GLubyte *version = glGetString(GL_VERSION);
	/// You can also get the version as ints	
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);


	printf("GL Version - %s\n", version);
	printf("Graphics card vendor - %s\n", vendor);
	printf("Graphics card name - %s\n", renderer);
	printf("GLSL Version - %s\n", glslVersion);

}
void Window::OnDestroy() {
	SDL_DestroyWindow(windowPtr);
	SDL_Quit();
	SDL_GL_DeleteContext(glContext);
	windowPtr = nullptr;
	glContext = nullptr;
	isInitialized = false;
}

void Window::SetWindowSize(const int width_, const int height_) {
	winRect.w = width_;
	winRect.h = height_;
}


void Window::ToggleFullScreen() {
	isFullScreen = !isFullScreen;
	SDL_SetWindowFullscreen(windowPtr, (isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
}


int Window::GetWidth() const {
	return winRect.w;
}

int Window::GetHeight() const {
	return winRect.h;
}