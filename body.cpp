#include "body.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>

void body::init(){
	torso3 = bone(0.0, 5.0, 0.0,"torso3");
	torso1 = bone(0.0, 5.0, 0.0,"torso1");
	head = bone(0.0, 2.0, 0.0,"head");
	thighL = bone(0.0, -5.0, 0.0,"thighL");
	thighR = bone(0.0, -5.0, 0.0,"thighR");
	legL = bone(0.0, -5.0, 0.0,"legL");
	legR = bone(0.0, -5.0, 0.0,"legR");
	footL = bone(0.0, -1.0, 0.0,"footL");
	footR = bone(0.0, -1.0, 0.0,"footR");
	uarmL = bone(0.0, -5.0, 0.0,"uarmL");
	uarmR = bone(0.0, -5.0, 0.0,"uarmR");
	larmL = bone(0.0, -5.0, 0.0,"larmL");
	larmR = bone(0.0, -5.0, 0.0,"larmR");
	handL = bone(0.0, -1.0, 0.0,"handL");
	handR = bone(0.0, -1.0, 0.0,"handR");

	torso2 = joint(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, &torso1,"torso2");
	neck = joint(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, &head,"neck");
	hipL = joint(1.8, 0.0, 0.0, 0.0, 0.0, 0.0, &thighL,"hipL");
	hipR = joint(-1.8, 0.0, 0.0, 0.0, 0.0, 0.0, &thighR,"hipR");
	kneeL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &legL,"kneeL");
	kneeR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &legR,"kneeR");
	ankleL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footL,"footL");
	ankleR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footR,"footR");
	shoulderL = joint(3.0, 4.0, 0.0, 0.0, 0.0, 0.0, &uarmL,"shoulderL");
	shoulderR = joint(-3.0, 4.0, 0.0, 0.0, 0.0, 0.0, &uarmR,"shoulderR");
	elbowL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &larmL,"elbowL");
	elbowR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &larmR,"elbowR");
	wristL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &handL,"handL");
	wristR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &handR,"handR");

	torso3.childeren.push_back(&torso2);
	torso3.childeren.push_back(&hipL);
	torso3.childeren.push_back(&hipR);
	torso1.childeren.push_back(&neck);
	torso1.childeren.push_back(&shoulderL);
	torso1.childeren.push_back(&shoulderR);
	thighL.childeren.push_back(&kneeL);
	thighR.childeren.push_back(&kneeR);
	legL.childeren.push_back(&ankleL);
	legR.childeren.push_back(&ankleR);
	uarmL.childeren.push_back(&elbowL);
	uarmR.childeren.push_back(&elbowR);
	larmL.childeren.push_back(&wristL);
	larmR.childeren.push_back(&wristR);

	this->initConstraints();
	this->initMuscles();
	this->initJointMuscles();
	this->initTexture();
}

void body::initConstraints(){
	torso2.setConstraint(-70, 70, -30, 30, -70, 70);
	neck.setConstraint(-70, 70, -70, 70, -70, 70);
	hipL.setConstraint(-90, 90, -10, 10, -90, 90);
	hipR.setConstraint(-90, 90, -10, 10, -90, 90);
	kneeL.setConstraint(0, 150, 0, 0, 0, 0);
	kneeR.setConstraint(0, 150, 0, 0, 0, 0);
	ankleL.setConstraint(-120, 0, -20, 20, -10, 10);
	ankleR.setConstraint(-120, 0, -20, 20, -10, 10);
	shoulderL.setConstraint(-150, 150, -20, 20, -50, 180);
	shoulderR.setConstraint(-150, 150, -20, 20, -180, 50);
	elbowL.setConstraint(0, 0, 0, 0, -170, 0);
	elbowR.setConstraint(0, 0, 0, 0, 0, 170);
	wristL.setConstraint(-90, 90, -20, 20, -40, 40);
	wristR.setConstraint(-90, 90, -20, 20, -40, 40);
}

void body::initMuscles(){

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluQuadricTexture(quadratic, true);

	torso3.muscle = glGenLists(1);

	glNewList(torso3.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,2.3f,2.1f,4.0f,32,32);
		glPopMatrix();
	glEndList();

	torso1.muscle = glGenLists(1);
	glNewList(torso1.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,2.1f,2.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	head.muscle = glGenLists(1);
	glNewList(head.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,1.1f,1.3f,2.0f,32,32);
		glPopMatrix();
	glEndList();
	thighL.muscle = glGenLists(1);
	glNewList(thighL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.6f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	thighR.muscle = glGenLists(1);
	glNewList(thighR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.6f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	legL.muscle = glGenLists(1);
	glNewList(legL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	legR.muscle = glGenLists(1);
	glNewList(legR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	footL.muscle = glGenLists(1);
	glNewList(footL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,0.8f,32,32);
		glPopMatrix();
	glEndList();
	footR.muscle = glGenLists(1);
	glNewList(footR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,0.8f,32,32);
		glPopMatrix();
	glEndList();
	uarmL.muscle = glGenLists(1);
	glNewList(uarmL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.6f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	uarmR.muscle = glGenLists(1);
	glNewList(uarmR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.6f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	larmL.muscle = glGenLists(1);
	glNewList(larmL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	larmR.muscle = glGenLists(1);
	glNewList(larmR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,4.0f,32,32);
		glPopMatrix();
	glEndList();
	handL.muscle = glGenLists(1);
	glNewList(handL.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,0.8f,32,32);
		glPopMatrix();
	glEndList();
	handR.muscle = glGenLists(1);
	glNewList(handR.muscle, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadratic,0.5f,0.5f,0.8f,32,32);
		glPopMatrix();
	glEndList();
}

void body::initJointMuscles(){

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	torso2.muscle = glGenLists(1);
	glNewList(torso2.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,2.0f,32,32);
		glPopMatrix();
	glEndList();

	neck.muscle = glGenLists(1);
	glNewList(neck.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,1.1f,32,32);
		glPopMatrix();
	glEndList();

	hipL.muscle = glGenLists(1);
	glNewList(hipL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.6f,32,32);
		glPopMatrix();
	glEndList();

	hipR.muscle = glGenLists(1);
	glNewList(hipR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.6f,32,32);
		glPopMatrix();
	glEndList();

	kneeL.muscle = glGenLists(1);
	glNewList(kneeL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	kneeR.muscle = glGenLists(1);
	glNewList(kneeR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	ankleL.muscle = glGenLists(1);
	glNewList(ankleL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	ankleR.muscle = glGenLists(1);
	glNewList(ankleR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	shoulderL.muscle = glGenLists(1);
	glNewList(shoulderL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.6f,32,32);
		glPopMatrix();
	glEndList();

	shoulderR.muscle = glGenLists(1);
	glNewList(shoulderR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.6f,32,32);
		glPopMatrix();
	glEndList();

	elbowL.muscle = glGenLists(1);
	glNewList(elbowL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	elbowR.muscle = glGenLists(1);
	glNewList(elbowR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	wristL.muscle = glGenLists(1);
	glNewList(wristL.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();

	wristR.muscle = glGenLists(1);
	glNewList(wristR.muscle, GL_COMPILE);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		gluSphere(quadratic,0.5f,32,32);
		glPopMatrix();
	glEndList();
}

void body::initTexture(){
	torso3.texture = SOIL_load_OGL_texture
	(
	  "images/a.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);

}

body::body(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->rx = 0;
	this->ry = 0;
	this->rz = 0;
}
body::body(float x,float y,float z,float rx,float ry,float rz){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

void body::draw(){
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		torso3.draw();
	glPopMatrix();
}
