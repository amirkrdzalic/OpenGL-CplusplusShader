#version 330

in vec3 tCoords; 

 
out vec4 fragColor;

uniform samplerCube myTexture0;

void main() { 
	
	vec3 newtextcoords = tCoords; 
	newtextcoords *= 1.0; 
	fragColor = texture(myTexture0,newtextcoords);
	
} 
