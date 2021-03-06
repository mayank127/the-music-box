#include "bone.h"
#include "joint.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

bone::bone(float x,float y,float z, string name){
	this->x = x;
	this->y = y;
	this->z = z;
	this->childeren = childeren;
	this->name = name;
	this->muscle = 0;
	this->texture = 0;
}
bone::bone(float x,float y,float z,list<joint*> childeren,string name){
	this->x = x;
	this->y = y;
	this->z = z;
	this->childeren = childeren;
	this->name = name;
	this->muscle = 0;
	this->texture = 0;
}
bone::bone(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->childeren = list<joint*>();
	name = "";
	this->muscle = 0;
	this->texture = 0;
}

void bone::draw(){
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0,0,0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(x,y,z);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glCallList(muscle);
	for (list<joint*>::iterator iterator = childeren.begin(), end = childeren.end(); iterator != end; ++iterator) {
		(*iterator)->draw();
	}
}
