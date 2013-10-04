#ifndef JOINT_H
#define JOINT_H
using namespace std;
#include <string>
class bone;
//Class for joint object
class joint {

	public:
		float x,y,z;	//position
		float rx,ry,rz;	//rotation
		float cxp, cxn, cyp, cyn, czp, czn;	//rotation constraint
		bone* child;
		string name;
		//constructor for joint
		joint(float,float,float,float,float,float,bone*,string); //position, rotation and child bone
		joint();												//null constructor
		joint(float,float,float,float,float,float,string);			//position and rotation

		void setConstraint(float,float,float,float,float,float);
		void draw();		//draw function
};
#endif
