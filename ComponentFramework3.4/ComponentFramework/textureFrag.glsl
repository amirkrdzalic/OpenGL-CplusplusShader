#version 330
in  vec2 textCoords;
//in vec3 vertNormal; 

out vec4 fragColor;

uniform sampler2D myTexture0;  

void main() { 	

	//fragColor = texture2D(myTexture0, textCoords);
  fragColor = vec4(1.0,0.0,0.0,0.0); 
}