#include <iostream>
#include <fstream>
#include <cassert>
#include "Renderer.h"
#include "Debug.h"


using namespace MATH;
using namespace GAME;

Renderer::Renderer():vbo(0),shader(0){
	
}

Renderer::~Renderer(){
	
}

//void Renderer::Render() const {
//	glUseProgram(shader);
//	///glDrawArrays(GL_QUADS, 0, numVertices);
//
//
//
//	glUseProgram(0);
//}

bool Renderer::LoadQuadArray(Vec3 *vertex, Vec3* normals, Vec2* uv, int length){
	///glGenVertexArrays(1, &vao); /// Generates a unique name(s), in this case I just want one name  
    ///glBindVertexArray(vao);		/// Commits the unique name as a vertex array object
	
    glGenBuffers(1, &vbo );  // Generate a unique name 
    glBindBuffer(GL_ARRAY_BUFFER, vbo); /// Make it active 
    glBufferData(GL_ARRAY_BUFFER,  (2*length*sizeof(Vec3) + length*sizeof(Vec2))  , NULL, GL_STATIC_DRAW ); /// Allocate the size of the buffer
	
	glEnableVertexAttribArray(VERTEX_ATTRIB); /// Make the identifier VERTEX_ATTRIBUTE (0) active 
    glBufferSubData(GL_ARRAY_BUFFER, 0, length*sizeof(Vec3), vertex ); /// Load the subsection of the overall array into the buffer
	glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) ); /// Describe how the data from the proevious call was arranged

	glEnableVertexAttribArray(NORMAL_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, length*sizeof(Vec3), length*sizeof(Vec3), normals );
	glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(length*sizeof(Vec3)) );

	glEnableVertexAttribArray(UV_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, 2*length*sizeof(Vec3), length * sizeof(Vec2), uv );
	glVertexAttribPointer(VERTEX_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(2*length*sizeof(Vec3)) );

	return true;
}


int Renderer::CreateShader(const char *vsFilename, const char *fsFilename, const char *vertexAttributeName, const char *normalAttributeName, const char* uvAttributeName) {
	/// Bind all the named attributes - skip it if NULL
	GLint status;
	readCompileAttach(vsFilename,fsFilename);
	if(vertexAttributeName){ 
		glBindAttribLocation(shader, VERTEX_ATTRIB, vertexAttributeName);
		printf("Binding attribute <%s> loc: %d\n",vertexAttributeName, VERTEX_ATTRIB);
	}
	if(normalAttributeName){
		glBindAttribLocation(shader, NORMAL_ATTRIB, normalAttributeName);
		printf("Binding attribute <%s> loc: %d\n",normalAttributeName, NORMAL_ATTRIB);
	}
	if(uvAttributeName){
		glBindAttribLocation(shader, UV_ATTRIB, uvAttributeName);
		printf("Binding attribute <%s> loc: %d\n",uvAttributeName, UV_ATTRIB);
	}
	
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if(status == 0) {
		GLsizei errorLogSize = 0;
		std::string errorLog;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
		errorLog.resize(errorLogSize);
		glGetProgramInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
				
	}
	return shader;
}


void Renderer::readCompileAttach(const char *vsFilename, const char *fsFilename){
    GLint status;
	
		
	const char* vsText = readTextFile(vsFilename);
	const char* fsText = readTextFile(fsFilename);
	if (vsText == NULL || fsText == NULL) return;

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	/// Check for errors
	if (vertShader == 0 || fragShader == 0) {
		std::string errorMsg("Can't create a new shader");
		throw errorMsg;
	}
    
	glShaderSource(vertShader, 1, &vsText, 0);   
	glShaderSource(fragShader, 1, &fsText, 0);
    
	glCompileShader(vertShader);
	/// Check for errors
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if(status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}

	glCompileShader(fragShader);
	/// Check for errors
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if(status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetShaderInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}
    
	shader = glCreateProgram();
	glAttachShader(shader, fragShader);
	glAttachShader(shader, vertShader);
	/// release the memory allocated in readTextFile()
	if(vsText) delete[] vsText;
	if(fsText) delete[] fsText;

	
	 
}


void Renderer::link(){
	GLint status;
	glLinkProgram(shader);
	/// Check for errors
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if(status == 0) {
		GLsizei errorLogSize = 0;
		std::string errorLog;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
		errorLog.resize(errorLogSize);
		glGetProgramInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
		throw errorLog;
	}
}

/// Read from a specified file and return a char array from the heap 
/// The memory must be deleted within this class. It may not be the best way 
/// to do this but it is all private and I did delete it! SSF
char* Renderer::readTextFile(const char *filename){
	char* buffer = NULL;
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {								/// Open the file
        file.seekg(0, std::ios::end);					/// goto the end of the file
        int bufferSize = (int) file.tellg();			/// Get the length of the file
		if(bufferSize == 0) {							/// If zero, bad file
			std::string errorMsg("Can't read shader file: ");
			std::string str2(filename);
			errorMsg += str2;
			throw errorMsg;								/// Bail out
		}
		buffer = new char[(int)(bufferSize + 1)];		/// Need to NULL terminate the array
        file.seekg(0, std::ios::beg);
        file.read(buffer, bufferSize);
		buffer[bufferSize] = '\0';						/// Add the NULL
		file.close();
    }else { 
		std::string errorMsg("Can't open shader file: ");
		printf("ERROR:%s:%s\n",filename,&errorMsg[0]);
	}
	return buffer;
}



/***

void QuadSphere::render(){

}
	



/// Set up vertex arrays for the vertex and color attributes
	/// These calls where in the vertex buffer the data is and how to move through it
	/// VERTEX_ATTRIB is the location, 4 is the length of each Vec of type GL_FLOAT, do not normalize, 
	/// the stride is zero and the beginning is zero (pointed to by the addr of a temp stack variable holding the value 0) - weird  
	/// pretty much the same as above but it starts at the end of the "points" array in bytes (pointed to by the addr of a temp stack variable)
	/// same as above but it starts at the end of the "points" array  + the "normal" array in bytes (pointed to by the addr of a temp stack variable)


// Create a vertex array object VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 
	
	 /// Create and initialize vertex buffer object VBO
    GLuint buffer;
    glGenBuffers(1, &buffer );
    glBindBuffer(GL_ARRAY_BUFFER, buffer); /// This binds buffer to the target name GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH , NULL, GL_STATIC_DRAW );
	
		 /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glEnableVertexAttribArray(VERTEX_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, vertex );
	glVertexAttribPointer(VERTEX_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) );


	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
	glEnableVertexAttribArray(NORMAL_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, normals );
	glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH) );


	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH , TEXCOORD_LENGTH , texCoords);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH) );
	
	
	


void Graphics::ReadCompileAttach(const char *vsFilename, const char *fsFilename){
    GLint status;
	shader = 0;
	vertShader = 0;
	fragShader = 0;
	try { 		
		const char* vsText = readTextFile(vsFilename);
		const char* fsText = readTextFile(fsFilename);
		if (vsText == NULL || fsText == NULL) return;

		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		/// Check for errors
		if (vertShader == 0 || fragShader == 0) {
			std::string errorMsg("Can't create a new shader");
			throw errorMsg;
		}
    
		glShaderSource(vertShader, 1, &vsText, 0);   
		glShaderSource(fragShader, 1, &fsText, 0);
    
		glCompileShader(vertShader);
		/// Check for errors
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				std::string errorLog;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(errorLogSize);
				glGetShaderInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
				throw errorLog;
			}

		glCompileShader(fragShader);
		/// Check for errors
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				std::string errorLog;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(errorLogSize);
				glGetShaderInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
				throw errorLog;
			}
    
		shader = glCreateProgram();
		glAttachShader(shader, fragShader);
		glAttachShader(shader, vertShader);
		/// release the memory allocated in readTextFile()
		if(vsText) delete[] vsText;
		if(fsText) delete[] fsText;

	}catch(std::string error){
		printf("ERROR:%s\n",&error[0]);
	}
	 
}

void Graphics::link(){
	GLint status;
	try{
			glLinkProgram(shader);
			/// Check for errors
			glGetProgramiv(shader, GL_LINK_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				std::string errorLog;
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(errorLogSize);
				glGetProgramInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
				throw errorLog;
			}
		
	}catch(std::string error){
		printf("ERROR:%s\n",&error[0]);
	}

}




//Shader::~Shader() {
//	glDetachShader(shader, fragShader);
//	glDetachShader(shader, vertShader);  
//	glDeleteShader(fragShader);
//	glDeleteShader(vertShader);
//	glDeleteProgram(shader);
//}

/// This is some code to explore the various Uniforms that might exist

//void Shader::handleUniforms(){
//	int count;
//	GLsizei actualLen;
//	GLint size;
//	GLint uniArrayStride;
//	GLenum type;
//	char *name;
//	int maxUniLength;
//	unsigned int loc;
//
//	glGetProgramiv(shader, GL_ACTIVE_UNIFORMS, &count);
//	printf("There are %d active Uniforms\n",count);
//	/// get the length of the longest named uniform
//	glGetProgramiv(shader, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniLength);
//
//	/// Create a little buffer to hold the uniform's name 
//	name = (char *)malloc(sizeof(char) * maxUniLength);
//
//	
//	for (int i = 0; i < count; ++i) {
//		/// Get the name of the ith uniform
//		glGetActiveUniform(shader, i, maxUniLength, &actualLen, &size, &type, name);
//		/// Get the (unsigned int) loc for this uniform
//		loc = glGetUniformLocation(shader, name);
//		
//		// -1 indicates that is not an active uniform, although it may be present in a
//		// uniform block
//		
//		glGetActiveUniformsiv(shader, 1, &loc, GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
//		printf("<%s> loc:%d stride:%d\n",name,loc);
//	}
//	free(name);
//}



***/

