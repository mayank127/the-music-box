#include "table.h"
#include <GL/glut.h>
#include <iostream>


table::table(){

}
void table::init(){
	int size1=2, size2=20, size3=2;
	legs = glGenLists(1);
	glNewList(legs,GL_COMPILE);
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture( GL_TEXTURE_2D, 0 );
		glPushMatrix();
			glTranslatef(-50.0, 0.0, 0.0);
			//front
			glPushMatrix();
				createSide(size1,size2);
			glPopMatrix();
			//below
			glPushMatrix();
				glRotatef(-90, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
			//left
			glPushMatrix();
				glRotatef(90, 0.0, 1.0, 0.0);
				createSide(size3,size2);
			glPopMatrix();

			//right
			glPushMatrix();
				glTranslatef(size1-1, 0.0, 0.0);
				glRotatef(90, 0.0, 1.0, 0.0);
				createSide(size3,size2);
			glPopMatrix();

			//back
			glPushMatrix();
				glTranslatef( 0.0, 0.0, -size3);
				createSide(size1,size2);
			glPopMatrix();

			//top
			glPushMatrix();
				glTranslatef(0.0, size2, -size3);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
		glPopMatrix();
	glEndList();
	size1=22, size2=2, size3=22;
	top = glGenLists(1);
	glNewList(top,GL_COMPILE);
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
			glTranslatef(-70.0, 20.0, 0.0);
			//front
			glPushMatrix();
				createSide(size1,size2);
			glPopMatrix();
			//below
			glPushMatrix();
				glRotatef(-90, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
			//left
			glPushMatrix();
				glRotatef(90, 0.0, 1.0, 0.0);
				createSide(size3,size2);
			glPopMatrix();

			//right
			glPushMatrix();
				glTranslatef(size1-1, 0.0, 0.0);
				glRotatef(90, 0.0, 1.0, 0.0);
				createSide(size3,size2);
			glPopMatrix();

			//back
			glPushMatrix();
				glTranslatef( 0.0, 0.0, -size3);
				createSide(size1,size2);
			glPopMatrix();

			//top
			glPushMatrix();
				glTranslatef(0.0, size2, -size3);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
		glPopMatrix();
	glEndList();
}

void table::createSide(float size1, float size2){
	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0,0.0);
		glVertex3f(size1, 0.0, 0.0);
		glTexCoord2d(1.0,1.0);
		glVertex3f(size1, size2, 0.0);
		glTexCoord2d(0.0,1.0);
		glVertex3f(0.0, size2, 0.0);
	glEnd();
}

void table::draw(){
	glPushMatrix();
		glCallList(legs);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		glCallList(legs);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-20.0, 0.0, 0.0);
		glCallList(legs);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-20.0, 0.0, -20.0);
		glCallList(legs);
	glPopMatrix();
	glPushMatrix();
		glCallList(top);
	glPopMatrix();
}
