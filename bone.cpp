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
}
bone::bone(float x,float y,float z,list<joint*> childeren,string name){
	this->x = x;
	this->y = y;
	this->z = z;
	this->childeren = childeren;
	this->name = name;
}
bone::bone(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->childeren = list<joint*>();
	name = "";
}

void bone::draw(){
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0,0,0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(x,y,z);
	glEnd();
	for (list<joint*>::iterator iterator = childeren.begin(), end = childeren.end(); iterator != end; ++iterator) {
		(*iterator)->draw();
	}
}