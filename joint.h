#ifndef JOINT_H
#define JOINT_H
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
class bone;
//Class for joint object
class joint {

	public:
		float x,y,z;
		float rx,ry,rz;
		bone* child;
		//constructor for joint
		joint(float,float,float,float,float,float,bone*); //position, rotation and child bone
		joint();												//null constructor
		joint(float,float,float,float,float,float);			//position and rotation

		void draw();		//draw function
};
#endif
