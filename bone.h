#ifndef BONE_H
#define BONE_H

#include <list>
#include <string>
using namespace std;
class joint;
//Class for bone object
class bone {
	public:
		float x,y,z;
		list<joint*> childeren;
		string name;
		//constructor for bone
		bone(float,float,float,list<joint*>,string); //points and childeren joint
		bone();												//null constructor
		bone(float,float,float,string);			//end point

		void draw();		//draw function
};
#endif
