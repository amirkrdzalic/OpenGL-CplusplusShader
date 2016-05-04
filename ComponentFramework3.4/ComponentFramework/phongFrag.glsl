#version 330
in  vec3 tCoords; 

out vec4 fragColor;
uniform samplerCube myTexture0; 

void main() { 
	/// I could have passed these in as Uniforms but for simplicity, 
	/// I'll just define them here: specular, diffuse, ambient for the surface material 
	vec3 newtextcoords = tCoords; 
	newtextcoords *= -1.0; 
	fragColor = texture(myTexture0, newtextcoords); // ka + (diff * kd) + (spec * ks);
	
} 
