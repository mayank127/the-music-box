#include "light.h"
#include <GL/glut.h>
#include <iostream>

light::light(){
}
void light::init(){
	GLfloat amb[] = {0,0,0, 1};
	GLfloat dif[] = {1.0,1.0,1.0, 1};

	glLightfv(GL_LIGHT0, GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT,amb);
}
void light::draw(){
	GLfloat light_position[] = {0.0,0.0,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);
}