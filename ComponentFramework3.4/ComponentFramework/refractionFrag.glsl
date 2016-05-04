#version 330

in vec3 tCoords;
in vec4 Normal;
in vec4 Position;
 
out vec4 fragColor;

uniform vec3 cameraPos;
uniform samplerCube myTexture0;

void main() { 
	
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position.xyz - cameraPos);
	vec3 R = refract(I, normalize(Normal.xyz), ratio);
	vec3 Reflection = reflect(I, normalize(Normal.xyz));
	fragColor = mix(texture(myTexture0, Reflection), texture(myTexture0, R), 0.5f);
} 
