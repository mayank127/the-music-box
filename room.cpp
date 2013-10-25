#include "room.h"
#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>


room::room(){
	this->rd = 45;
}
void room::init(){
	int size1=201, size2=200, size3=250;
	table_tex = SOIL_load_OGL_texture
	(
	  "images/table.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);

	wall1_tex = SOIL_load_OGL_texture
	(
	  "images/wall1.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	
	wall2_tex = SOIL_load_OGL_texture
	(
	  "images/wall2.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	
	walls_tex = SOIL_load_OGL_texture
	(
	  "images/walls.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);

	door_tex = SOIL_load_OGL_texture
	(
	  "images/door.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	
	silver_tex = SOIL_load_OGL_texture
	(
	  "images/silver.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);

	walls = glGenLists(1);
	glNewList(walls,GL_COMPILE);
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();


			//front
			glPushMatrix();
				glBindTexture( GL_TEXTURE_2D, wall2_tex);
				createSide(size1/3,size2/2);
				glBindTexture( GL_TEXTURE_2D, wall1_tex);
				glTranslatef(0,size2/2,0);
				createSide(size1/3,size2/2);
				glTranslatef(size1/3,0,0);
				createSide(size1/3,size2/2);
				glTranslatef(size1/3,0,0);
				createSide(size1/3,size2/2);
				glBindTexture( GL_TEXTURE_2D, wall2_tex);
				glTranslatef(0,-size2/2,0);
				createSide(size1/3,size2/2);
			glPopMatrix();
			//below
			glBindTexture( GL_TEXTURE_2D, walls_tex);
			glPushMatrix();
				glRotatef(270, 1.0, 0.0, 0.0);
				createSide(size1,size3);
			glPopMatrix();

			//right
			glPushMatrix();
				glTranslatef(size1-1, 0.0, 0.0);
				glRotatef(90, 0.0, 1.0, 0.0);
				createSide(size3,size2);
			glPopMatrix();

			//back
			glPushMatrix();
				glTranslatef( size1-1, 0.0, -size3);
				glRotatef(180, 0.0, 1.0, 0.0);
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

	size1 = 80; size2 = 50;
	table  = glGenLists(1);
	glNewList(table, GL_COMPILE);
		glBindTexture( GL_TEXTURE_2D, table_tex );

		glColor3f(1.0, 1.0, 1.0);
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

	size1 = 15; size2 = 20;
	chair  = glGenLists(1);
	glNewList(chair, GL_COMPILE);

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
			glScalef(2,2,2);
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

	cabinet  = glGenLists(1);
	glNewList(cabinet, GL_COMPILE);

		glPushMatrix();
			glScalef(2,2,2);
			//back
			glPushMatrix();
				createSide(size1,size2);
			glPopMatrix();
			//front
			glPushMatrix();
				glTranslatef(0, 0, size1);
				createSide(size1,size2);
			glPopMatrix();
			//down
			glPushMatrix();
				glTranslatef(0.0, 1.0, 0);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size1);
			glPopMatrix();
			//up
			glPushMatrix();
				glTranslatef(0, size2, 0);
				glRotatef(90, 1.0, 0.0, 0.0);
				createSide(size1,size1);
			glPopMatrix();
			//left
			glPushMatrix();
				glTranslatef(2.0, 0, 0);
				glRotatef(90, 0.0, -1.0, 0.0);
				createSide(size1,size2);
			glPopMatrix();
			//right
			glPushMatrix();
				glTranslatef(size1, 0, 0);
				glRotatef(60, 0.0, -1.0, 0.0);
				createSide(size1,size2);
				glTranslatef(size1*3/4,size2/2,-2);
				glPushMatrix();
					glTranslatef(0,0,0);
					createSide(2,2);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90,1.0,0.0,0.0);
					createSide(2,2);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,2,0);
					glRotatef(90,1.0,0.0,0.0);
					createSide(2,2);
				glPopMatrix();
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
			glScalef(2,2,2);
			glPushMatrix();
				glTranslatef(0,0.5,0);
				glPushMatrix();
					glTranslatef(0.0,-2.0,0.0);
					glRotatef(90, 1.0, 0.0 ,0.0);
					gluDisk(quadratic,0.0f,9.0f,32,32);
				glPopMatrix();
				glPushMatrix();
					glRotatef(270, 1.0, 0.0 ,0.0);
					gluDisk(quadratic,0.0f,9.0f,32,32);
				glPopMatrix();
				glRotatef(90, 1.0, 0.0 ,0.0);
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
		glPopMatrix();
	glEndList();
	
	lamp = glGenLists(1);
	glNewList(lamp, GL_COMPILE);
		glPushMatrix();
			glBindTexture( GL_TEXTURE_2D, silver_tex);

			gluQuadricOrientation(quadratic,GLU_OUTSIDE);
			glTranslatef(-4.0,15.0,6.0);
			glPushMatrix();
				glRotatef(90, 1.0, 0.0 ,0.0);
				gluCylinder(quadratic,4.0f,10.0f,10.0f,32,32);
			glPopMatrix();
			glTranslatef(0.0,5.0,0.0);
			glPushMatrix();
				glRotatef(90, 1.0, 0.0 ,0.0);
				gluCylinder(quadratic,4.0f,4.0f,12.0f,32,32);
			glPopMatrix();
			glPushMatrix();
				glColor4f(1,1,1,0.4);
				glTranslatef(0.0,12.0,0.0);
				glRotatef(90, 1.0, 0.0 ,0.0);
				gluQuadricOrientation(quadratic,GLU_INSIDE);
				gluCylinder(quadratic,12.0f,12.0f,12.0f,32,32);
				gluDisk(quadratic,0.0f,12.0f,32,32);
			glPopMatrix();
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
	int size1=201, size2=200, size3=250;
	glPushMatrix();
		glTranslatef(-100,-100,+100);
		glCallList(walls);
		glPushMatrix();
			glBindTexture( GL_TEXTURE_2D, door_tex);
			glTranslatef(size1/3,0,0);
			glRotatef(rd,0.0,-1.0,0.0);
			createSide(size1/3,size2/2);
		glPopMatrix();
		glTranslatef(60, 50,-150);
		glCallList(table);
		glTranslatef(25, -10, -30);
		glCallList(chair);
		glTranslatef(-60, -30, -50);
		glCallList(cabinet);
		glTranslatef(150, 30, 20);
		glCallList(stool);
		glCallList(lamp);
	glPopMatrix();
}
void room::drawLeftWall(){
	int size1=201, size2=200, size3=250;
	//left
	glBindTexture( GL_TEXTURE_2D, walls_tex);
	glPushMatrix();
		glTranslatef(-100,-100,+100-size3);
		glRotatef(270, 0.0, 1.0, 0.0);
		createSide(size3,size1);
	glPopMatrix();
}
