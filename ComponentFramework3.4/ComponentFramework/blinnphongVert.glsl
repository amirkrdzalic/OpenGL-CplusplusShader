#version 330
in  vec4 vVertex;
in  vec4 vNormal; 
in  vec3 vTexture; 

out vec3 tCoords; 
	


uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;


void main() {
	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
	tCoords = vVertex.xyz; 
}
