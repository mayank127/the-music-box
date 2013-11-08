#include "joint.h"
#include "bone.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
joint::joint(float x,float y,float z,float rx,float ry,float rz, bone* child, string name){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->child = child;
	this->name = name;
	this->muscle = 0;
	this->texture = 0;
}
joint::joint(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->rx = 0;
	this->ry = 0;
	this->rz = 0;
	this->child = NULL;
	this->name = "";
	this->muscle = 0;
	this->texture = 0;
}
joint::joint(float x,float y,float z,float rx,float ry,float rz,string name){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->child = NULL;
	this->name = name;
}

void joint::setConstraint(float cxn, float cxp, float cyn, float cyp, float czn, float czp){
	this->cxn = cxn;
	this->cxp = cxp;
	this->cyn = cyn;
	this->cyp = cyp;
	this->czn = czn;
	this->czp = czp;
	this->muscle = 0;
	this->texture = 0;
}

void joint::draw(){
	// if(cxn > rx) rx = cxn;
	// else if(cxp < rx) rx = cxp;

	// if(cyn > ry) ry = cyn;
	// else if(cyp < ry) ry = cyp;

	// if(czn > rz) rz = czn;
	// else if(czp < rz) rz = czp;
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glCallList(muscle);
		if(this->child!=NULL)
			(this->child)->draw();
	glPopMatrix();
}
