#include "room.h"
#include <GL/glut.h>
#include <iostream>


room::room(){

}
void room::init(){
	int size1=201, size2=200, size3=250;
	walls = glGenLists(1);
	glNewList(walls,GL_COMPILE);
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture( GL_TEXTURE_2D, 0 );
			//front
			glPushMatrix();
				createSide(size1/3,size2/2);
				glTranslatef(0,size2/2,0);
				createSide(size1/3,size2/2);
				glTranslatef(size1/3,0,0);
				createSide(size1/3,size2/2);
				glTranslatef(size1/3,0,0);
				createSide(size1/3,size2/2);
				glTranslatef(0,-size2/2,0);
				createSide(size1/3,size2/2);
			glPopMatrix();
			//below
			glColor3f(1.0, 0.0, 0.0);
			glPushMatrix();
				glRotatef(270, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
			//left
			glColor3f(0.0, 0.0, 1.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, -size3);
				glRotatef(270, 0.0, 1.0, 0.0);
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
				glTranslatef( size1-1, 0.0, -size3);
				glRotatef(180, 0.0, 1.0, 0.0);
				createSide(size1,size2);
			glPopMatrix();

			//top
			glColor3f(1.0, 1.0, 0.0);
			glPushMatrix();
				glTranslatef(0.0, size2, -size3);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();
		glPopMatrix();
	glEndList();

	size1 = 80; size2 = 50;
	table  = glGenLists(1);
	glNewList(table, GL_COMPILE);
		glPushMatrix();
			//top
			glPushMatrix();
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size2);
			glPopMatrix();

			//legs
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.0);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,2);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(size1-1, 0.0, 0.0);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,2);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(size1-1, 0.0, size2-1);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,2);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, size2-1);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,2);
			glPopMatrix();
		glPopMatrix();
	glEndList();
	
	size1 = 15; size2 = 20;
	chair  = glGenLists(1);
	glNewList(chair, GL_COMPILE);
		glPushMatrix();
			//top
			glPushMatrix();
				createSide(size1,size2);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size2);
			glPopMatrix();

			//legs
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.0);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(size1-1, 0.0, 0.0);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(size1-1, 0.0, size2-1);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, size2-1);
				glRotatef(-90, 0.0, 0.0, 1.0);
				createSide(size2,1);
			glPopMatrix();
		glPopMatrix();
	glEndList();
	
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	stool = glGenLists(1);
	glNewList(stool, GL_COMPILE);
	
		glPushMatrix();
			glTranslatef(0.0,0.5,0.0);
			glRotatef(90, 1.0, 0.0 ,0.0);
			gluDisk(quadratic,0.0f,9.0f,32,32);
			gluCylinder(quadratic,9.0f,9.0f,2.0f,32,32);
		glPopMatrix();
		glPushMatrix();
			glRotatef(110, 1.0, 0.0 ,-0.25);
			gluCylinder(quadratic,1.0f,1.0f,20.0f,32,32);
		glPopMatrix();
		glPushMatrix();
			glRotatef(110, 1.0, 0.0 ,0.25);
			gluCylinder(quadratic,1.0f,1.0f,20.0f,32,32);
		glPopMatrix();
		glPushMatrix();
			glRotatef(70, 1.0, 0.0 ,0.25);
			gluCylinder(quadratic,1.0f,1.0f,20.0f,32,32);
		glPopMatrix();
		glPushMatrix();
			glRotatef(70, 1.0, 0.0 ,-0.25);
			gluCylinder(quadratic,1.0f,1.0f,20.0f,32,32);
		glPopMatrix();
	glEndList();
}

void room::createSide(float size1, float size2){
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

void room::draw(){
	glPushMatrix();
		glTranslatef(-100,-100,+100);
		glCallList(walls);
		glTranslatef(60, 50,-150);
		glCallList(table);
		glTranslatef(30, 0, -30);
		glCallList(chair);
		glTranslatef(60, 0, 0);
		glCallList(stool);
	glPopMatrix();
}
