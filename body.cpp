#include "body.h"

#include <GL/gl.h>
#include <GL/glut.h>

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
	hipL = joint(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, &thighL,"hipL");
	hipR = joint(-2.0, 0.0, 0.0, 0.0, 0.0, 0.0, &thighR,"hipR");
	kneeL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &legL,"kneeL");
	kneeR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &legR,"kneeR");
	ankleL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footL,"footL");
	ankleR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footR,"footR");
	shoulderL = joint(3.0, 5.0, 0.0, 0.0, 0.0, 0.0, &uarmL,"shoulderL");
	shoulderR = joint(-3.0, 5.0, 0.0, 0.0, 0.0, 0.0, &uarmR,"shoulderR");
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
	GLuint index = glGenLists(1);

	// compile the display list, store a triangle in it
	glNewList(index, GL_COMPILE);
	    glBegin(GL_QUADS);
	    glColor3f(0, 1, 0);
	    glVertex3f(0,0,0);
	    glVertex3f(0,1,0);
	    glVertex3f(1,1,0);
	    glVertex3f(1,0,0);
	    glEnd();
	glEndList();

	torso3.muscle = index;
	torso1.muscle = index;
	head.muscle = index;
	thighL.muscle = index;
	thighR.muscle = index;
	legL.muscle = index;
	legR.muscle = index;
	footL.muscle = index;
	footR.muscle = index;
	uarmL.muscle = index;
	uarmR.muscle = index;
	larmL.muscle = index;
	larmR.muscle = index;
	handL.muscle = index;
	handR.muscle = index;
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