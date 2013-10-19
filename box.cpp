#include <GL/glut.h>
#include <iostream>
#include "box.h"

box::box(float size1, float size2, float rx, float x, float y, float z){
	this->size1 = size1;
	this->size2 = size2;
	this->rx = rx;
	this->x= x;
	this->y= y;
	this->z= z;
	createDL();

}

box::box(){
	this->size1 = 10;
	this->size2 = 6;
	this->rx = 90;
	this->x= 0;
	this->y= 0;
	this->z= 0;
	this->dx=0;
}

void box::createSide(float size1, float size2){
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1.0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 0.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 0.0);

		glNormal3f(0, 0, 1.0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 1.0);

		glNormal3f(0, 1.0, 0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, size2, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(0.0, size2, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, size2, 0.0);

		glNormal3f(0, -1.0, 0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, 0, 0.0);

		glNormal3f(1, 0, 0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 0.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, size2, 1.0);

		glNormal3f(-1, 0, 0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, size2, 1.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 0.0);
	glEnd();
}
void box::createDL(){

	boxDL11 = glGenLists(1);
	glNewList(boxDL11,GL_COMPILE);
		createSide(size1,size1);
	glEndList();

	boxDL12 = glGenLists(1);
	glNewList(boxDL12,GL_COMPILE);
		createSide(size1,size2);
	glEndList();



}


void box::draw(){
	glPushMatrix();
		glTranslatef(x,y,z);

		glBindTexture( GL_TEXTURE_2D, this->texture );
		//front
		glColor3f(1.0, 1.0, 1.0);
		glCallList(boxDL12);
		//below
		glPushMatrix();
			glTranslatef(0,dx,0);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glCallList(boxDL11);
		glPopMatrix();
		//left
		glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glCallList(boxDL12);
		glPopMatrix();
		//right
		glPushMatrix();
			glTranslatef(size1-1, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			glCallList(boxDL12);
		glPopMatrix();

		//back
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -size1);
			glCallList(boxDL12);
		glPopMatrix();

		//top
		glPushMatrix();
			glTranslatef(0.0, size2, -size1);
			if(rx>90) rx = 90;
			else if(rx<0) rx = 0;
			glRotatef(rx, 1.0, 0.0, 0.0);
			glCallList(boxDL11);
		glPopMatrix();
	glPopMatrix();
}
