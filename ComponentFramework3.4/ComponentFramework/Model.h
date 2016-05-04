#ifndef MODEL_H
#define MODEL_H
#include "MMath.h"
#include "Renderer.h"
#include "Scene.h"

using namespace MATH;

namespace GAME {

class Model {
protected:
	Vec3 pos;
	Vec3 vel;
	Vec3 orientation;
	Vec3 gravity;
	Sphere bounding;
	Matrix4 modelMatrix;

	
public:

	Renderer *renderer;
	inline void SetPos(const Vec3& pos_){ pos = pos_; }
	inline void SetVel(const Vec3& vel_){ vel = vel_; }

	virtual ~Model(){};

	Model(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator = (const Model&) = delete;
	Model& operator = (Model&&) = delete;

	Model() : gravity(0.0f,-9.8f,0.0f)  { };
 

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix)const = 0;


	void Update(const float deltaTime){
		pos += vel * deltaTime + 0.5f * gravity * deltaTime * deltaTime;
		vel += gravity * deltaTime;
	}

};




} /// end of namespace

#endif