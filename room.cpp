#include "room.h"
#include <GL/glut.h>
#include <iostream>


room::room(){

}
void room::init(){
	int size1=150, size2=150, size3=150;
	walls = glGenLists(1);
	glNewList(walls,GL_COMPILE);
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture( GL_TEXTURE_2D, 0 );
		//front
		glPushMatrix();
			createSide(size1/3,size2);
			glTranslatef(size1/3,size2/2,0);
			createSide(size1/3,size2/2);
			glTranslatef(size1/3,-size2/2,0);
			createSide(size1/3,size2);
		glPopMatrix();
		//below
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
			glRotatef(-90, 1.0, 0.0, 0.0);
			createSide(size1,size3);
		glPopMatrix();
		//left
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			createSide(size3,size1);
		glPopMatrix();

		//right
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(size1-1, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			createSide(size3,size2);
		glPopMatrix();

		//back
		glColor3f(1.0, 0.0, 1.0);
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -size3);
			createSide(size1,size2);
		glPopMatrix();

		//top
		glColor3f(1.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(0.0, size2, -size3);
			glRotatef(90, 1.0, 0.0, 0.0);
			createSide(size1,size3);
		glPopMatrix();
	glEndList();
}

void room::createSide(float size1, float size2){
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 0.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 0.0);

		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 1.0);

		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, size2, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(0.0, size2, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, size2, 0.0);

		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, 0, 0.0);

		glTexCoord2d(0.0,0.0);
		glVertex3f(size1, 0.0, 1.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 0.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(size1, size2, 1.0);

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

void room::draw(){
	glCallList(walls);

}
