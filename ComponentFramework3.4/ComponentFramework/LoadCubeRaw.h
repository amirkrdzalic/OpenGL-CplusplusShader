#pragma once
#include <stdio.h>
#include <GL\glew.h>

GLuint LoadCubeRAW(const char * positive_x_image, const char * negative_x_image,
	               const char * positive_y_image, const char * negative_y_image,
	               const char * positive_z_image, const char * negative_z_image,
	               int width, int height); 

