#include <GL/glut.h>
#include <iostream>
#include "box.h"

box::box(float size, float rx, float x, float y, float z){
	this->size = size;
	this->rx = rx;
	this->x= x;
	this->y= y;
	this->z= z;
}

box::box(){
	this->size = 10;
	this->rx = 90-30;
	this->x= 0;
	this->y= 0;
	this->z= 0;
}

void box::rectangle(){
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(size, 0.0, 0.0);
		glVertex3f(size, size, 0.0);
		glVertex3f(0.0, size, 0.0);
	glEnd();
}

void box::draw(){
	glPushMatrix();
		glTranslatef(x,y,z);
		//front
		glColor3f(1.0, 1.0, 1.0);
		rectangle();
		//below
		glPushMatrix();
			glRotatef(-90, 1.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			rectangle();
		glPopMatrix();
		//top
		glPushMatrix();
			glTranslatef(0.0, size, 0.0);
			glTranslatef(0.0, 0.0 , -size);
			if(rx>90) rx = 90;
			else if(rx<0) rx = 0;
			glRotatef(rx, 1.0, 0.0, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			rectangle();
		glPopMatrix();
		//left
		glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			rectangle();
		glPopMatrix();
		//right
		glPushMatrix();
			glTranslatef(size, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			rectangle();
		glPopMatrix();
		//back
		glPushMatrix();
			glColor3f(0.0, 0.0, 1.0);
			glTranslatef( 0.0, 0.0, -size);
			rectangle();
		glPopMatrix();
	glPopMatrix();
}
