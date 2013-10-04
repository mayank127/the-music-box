#ifndef BODY_H
#define BODY_H

#include "bone.h"
#include "joint.h"
using namespace std;

//Class for body object
class body {
	public:
		float x,y,z;
		float rx,ry,rz;
		bone torso3, torso1, head, thighL, thighR, legL, legR, footL, footR, uarmL, uarmR, larmL, larmR, handL, handR;
		joint torso2, neck, hipL, hipR, kneeL, kneeR, ankleL, ankleR, shoulderL, shoulderR, elbowL, elbowR, wristL, wristR;
		//constructor for body
		body();												//null constructor
		body(float,float,float,float,float,float);			//both end points

		void init();
		void initConstraints();
		void draw();		//draw function
};
#endif