#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"
#include "Window.h"
#include "Matrix.h"

using namespace MATH;
namespace GAME {
	class Scene {
	public:
		explicit Scene(class Window& windowRef);
		virtual ~Scene();

		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator = (const Scene&) = delete;
		Scene& operator = (Scene&&) = delete;
		
		

		/// Create the following four abstract functions and make them polymorphic
		/// The proper term for these are "pure viruals"
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
		virtual void HandleEvents(const SDL_Event &SDLEvent) = 0;
		virtual void OnResize(const int, const int) = 0;

	protected:
		Window* windowPtr;

		Matrix4 projectionMatrix;
		Matrix4 sphereprojectionMatrix;

		Matrix4 modelViewMatrix;
		Matrix4 spheremodelViewMatrix;

		Matrix3 normalMatrix;
		Matrix3 spherenormalMatrix;

		Matrix4 viewMatrix;
		Vec3 pos; 

	};
}

#endif