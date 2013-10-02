#include "joint.h"
#include "bone.h"
#include <GL/gl.h>
#include <GL/glut.h>

joint::joint(float x,float y,float z,float rx,float ry,float rz, bone* child){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->child = child;
}
joint::joint(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->rx = 0;
	this->ry = 0;
	this->rz = 0;
	this->child = NULL;
}
joint::joint(float x,float y,float z,float rx,float ry,float rz){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->child = NULL;
}

void joint::draw(){
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(rx, 1.0, 0.0, 0.0);
		glRotatef(ry, 0.0, 1.0, 0.0);
		glRotatef(rz, 0.0, 0.0, 1.0);
		if(this->child!=NULL)
			(this->child)->draw();
	glPopMatrix();
}