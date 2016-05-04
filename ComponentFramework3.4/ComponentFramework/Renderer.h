#ifndef RENDERER_H
#define RENDERER_H

#include "GL/glew.h"
#include "Vector.h"

namespace GAME {

class Renderer {
public:
	enum StdAttributes {VERTEX_ATTRIB = 0, NORMAL_ATTRIB, UV_ATTRIB, COLOR_ATTRIB };
	/// C11 precautions delete these non-needed default constructors and operators
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator = (const Renderer&) = delete;
	Renderer& operator = (Renderer&&) = delete;

	Renderer();
	~Renderer();
	
	bool LoadQuadArray(MATH::Vec3 *vertex, MATH::Vec3* normals, MATH::Vec2* uv, int length);
	int CreateShader(const char *vsFilename, const char *fsFilename, const char *vertexAttributeName, const char *normalAttributeName, const char* uvAttributeName);

	inline GLuint getProgram() { return shader; }
private:
	/// GLuint vao;
	GLuint  vbo; 
	GLuint shader;

protected:
	void Renderer::readCompileAttach(const char *vsFilename, const char *fsFilename);
	void link();
	char* readTextFile(const char *filename);
	
	
};


}
#endif 
