#ifndef MODEL1_H
#define MODEL1_H
#include "Model.h"

namespace GAME {
	class Shader; /// Forward declarations;
	class QuadSphere;

	class Model1 :public Model {
	public:
		Model1();


		Model1(const Model1&) = delete;
		Model1(Model1&&) = delete;
		Model1& operator = (const Model1&) = delete;
		Model1& operator = (Model1&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
		virtual ~Model1();

	private:
		QuadSphere *quadSphere;
		QuadSphere * skybox;
		Shader *shader;
		Shader *sphereshader;
		Shader * skyboxshader;
		GLuint vbo;
		Vec3 lightPos;
		GLuint projectionMatrixID;
		GLuint modelViewMatrixID;
		GLuint sphereprojectionMatrixID;
		GLuint spheremodelViewMatrixID;
		GLuint normalMatrixID;
		GLuint spherenormalMatrixID;
		GLuint modelMatrixID;
		GLuint lightPosID;
		GLuint textureID;
		//GLuint loc; 
	};
}
#endif