#include "bone.h"
#include "joint.h"
#include <GL/gl.h>
#include <GL/glut.h>

bone::bone(float x2,float y2,float z2){
	this->x1 = 0;
	this->y1 = 0;
	this->z1 = 0;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->child = child;
}
bone::bone(float x1,float y1,float z1,float x2,float y2,float z2,joint* child){
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->child = child;
}
bone::bone(){
	this->x1 = this->y1 = this->z1 = 0;
	this->x2 = this->y2 = this->z2 = 0;
	this->child = NULL;
}
bone::bone(float x1,float y1,float z1,float x2,float y2,float z2){
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	this->child=NULL;
}

void bone::draw(){
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x1,y1,z1);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x2,y2,z2);
    glEnd();
    if(this->child!=NULL)
    	(this->child)->draw();
}