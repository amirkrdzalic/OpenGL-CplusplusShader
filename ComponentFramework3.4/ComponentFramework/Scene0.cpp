#include "GL/glew.h"
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "Model1.h"

using namespace GAME;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef), cube(nullptr) { 
	projectionMatrix.loadIdentity();
	modelViewMatrix.loadIdentity();

	//sphereprojectionMatrix.loadIdentity();
	spheremodelViewMatrix.loadIdentity();

	normalMatrix.loadIdentity();
	//spherenormalMatrix.loadIdentity();
	//load all other created double proj and models

	//pos = Vec3(0.0f, 1.0f, 5.0f); 
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST); 
}

Scene0::~Scene0(){ 
	OnDestroy();
}

bool Scene0::OnCreate() {
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	cube = new Model0();
	sphere = new Model1();

	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect =  float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	//load the dpoubles too to the samething
	projectionMatrix = MMath::perspective(45.0f, aspect, 0.1f, 100.0f);
	modelViewMatrix.loadIdentity();

	//sphereprojectionMatrix = MMath::perspective(45.0f, aspect, 0.1f, 100.0f);
	spheremodelViewMatrix.loadIdentity();
	
	//modelViewMatrix =  MMath::lookAt(Vec3(0.0f, 0.0f, 0.499999999999999999999999999999999999999f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

}

void Scene0::OnDestroy(){

	/// Cleanup Assets
	if(cube) delete cube;
	cube = nullptr;

	if (sphere) delete sphere;
	sphere == nullptr;
}
float aangle = 0.0f;
void Scene0::Update(const float deltaTime){
 
	aangle += 0.5f;
	modelViewMatrix = MMath::rotate(aangle, 0.0F, 1.0F, 0.0F);
	spheremodelViewMatrix = MMath::rotate(aangle, 0.0f, 1.0f, 0.0f);
}

void Scene0::Render() const{
	/// Draw your scene here
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);

	cube->Render(projectionMatrix, modelViewMatrix, normalMatrix);
	//use YOUR OWN DOUBLE CREATED THIGNS
	sphere->Render(projectionMatrix, spheremodelViewMatrix, normalMatrix);

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	///std::cout << "event!!" << std::endl;
}