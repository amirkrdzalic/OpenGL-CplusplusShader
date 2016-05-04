#include "Model0.h"
#include "QuadSphere.h"
#include "Shader.h"
#include "LoadTextureRAW.h"
#include "LoadCubeRaw.h"
using namespace GAME;


Model0::Model0():quadSphere(nullptr), skybox(nullptr),shader(nullptr),skyboxshader (nullptr){
	OnCreate();
}

bool Model0::OnCreate(){
	//ve
	/// Create a cube
	quadSphere = new QuadSphere(0); 

	//spherereflect = new QuadSphere(2); 

	//lightPos = Vec3(10.0, 10.0, 10.0);
    shader = new Shader("skyboxVert.glsl", "skyboxfrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "vTexture"); 

	//textureID = loadTexturesRAW("internalreflect.raw", 1024, 1024);
	textureID = LoadCubeRAW("pos.raw", "negx.raw", 
							"posy.raw", "negy.raw",
							"posz.raw", "negz.raw", 
							 2048, 2048);	

	GLuint loc = glGetUniformLocation(shader->getProgram(), "myTexture0");
	glUniform1ui(loc, textureID);	

	#define VERTEX_LENGTH 	(quadSphere->getNumVertices() * (sizeof(Vec4)))
	#define NORMAL_LENGTH 	(quadSphere->getNumVertices() * (sizeof(Vec4)))
	#define TEXCOORD_LENGTH (quadSphere->getNumVertices() * (sizeof(Vec2)))
	
	

    /// Create and initialize vertex buffer object VBO
    
    glGenBuffers(1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);/// This binds buffer to the target name GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH , NULL, GL_STATIC_DRAW );


	 /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glEnableVertexAttribArray(0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, quadSphere->getVerticies() );
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) );


	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
	glEnableVertexAttribArray(1);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, quadSphere->getNormals() );
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH) );


	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
	glEnableVertexAttribArray(2);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH , TEXCOORD_LENGTH , quadSphere->getTexCoords());
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH) );

	//glBindVertexArray(vbo); 
	/*glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0); */
	  
	#undef VERTEX_LENGTH
	#undef NORMAL_LENGTH
	#undef TEXCOORD_LENGTH

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	modelMatrix = MMath::lookAt(Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));

	glBindBuffer(GL_ARRAY_BUFFER,0); /// Unbinds the buffer by setting it to zero 
	return true;
}


void Model0::OnDestroy(){
	glDeleteBuffers(1,  &vbo);
}

void Model0::Update(const float deltaTime){}



void Model0::Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const{
	
	glUseProgram(shader->getProgram());
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, modelViewMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	//glUniform3fv(lightPosID, 1, lightPos);
	
	glDrawArrays(GL_QUADS, 0,quadSphere->getNumVertices());
	//glDepthMask(GL_TRUE); 
	glBindVertexArray(0); 
}


Model0::~Model0(){
	if(quadSphere) delete quadSphere;
	if(shader) delete shader;
}
