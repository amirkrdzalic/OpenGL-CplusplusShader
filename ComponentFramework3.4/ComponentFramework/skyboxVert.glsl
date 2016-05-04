#version 330
in  vec4 vVertex;
in  vec4 vNormal; 
in  vec3 vTexture; 

out vec3 tCoords; 
	
/*out VS_OUT{
	vec3 FragPos; 
	vec3 Normal; 
	vec4 FragPosLightSpace; 
	} vs_out; */

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;


void main() {
	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
	/*vs_out.FragPos = vec3(modelViewMatrix * vVertex); 
	//vs_out.Normal = transpose(inverse(mat3(modelViewMatrix))) * vec3(vNormal); */
	tCoords = vVertex.xyz; 
	//vs_out.FragPosLightSpace = lightPos * vec4(vs_out.FragPos, 1.0); 

}
