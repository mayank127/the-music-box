#ifndef BONE_H
#define BONE_H
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
class joint;
//Class for bone object
class bone {
	public:
		float x1,y1,z1;
		float x2,y2,z2;
		joint* child;
		//constructor for bone_t
		bone(float,float,float);
		bone(float,float,float,float,float,float,joint*); //both the points and child joint
		bone();												//null constructor
		bone(float,float,float,float,float,float);			//both end points

		void draw();		//draw function
};
#endif
