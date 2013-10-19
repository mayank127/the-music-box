#ifndef BOX_H
#define BOX_H

#include <list>
#include <string>
using namespace std;

//Class for box object
class box {
	public:
		GLuint boxDL11,boxDL12,texture;
		float size1,size2;
		float rx,x,y,z,dx;
		//constructor for box
		box(float,float,float,float,float,float);
		box();											//null constructor

		void createDL();
		void createSide(float, float);
		void draw();		//draw function
};
#endif
