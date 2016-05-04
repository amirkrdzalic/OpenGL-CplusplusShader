#version 330
in  vec4 vVertex;
in  vec4 vNormal;

out vec4 Normal; 
out vec4 Position;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main() {

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
	Normal = transpose(inverse(modelViewMatrix)) * vNormal;
	Position = vec4(modelViewMatrix * vVertex);

	
}
