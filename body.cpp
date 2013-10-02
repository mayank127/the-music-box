#include "body.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>

void body::init(){
	torso3 = bone(0.0, 5.0, 0.0,"torso3");
	torso1 = bone(0.0, 5.0, 0.0,"torso1");
	head = bone(0.0, 2.0, 0.0,"head");
	thighL = bone(0.0, -4.0, 0.0,"thighL");
	thighR = bone(0.0, -4.0, 0.0,"thighR");
	legL = bone(0.0, -5.0, 0.0,"legL");
	legR = bone(0.0, -5.0, 0.0,"legR");
	footL = bone(1.0, 0.0, 1.0,"footL");
	footR = bone(1.0, 0.0, 1.0,"footR");
	uarmL = bone(0.0, -3.0, 0.0,"uarmL");
	uarmR = bone(0.0, -3.0, 0.0,"uarmR");
	larmL = bone(0.0, -3.0, 0.0,"larmL");
	larmR = bone(0.0, -3.0, 0.0,"larmR");
	handL = bone(1.0, 0.0, 1.0,"handL");
	handR = bone(1.0, 0.0, 1.0,"handR");

	torso2 = joint(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, &torso1,"torso2");
	neck = joint(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, &head,"neck");
	hipL = joint(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, &thighL,"hipL");
	hipR = joint(-2.0, 0.0, 0.0, 0.0, 0.0, 0.0, &thighR,"hipR");
	kneeL = joint(0.0, -4.0, 0.0, 0.0, 0.0, 0.0, &legL,"kneeL");
	kneeR = joint(0.0, -4.0, 0.0, 0.0, 0.0, 0.0, &legR,"kneeR");
	ankleL = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footL,"footL");
	ankleR = joint(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, &footR,"footR");
	shoulderL = joint(3.0, 5.0, 0.0, 0.0, 0.0, 0.0, &uarmL,"shoulderL");
	shoulderR = joint(-3.0, 5.0, 0.0, 0.0, 0.0, 0.0, &uarmR,"shoulderR");
	elbowL = joint(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, &larmL,"elbowL");
	elbowR = joint(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, &larmR,"elbowR");
	wristL = joint(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, &handL,"handL");
	wristR = joint(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, &handR,"handR");

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


	torso3.name = "torso3";
	torso1.name = "torso1";
	head.name = "head";
	thighL.name = "thighL";
	thighR.name = "thighR";
	legL.name = "legL";
	legR.name = "legR";
	footL.name = "footL";
	footR.name = "footR";
	uarmL.name = "uarmL";
	uarmR.name = "uarmR";
	larmL.name = "larmL";
	larmR.name = "larmR";
	handL.name = "handL";
	handR.name = "handR";
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